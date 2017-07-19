// Dynamic programming solution. Use a matrix of integers of the same size to record the largest square having
// that position as the upper left corner. Work from lower right corner of matrix backwards. Let L(i,j) be this 
// maximum sidelength. Then L(i,j) = Min{L(i+1,j), L(i,j), L(i,j+1)} + 1 when L(i,j) = 1. That is, consider
// the a length of square that is in common for these specific adjacent spaces. Then (i,j) gives the upper left
// corner of square of one more length.

#include <iostream>
#include <vector>

using namespace std;

class Solution {

    public:
        int maximalSquare(vector<vector<char> > &matrix);

    private:
        void computeLengthMatrix(vector<vector<char> > &matrix, vector<vector<int> > &lengths);
        template <typename T>
        void initPosIt(typename vector<T>::reverse_iterator posIt[2][2], vector<T> &row1, vector<T> &row2);
        template <typename T>
        void moveLeft(typename vector<T>::reverse_iterator posIt[2][2]);
        int updateLength(int a, int b, int c);

        int maxLength;
};

// Debug functions

template<typename T>
void printMatrix(vector<vector<T> > &matrix); 
template void printMatrix<int>(vector<vector<int> > &matrix);

int main() {

    int maxSize;
    const int m = 7, n = 1;
    char strings[m][n+1] = {"1", "0", "1", "1", "1", "1", "0"};
    // const int m = 4, n = 5;
    // char strings[m][n+1] = {"10100",
    //                         "10111",
    //                         "11111",
    //                         "10010"};
    // This case failed on Leetcode as giving 1 as the area, but
    // it seems to return 0 on my machine.
    // const int m = 4, n = 3;
    // char strings[m][n+1] = {"000",
    //                         "000",
    //                         "000",
    //                         "000"};

    // const int m = 4, n = 5;
    // char strings[n][n+1] = {"00000",
    //                         "00000",
    //                         "00000",
    //                         "00000"};
   
    // char strings[m][n+1]  = {"10111",
    //                          "11011",
    //                          "11101",
    //                          "11111"};
    // const int m = 2, n = 2;
    // char strings[m][n+1] = {"11",
    //                         "11"};
    vector<vector<char> > matrix(m);
    Solution s;

    for(int i = 0; i < matrix.size(); i++)
        matrix[i] = vector<char>(strings[i], strings[i] + n);

    cout << "Matrix is:" << endl << endl;
    printMatrix(matrix);
    cout << endl;

    maxSize = s.maximalSquare(matrix);
    cout << "Maximal square area is " << maxSize << endl;

    return 1;

}

int Solution::maximalSquare(vector<vector<char> > &matrix) {

    int m = matrix.size(), n;
    vector<vector<int> > lengths;

    // Set up matrix size info.
    if(m == 0)
        return 0;

    n = matrix.begin() -> size();

    // Set up matrix for computing lengths.`
    lengths = vector<vector<int> >(m);
    for(int i = 0; i < m; i++)
        lengths[i] = vector<int>(n, 0);

    computeLengthMatrix(matrix, lengths);

    return maxLength * maxLength;
}

void Solution::computeLengthMatrix(vector<vector<char> > &matrix, vector<vector<int> > &lengths) {

    vector<vector<int> >::reverse_iterator rowIt;
    vector<vector<char> >::reverse_iterator rowIt2;
    vector<int>::reverse_iterator posIt[2][2];
    vector<char>::reverse_iterator posIt2;

    // Iterate over comparing mimima using position iterators. posIt[][] represents the following
    // posIt[0][0]  posIt[0][1]
    // posIt[1][0]  posIt[1][1]

    maxLength = 0;

    // Last row of lengths is just the last row of matrix, converted to integers.
    rowIt = lengths.rbegin();
    rowIt2 = matrix.rbegin(); 
    for(posIt[0][0] = rowIt -> rbegin(), posIt2 = rowIt2 -> rbegin();
        posIt[0][0] != rowIt -> rend();
        posIt[0][0]++, posIt2++) {


        *posIt[0][0] = *posIt2 - '0';
        if(*posIt[0][0] == 1)
            maxLength = 1;
    } 
  
    // Last column of lengths is also the same as that of matrix, just converted to integers.

    for(rowIt = lengths.rbegin(), rowIt2 = matrix.rbegin();
        rowIt != lengths.rend();
        rowIt++, rowIt2++) {

        *(rowIt -> rbegin()) = *(rowIt2 -> rbegin()) - '0'; 
        if (*(rowIt -> rbegin()) == 1)
            maxLength = 1;
    } 

    // Return if only one row or one column. 
    if(matrix.size() == 1 || matrix.begin() -> size() == 1)
        return;

    // Now iterate to the left and up over the remaining rows. Make sure to use reverse iterators. 

    for(rowIt = lengths.rbegin() + 1, rowIt2 = matrix.rbegin() + 1; rowIt != lengths.rend(); rowIt++, rowIt2++) {
        for ( initPosIt(posIt, *rowIt, *(rowIt - 1)), posIt2 = rowIt2 -> rbegin() + 1;
              posIt[0][0] != rowIt -> rend() ;
              moveLeft<int>(posIt), posIt2++) {

            if(*posIt2 == '1') {
                *posIt[0][0] = updateLength(*posIt[0][1], *posIt[1][1], *posIt[1][0]);
                if( *posIt[0][0] > maxLength)
                    maxLength = *posIt[0][0];
            }
        }

    }
}

template <typename T>
void Solution::initPosIt(typename vector<T>::reverse_iterator posIt[2][2], vector<T> &row1, vector<T> &row2) {
    
    posIt[0][1] = row1 . rbegin();
    posIt[0][0] = posIt[0][1] + 1;
   
    posIt[1][1] = row2 . rbegin();
    posIt[1][0] = posIt[1][1] + 1; 

}

template <typename T>
void Solution::moveLeft(typename vector<T>::reverse_iterator posIt[2][2]) {

    posIt[0][0]++;
    posIt[0][1]++;
    posIt[1][0]++;
    posIt[1][1]++;

}

int Solution::updateLength(int a, int b, int c) {

    int min;
    if( a < b )
        min = a;
    else 
        min = b;

    if( min > c)
        min = c;

    return min + 1;
}

template <typename T>
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
