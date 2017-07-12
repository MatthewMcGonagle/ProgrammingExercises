#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Solution {

    public:
        int kthSmallest(vector<vector<int> > &matrix, int k);

    private:
        int colMaxByArea(int row, int k);
};

int main() {

    // int numArrays[4][4] = { {1, 2, 3, 4},
    //                       {5, 6, 7, 8},
    //                       {9, 10, 11, 12},
    //                       {13, 14, 15, 16}};
    int n = 2,
        numArrays[2][2] = {{1, 2},
                           {1, 3}};
    vector<vector<int> > matrix(2);
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

    int n = matrix.size(), rowCnt, unitCnt;
    vector<vector<int> >::iterator rowIt, rowItEnd;
    vector<int>::iterator colItEnd;
    priority_queue<int> minVals;

    if( k < n )
        rowItEnd = matrix.begin() + k;
    else
        rowItEnd = matrix.end();

    rowCnt = 0;
    for ( rowIt = matrix.begin();
          rowIt != rowItEnd; 
          rowIt++, rowCnt++) {
    
        if(colMaxByArea(rowCnt, k) < n)
            colItEnd = rowIt -> begin() + colMaxByArea(rowCnt, k);
        else
            colItEnd = rowIt -> end(); 

        for(vector<int>::iterator colIt = rowIt -> begin();
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

    return minVals.top();
    
}

int Solution::colMaxByArea(int row, int k) {

    // Number of points in matrix that are less than or equal to the value at the position
    // at (row, col) is (row + 1)(col + 1) - 1 = row * col + row + col

    return 1 + (k - row) / (row + 1); 
}
