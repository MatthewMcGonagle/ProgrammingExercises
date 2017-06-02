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
        void printHeap(vector<int> &heap);
};

int main() {

    int numArray[] = {7,6,5,4,3,2,1};
    int k = 5;
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

    for(; numsIt != nums.end(); numsIt++) {
        if( *numsIt > heap[0])
            addFull(heap, *numsIt);
    }
 
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

        current = (last + 1) / 2 - 1;

        if(heap[current] > heap[last]) {

            //Swap current and last
            temp = heap[current];
            heap[current] = heap[last];
            heap[last] = temp;
        }
        else
            bubbling = false;

        last = current;
    }

}

// Add value into heap when it is full. Should only be called if value is greater than top of heap.
// Value on top of heap is replaced by new value (as it is smallest value there and we seek kth 
// largest value). Then new value is bubbled down into position.

void Solution::addFull(vector<int> &heap, int value) {

    int current, lchild, temp, rchild;
    bool bubbling;

    heap[0] = value;
    current = 0;
    lchild = 2 * (current + 1) - 1;
    bubbling = true;

    while(lchild < heap.size() && bubbling) {
        
        rchild = lchild + 1;
        // Check to see if right child is in range of heap
        if( rchild < heap.size()) {
       
            // Bubble up the least of current, left child, and right child. 
            if( heap[current] > heap[lchild] && heap[lchild] < heap[rchild] ) {
                //Swap current and left child.
                temp = heap[current];
                heap[current] = heap[lchild];
                heap[lchild] = temp;

                current = lchild;
            }
            else if ( heap[current] > heap[rchild] ) {
                //Swap current and right child.
                temp = heap[current];
                heap[current] = heap[rchild];
                heap[rchild] = temp;

                current = rchild;
            } 
            else
                bubbling = false;
        }

        // Right child outside of heap range, so it is not in heap. Only
        // need to look at left child.
        else {
            if( heap[current] > heap[lchild] ) {
                // Swap current and left child.
                temp = heap[current];
                heap[current] = heap[lchild];
                heap[lchild] = temp;

                current = lchild;
            }
            else
                bubbling = false;
        }

        // Compute left child of new current position.
        lchild = 2 * (current + 1) - 1;
    }
    
}

void Solution::printHeap(vector<int> &heap) {
    
    cout << "Heap = ";
    for(int i = 0; i < heap.size(); i++)
        cout << heap[i] << ", ";
    cout << endl;
}
