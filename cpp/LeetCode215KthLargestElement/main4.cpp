// Solution using heap of size k. Let the heap be ordered so that smallest is at top.
// Iterate over the numbers and add to the heap only if value is greater than minimum.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {

    public:
     
        int findKthLargest(vector<int> &nums, int k);

    private:

        void addNotFull(vector<int> &heap, int val);
        void addFull(vector<int> &heap, int val);
};

int main() {

    int numArray[] = {3,2,3,4,3};
    int k = 2;
    vector<int> numVector(numArray, numArray + sizeof(numArray) / sizeof(int));
    Solution s;

    cout << "numVector = ";
    for(int i = 0; i < numVector.size(); i++)
        cout << numVector[i] << ", ";
    cout << endl;

    cout << "k = " << k << endl
         << "kth Largest = " << s.findKthLargest(numVector, k) << endl;

    sort(numVector.begin(), numVector.end());
    cout << "Double check, sorted kth largest = " << *(numVector.end() - k) << endl;

    return 0;

}

int Solution::findKthLargest(vector<int> &nums, int k) {

    vector<int> heap;
    vector<int>::iterator numsIt;

    heap.reserve(k);
    
    // Add values into non-full heap.

    for(numsIt = nums.begin(); numsIt != nums.begin() + k; numsIt++)
        addNotFull(heap, *numsIt);

    // Now only add values into heap when greater than top of heap.

    return heap[0];

}
   
// Add value to heap when heap is not full. Top of heap is smallest value. 
void Solution::addNotFull(vector<int> &heap, int val) {

    int last, current, temp;
    bool bubbling;

    heap.push_back(val);
    last = heap.size() - 1;
    bubbling = true;

    while(last > 0 && bubbling) {

        current = last / 2;

        if(heap[current] > heap[last]) {

            //Swap current and last
            temp = heap[current];
            heap[current] = heap[last];
            heap[last] = temp;
        }
        else
            bubbling = false;
    }
    
}

// Add value into heap when it is full. Should only be called if value is greater than top of heap.
// Value on top of heap is replaced by new value (as it is smallest value there and we seek kth 
// largest value). Then new value is bubbled down into position.

void Solution::addFull(vector<int> &heap, int value) {

    int current, lchild, temp;
    bool bubbling;


    heap[0] = value;
    current = 0;
    
}
