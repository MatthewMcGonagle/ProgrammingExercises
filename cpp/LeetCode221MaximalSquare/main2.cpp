// Do a recursive solution on the number of rows. If we know the maximum dimensions of squares in rows
// 1 to m is D, then in row m+1, we need only look at sequences of '1' of length D+1. Note, adding one row
// can't increase the maximum dimension to D+2, because then the submatrix would have a '1' square of
// length D + 1. 

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {

    public:
        int maximalSquare(vector<vector<char> > &matrix);

    private:
        int maxLengthSub(int corneri, int cornerj, vector<vector<char> > &matrix);
        int maxLengthRow(vector<char> &row);
        void checkSquaresInEdge(int corneri, int cornerj, vector<vector<char> > &matrix, int length);
        bool isSquare(int corneri, int cornerj, vector<vector<char> > &matrix, int length);
    
        bool newSquaresFound;
};

// Debugging Functions

void printRow(vector<char> &row) {

    for (vector<char>::iterator iT = row.begin(); iT != row.end(); iT++)
        cout << *iT << " ";
    cout << endl;
}

void printSubmatrix(int corneri, int cornerj, vector<vector<char> > &matrix, int length) {

    for(int i = corneri; i < matrix.size() && i < corneri + length; i++) {
        for(int j = cornerj; j < matrix[i].size() && j < cornerj + length; j++)
            cout << matrix[i][j] << " ";
        cout << endl; 
    }
}

int main() {

    int maxSize;
    // const int m = 4, n = 5;
    // char strings[m][n+1]  = {"10111",
    //                          "11011",
    //                          "11101",
    //                          "11111"};
    const int m = 2, n = 2;
    char strings[m][n+1] = {"11",
                            "11"};
    vector<vector<char> > matrix(m);
    Solution s;

    for(int i = 0; i < matrix.size(); i++)
        matrix[i] = vector<char>(strings[i], strings[i] + n);

    cout << "Matrix is:" << endl << endl;
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    maxSize = s.maximalSquare(matrix);
    cout << "Maximal square area is " << maxSize << endl;

    return 1;
}

int Solution::maximalSquare(vector<vector<char> > &matrix) {

    int maxlength;

    // First handle trivial cases of empty matrix.

    if (matrix.size() == 0)
        return 0;
    if (matrix[0].size() == 0)
        return 0;

    maxlength = maxLengthSub(0, 0, matrix);
    return maxlength * maxlength; 

}

// Find the maximal square in the submatrix with upper left corner at
// position (corneri, cornerj). The matrix should be non-empty.

int Solution::maxLengthSub(int corneri, int cornerj, vector<vector<char> > &matrix) {

    int m = matrix.size() - corneri, 
        n = matrix.begin() -> size() - cornerj,
        max;

    if (corneri == matrix.size() - 1)
        return maxLengthRow(matrix[corneri]);
    else {
        max = maxLengthSub(corneri + 1, cornerj, matrix);
        checkSquaresInEdge(corneri, cornerj, matrix, max + 1); 
        if(newSquaresFound)
            max++;
    }

    return max;
} 

int Solution::maxLengthRow(vector<char> &row) {

    // If row contains any 1's, then the max is one, else it is 0.

    for (vector<char>::iterator iT = row.begin(); iT != row.end(); iT++)
        if (*iT == '1')
            return 1;

    return 0;
}

void Solution::checkSquaresInEdge(int corneri, int cornerj, vector<vector<char> > &matrix, int length) {

    newSquaresFound = false; 

    for(int j = cornerj; j < matrix[corneri].size() - length + 1; j++)
        if(isSquare(corneri, j, matrix, length) ) {
            newSquaresFound = true;
            return;
        }

}

bool Solution::isSquare(int corneri, int cornerj, vector<vector<char> > &matrix, int length) {

    // Two simple dimension checks.
    if (cornerj + length  - 1 >= matrix[corneri].size())
        return false;
    else if (corneri + length - 1 >= matrix.size())
        return false;

    // Now check that all of the entries are 1's.
    else {

        for (int i = corneri; i < corneri + length; i++)
            for (int j = cornerj; j < cornerj + length; j++)
                if(matrix[i][j] == '0')
                    return false;
    }
    
    // Everything passed so it is a square.
    return true;

}
