// Solution based on quicksort. However, only need to worry about sorting around kth largest space instead of the entire array.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {

    public:

        int findKthLargest(vector<int> &nums, int k);
        int partition(vector<int> &nums, int left, int right);

    private:
        void printNums(vector<int> &nums);
        void printRange(vector<int> &nums, int left, int right);
};

int main() {

    int numArray[] = {5, 5, 5, 2, 4, 5};
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

    int pivot, begin, end;

    // Do partial quicksort into descending order around k-1 position.

    begin = 0;
    end = nums.size();
    do {

        pivot = partition(nums, begin, end);

        if ( pivot < k - 1 ) 
            begin = pivot + 1;

        else if ( pivot > k - 1) 
            end = pivot;

    } while (pivot != k - 1);

    return nums[pivot];
}

int Solution::partition(vector<int> &nums, int left, int right) {
    
    int lastLeftPart, temp, pValue;

    // Use nums[left] as pivot.

    pValue = nums[left];
    lastLeftPart = left;
    for(int i = left + 1; i < right; i++) {
       if(nums[i] > pValue){
            // Increment left partition endpoint and swap value there with nums[i].
            lastLeftPart++;
            temp = nums[i];
            nums[i] = nums[lastLeftPart];
            nums[lastLeftPart] = temp;
       } 
    }
    
    // Now swap nums[left] and nums[lastLeftPart].
    nums[left] = nums[lastLeftPart];
    nums[lastLeftPart] = pValue;

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
