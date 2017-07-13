// Now we put in minimum for each row in addition to previously used max for each row. Minimum is coming from the number of squares to the right and down of current position; this can't exceed n^2 - (k - 1).
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Solution {

    public:
        int kthSmallest(vector<vector<int> > &matrix, int k);

    private:
        int colMaxByArea(int row, int k);
        int colMinByArea(int row, int k, int n);
};

int main() {

    // int numArrays[4][4] = { {1, 2, 3, 4},
    //                       {5, 6, 7, 8},
    //                       {9, 10, 11, 12},
    //                       {13, 14, 15, 16}};
    // int n = 2,
    //     numArrays[2][2] = {{1, 2},
    //                        {1, 3}};
    // int n = 3,
    //     numArrays[3][3] = { {1, 3, 5},
    //                         {6, 7, 12},
    //                         {11, 14, 14}};
    int n = 3,
        numArrays[3][3] = { {1, 5 , 9},
                           {10, 11, 13},
                           {12, 13, 15}};
    vector<vector<int> > matrix(3);
    for(int i = 0; i < n; i++)
        matrix[i] = vector<int>(numArrays[i], numArrays[i] + n);
    Solution s;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }

    for ( int k = 1; k < n * n; k++)
        cout << k << "th min = " << s.kthSmallest(matrix, k) << endl;

    return 0;

}

int Solution::kthSmallest(vector<vector<int> > &matrix, int k) {

    int n = matrix.size(), rowCnt, unitCnt, beginCol, endCol, numPop = 0;
    vector<vector<int> >::iterator rowIt, rowItEnd;
    vector<int>::iterator colItEnd, colItBegin;
    priority_queue<int> minVals;

    if( k < n )
        rowItEnd = matrix.begin() + k;
    else
        rowItEnd = matrix.end();

    rowCnt = 0;
    for ( rowIt = matrix.begin();
          rowIt != rowItEnd; 
          rowIt++, rowCnt++) {
  
        endCol = colMaxByArea(rowCnt, k); 
        if (endCol > n)
            endCol = n;
        colItEnd = rowIt -> begin() + endCol; 

        colItBegin = rowIt -> begin();
        beginCol = colMinByArea(rowCnt, k, n);

        if(beginCol < 0)
            beginCol = 0;
        else if(beginCol > endCol)
            beginCol = endCol;

        numPop += beginCol;        
        colItBegin = rowIt -> begin() + beginCol;

        for(vector<int>::iterator colIt = colItBegin; 
             colIt != colItEnd; 
             colIt++) {
     
           if(minVals.size() < k) 
                minVals.push(*colIt);
           else if( *colIt < minVals.top()) {
              minVals.pop();
              minVals.push(*colIt);
           } 
        }

    } 

    numPop -= k - minVals.size();
    for (int i = 0; i < numPop; i++)
        minVals.pop();

    return minVals.top();
    
}

int Solution::colMaxByArea(int row, int k) {

    // Number of points in matrix that are less than or equal to the value at the position
    // at (row, col) is (row + 1)(col + 1) - 1 = row * col + row + col

    return  k / (row + 1); 
}

int Solution::colMinByArea(int row, int k, int n) {

    // Number of points in matrix that are greater than or equal to the point at position
    // (row, col) is (n - row) * (n - col). Need this number to be less than or equal to
    // n^2 - (k - 1). So n - col <= (n^2 + 1 - k) / ( n - row).

    return -1 + n - (n * n + 1 - k) / (n - row);
}
