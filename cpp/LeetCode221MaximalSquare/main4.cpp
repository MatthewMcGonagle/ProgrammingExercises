// Dynamic programming using lower right corners and only keeping track of last row. Iterates to the right and
// down inside matrix.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {

    public:
        int maximalSquare(vector<vector<char> > &matrix);

    private:
        bool allEmpty(vector<char> &row);
        bool trivialCase(vector<vector<char> > &matrix);
        void initLastRow(vector<vector<char> > &matrix, vector<int> &lastRow);
        void computeRow(vector<int> &lastRow, vector<char> &newRow);
        int computeVal(int upleft, int upright, int lowleft);

        const static char EMPTY = '0', NONEMPTY = '1';
        int maxLength;
};

// Debug functions.

template<typename T>
void printMatrix(vector<vector<T> > &matrix);

int main() {

    // const int m = 4, n = 5;
    // char stringArray[m][n+1] = {"10101",
    //                             "11101",
    //                             "11110",
    //                             "11111"};
    // const int m = 4, n = 1;
    // char stringArray[m][n+1] = {"1", "0", "0", "0"};
    // const int m = 1, n = 4;
    // char stringArray[m][n+1] = {"0000"};
    const int m = 2, n = 4;
    char stringArray[m][n+1] = {"0000",
                                "0001"};
    vector<vector<char> > matrix(m);
    Solution s;
    int maxArea;

    for(int row = 0; row < m; row++)
        matrix[row] = vector<char>(stringArray[row], stringArray[row] + n);

    cout << "Matrix is:" << endl;
    printMatrix<char>(matrix);

    maxArea = s.maximalSquare(matrix);
    cout << "Maximal square area = " << maxArea << endl;

    return 1;
}

int Solution::maximalSquare(vector<vector<char> > &matrix) {

    vector<int> lastRow, currentRow;
    vector<vector<char> >::iterator rowIt;

    if(trivialCase(matrix))
        return maxLength * maxLength;

    // In a non-trivial case, i.e. non-empty matrix with atleast 2 rows and 2 columns. 

    initLastRow(matrix, lastRow);
    for(rowIt = matrix.begin() + 1; rowIt != matrix.end(); rowIt++) 
        computeRow(lastRow, *rowIt); 

    return maxLength * maxLength;
}

bool Solution::allEmpty(vector<char> &row) {

    for (vector<char>::iterator valIt = row.begin(); valIt != row.end(); valIt++)
        if (*valIt == NONEMPTY)
            return false;
    return true;
}

// Checks for trivial cases. If trivial, then maxLength is either 1 or 0.
bool Solution::trivialCase(vector<vector<char> > &matrix) {

    int m = matrix.size();
    vector<vector<char> >::iterator rowIt;

    // Set up sizes. Empty matrices return a max of 0.

    if (m == 0 || matrix.begin() -> size() == 0) {
        maxLength = 0;
        return true;
    }

    // Trivial one row case doesn't really fall under pattern of dynamic programming.

    if (m == 1 && allEmpty(matrix[0])) {
        maxLength = 0;
        return true;
    }
    else if (m == 1) {
        maxLength = 1;
        return true;
    }

    // Trivial case of one column.
    if (matrix.begin() -> size() == 1) {
        maxLength = 0;
        for (rowIt = matrix.begin(); rowIt != matrix.end(); rowIt++)
            if( *(rowIt -> begin()) != EMPTY) {
                maxLength = 1;
                return true;
            } 
        return true; 
    }

    return false;
 
}

// The array lastRow is initially set to integer equivalent of matrix[0].

void Solution::initLastRow(vector<vector<char> > &matrix, vector<int> &lastRow) {

    vector<int>::iterator outIt;
    vector<char>::iterator inIt, inEnd = matrix.begin() -> end();

    lastRow = vector<int>(matrix.begin() -> size());

    maxLength = 0;
    for(inIt = matrix.begin() -> begin(), outIt = lastRow.begin(); inIt != inEnd; inIt++, outIt++) {
        if(*inIt == EMPTY)
            *outIt = 0;
        else {
            *outIt = 1;
            maxLength = 1;
        }
    } 
        
}

void Solution::computeRow(vector<int> &lastRow, vector<char> &newRow) {

    vector<int> newVals = vector<int>(lastRow.size());
    vector<int>::iterator lastIt, valsIt;
    vector<char>::iterator newIt;
    int newVal;

    // Initialize first value of newVals.

    if(*newRow.begin() == EMPTY)
        *newVals.begin() = 0;
    else {
        *newVals.begin() = 1;
        if (maxLength < 1)
            maxLength = 1;
    }

    // newIt points to lower right. lastIt points to upperleft. valsIt points to lower left. 

    for( lastIt = lastRow.begin(), newIt = newRow.begin() + 1, valsIt = newVals.begin();
         lastIt != lastRow.end() - 1; 
         lastIt++, newIt++, valsIt++) {
        
         if(*newIt == EMPTY)
            *(valsIt + 1) = 0;

         else { 
            newVal = computeVal(*lastIt, *(lastIt+1), *valsIt);
            if(newVal > maxLength)
                maxLength = newVal;
            *(valsIt + 1) = newVal; 
         }
    }

    lastRow = newVals;   
}

int Solution::computeVal(int upleft, int upright, int lowleft) {

    int min;

    // Fist compute the minimum of the three values.

    if(upleft < upright)
        min = upleft;
    else
        min = upright;

    if(lowleft < min)
        min = lowleft;

    return min + 1;
}

template<typename T>
void printMatrix(vector<vector<T> > &matrix) {

    typename vector<vector<T> >::iterator rowIt;
    typename vector<T>::iterator valIt;

    for(rowIt = matrix.begin(); rowIt != matrix.end(); rowIt++) {

        for(valIt = rowIt -> begin(); valIt != rowIt -> end(); valIt++)
            cout << *valIt << " ";

        cout << endl;
    }
    cout << endl;
}


