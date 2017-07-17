#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct cornerNode {

    int i, j;
    cornerNode *next;

    cornerNode(int i_, int j_) : i(i_), j(j_), next(NULL) {} 
};

class Solution {

    public:
        int maximalSquare(vector<vector<char> > &matrix);

    private:
        void initializeCorners(vector<vector<char> >&matrix); 
        void filterSize(vector<vector<char> > &matrix, int size);
        void checkEdges(vector<vector<char> > &matrix, cornerNode *corner, int size);
        void deleteNode(cornerNode *toDelete, cornerNode *parent);
   
        cornerNode *start; 
        bool edgesFull;
        int n;
};

void printNodes(cornerNode* base);

int main() {

    const int n = 5;
    int rowN, maxSize;
    char numArray[n][n] = { {1, 0, 1, 0, 0},
                            {1, 0, 1, 1, 1},
                            {1, 1, 1, 1, 1},
                            {1, 0, 0, 1, 0},
                            {0, 0, 0, 0, 0}};
    vector<vector<char> > matrix(n);
    Solution s;
   
    rowN = 0; 
    for(vector<vector<char> >::iterator rowIt = matrix.begin(); rowIt != matrix.end(); rowIt++, rowN++) {

        *rowIt = vector<char>(numArray[rowN], numArray[rowN] + n);
    }

    // Print out the matrix.

    for(vector<vector<char> >::iterator rowIt = matrix.begin(); rowIt != matrix.end(); rowIt++) { 
        for(vector<char>::iterator colIt = rowIt -> begin(); colIt != rowIt -> end(); colIt++)
            cout << (int)*colIt << " ";
        cout << endl;
    }

    maxSize = s.maximalSquare(matrix);
    cout << "Maximal Square size = " << maxSize << endl;
    return 0;
}

int Solution::maximalSquare(vector<vector<char> > &matrix) {

    int size = 0;

    n = matrix.size();
    initializeCorners(matrix);

    size = 0;
    while(start != NULL) {
       size++;
       filterSize(matrix, size + 1); 
    }

    return size * size;
      
}

void Solution::initializeCorners(vector<vector<char> > &matrix) {

    vector<vector<char> >::iterator rowIt;
    vector<char>::iterator valIt;
    int rowN, colN;
    cornerNode *current;

    start = NULL;
    if (matrix.size() == 0)
        return;

    // Set up temporary dummy node to initialize list.

    start = new cornerNode(-1, -1);
    current = start;

    rowN = 0;
    for(rowIt = matrix.begin(); rowIt != matrix.end(); rowIt++, rowN++) {

        colN = 0;
        for(valIt = rowIt -> begin(); valIt != rowIt -> end(); valIt++, colN++) {
            if (*valIt == 1) {
                current -> next = new cornerNode(rowN, colN);
                current = current -> next; 
            }
        }
    }

    // Now delete temporary dummy starting point.
    current = start -> next;
    delete start;
    start = current;
    
}

void Solution::filterSize(vector<vector<char> > &matrix, int size) {

    cornerNode *current = start, *parent = NULL;

    while(current != NULL) {

        checkEdges(matrix, current, size);
        if(!edgesFull) { 
            deleteNode(current, parent);
            if( parent != NULL)
                current = parent -> next;
            else
                current = start;
        }
        else {
            parent = current;
            current = current -> next;
        }
    }
}

void Solution::checkEdges(vector<vector<char> > &matrix, cornerNode *corner, int size) {

    int i, j;
   
    j = corner -> j + size - 1; 
    if (j >= n) {
        edgesFull = false;
        return;
    }
    if ( corner-> i + size - 1 >= n) {
        edgesFull = false;
        return;
    }
    
    for(i = corner -> i; i < corner -> i + size; i++)
        if(matrix[i][j] == 0) {
            edgesFull = false;
            return;
        }

    i = corner -> i + size - 1;
    if (i >= n) {
        edgesFull = false;
        return;
    }
    if(corner -> j + size - 2 >= n) {
        edgesFull = false;
        return;
    }

    // Note, we don't need to check the corner again, so bound is one less than
    // that for the loop of i above.
    for ( j = corner -> j; j < corner -> j + size - 1; j++)
        if(matrix[i][j] == 0) {
            edgesFull = false;
            return;
        }

    edgesFull = true;
}

void Solution::deleteNode(cornerNode* toDelete, cornerNode* parent) {

    if(parent == NULL) // Deleting start. 
        start = toDelete -> next;
    else 
        parent -> next = toDelete -> next;

    delete toDelete;
}

void printNodes(cornerNode *base) {

    while( base != NULL) {

        cout << "(" << base -> i 
             << ", " << base -> j 
             << ") -> ";
        base = base -> next;
    }
    cout << "NULL" << endl;
}
