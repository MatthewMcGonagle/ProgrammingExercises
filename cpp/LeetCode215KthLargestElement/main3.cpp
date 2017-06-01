// Solution based on quicksort. However, only need to worry about sorting around kth largest space instead of the entire array.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {

    public:

        int findKthLargest(vector<int> &nums, int k);
        vector<int>::iterator partition(vector<int> &nums, vector<int>::iterator left, vector<int>::iterator right);

    private:
        void printNums(vector<int> &nums);
        void printRange(vector<int> &nums, int left, int right);
};

int main() {

    int numArray[] = {5, 3, 3, 2, 4, 2};
    int k = 2;
    vector<int> numVector(numArray, numArray + sizeof(numArray) / sizeof(int));
    Solution s;
    int result;
   
    cout << "numVector = ";
    for(int i = 0; i < numVector.size(); i++)
        cout << numVector[i] << ", ";
    cout << endl; 

    result = s.findKthLargest(numVector, k);
    cout << "k = " << k << endl
         << "kth Largest = " << result << endl;

    sort(numVector.begin(), numVector.end()); 
    cout << "As a double check, sorted kth largest = " << *(numVector.end() - k) << endl;

    return 0;
}

int Solution::findKthLargest(vector<int> &nums, int k) {

    vector<int>::iterator pivot, begin, end;
    int pIndex;

    // Do partial quicksort into descending order around k-1 position.

    begin = nums.begin();
    end = nums.end();
    do {

        pivot = partition(nums, begin, end);
    
        pIndex = pivot - nums.begin();

        if ( pIndex < k - 1 ) 
            begin = pivot + 1;

        else if ( pIndex > k - 1) 
            end = pivot;


    } while (pIndex != k - 1);

    return (*pivot);
}

vector<int>::iterator Solution::partition(vector<int> &nums, vector<int>::iterator left, vector<int>::iterator right) {
    
    int temp, pValue;
    vector<int>::iterator lastLeftPart, numsIt;

    // Use nums[left] as pivot.

    pValue = *left;
    lastLeftPart = left;
    for(numsIt = left + 1; numsIt != right; numsIt++) {
       if(*numsIt > pValue){
            // Increment left partition endpoint and swap value there with nums[i].
            lastLeftPart++;
            temp = *numsIt;
            *numsIt = *lastLeftPart;
            *lastLeftPart = temp;
       } 
    }
    
    // Now swap nums[left] and nums[lastLeftPart].
    *left = *lastLeftPart;
    *lastLeftPart = pValue;

    return lastLeftPart;
}

void Solution::printNums(vector<int> &nums) {

    vector<int>::iterator numsIt;

    cout << "Nums = ";
    for(numsIt = nums.begin(); numsIt != nums.end(); numsIt++)
        cout << *numsIt << ", ";
    cout << endl;
}

void Solution::printRange(vector<int> &nums, int left, int right) {
    
    cout << "Range = ";
    for(int i = left; i < right; i++) 
        cout << nums[i] << ", ";
    cout << endl;
}
