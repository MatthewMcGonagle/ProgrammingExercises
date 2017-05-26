// Solution based on doing an initial pass to find first occurrence of max and last occurrence of max. Then rain water formation is to make the elevation increase to first occurrence, stay constant until last occurrence, and then decrease until end.

#include <iostream>
#include <vector>

using namespace std;

class Solution {

    public:
        
        int trap(vector<int>& height);

};

int main() {

    int height[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    vector<int> hvector = vector<int>(height, height + sizeof(height) / sizeof(int));
    class Solution s;

    cout << "Water trapped = " << s.trap(hvector) << endl;
    return 0;
}

int Solution::trap(vector<int>& height) {

    int maxVal, lastVal; 
    vector<int>::iterator heightIt, mPosFirst, mPosLast;

    // Take care of trivial case.

    if(height.size() == 0)
        return 0;

    // Do a first pass finding the position of the maximum of the heights, the first position the maximum
    // height occurs, and the last position the maximum height occurs.

    mPosFirst = height.begin();
    maxVal = *mPosFirst; 
    for(heightIt = height.begin(); heightIt != height.end(); heightIt++) {
        if(*heightIt == maxVal)
            mPosLast = heightIt;
        else if( *heightIt > maxVal) {
            mPosFirst = heightIt;
            mPosLast = heightIt;
            maxVal = *heightIt;
        }
    }
    
    return 0;
}
