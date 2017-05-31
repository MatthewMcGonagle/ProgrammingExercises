// Implement a tree where we keep track of kth largest element. Only insert elements if they are atleast as large.
// Then move marker for kth largest.

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

struct node {
    int value;
    node *left = NULL, *right = NULL;
};

class Solution {

    public:
    
        int findKthLargest(vector<int> &nums, int k);

    private:

        void simpleInsert(node *root, int value);
        void findSmallest(node *root, stack<node*> &path);
        void moveKthLargest(stack<node*> &path);
        void printPath(stack<node*> path);
        void printTree(node* root);
};

int main() {

    int numArray[] = {3,1,2,4}; 
    int k = 2;
    vector<int> numVector(numArray, numArray + sizeof(numArray) / sizeof(int));
    Solution s;

    cout << "numVector = ";
    for(vector<int>::iterator it = numVector.begin(); it != numVector.end(); it++)
        cout << *it << ", "; 
    cout << endl;

    cout << "k = " << k << endl;

    cout << "kth Largest Element = " << s.findKthLargest(numVector, k) << endl;
 
    sort(numVector.begin(), numVector.end());
    cout << "For double checking, numVector in order is" << endl << "    = "; 
    for(vector<int>::iterator it = numVector.begin(); it != numVector.end(); it++)
        cout << *it << ", "; 
    cout << endl;
    cout << "For double checking, kth Largest by sort = " << *(numVector.end() - k) << endl;

   return 0;

}

int Solution::findKthLargest(vector<int> &nums, int k) {

    int numInTree = 0;
    vector<int>::iterator numsIt;
    node largestRoot; 
    stack<node*> pathToKth;
    bool inserted;

    largestRoot.value = nums[0];
    numInTree = 1; 
    if(k == 1)
        pathToKth.push(&largestRoot);

    for(numsIt = nums.begin() + 1; numsIt != nums.end(); numsIt++) {

        // When there are too few elements in tree, we just do simple insert.
        // Also check to see if we now have exaclty k elements. In that case,
        // find the smallest element in tree, which is the current kth Largest. 

        if(numInTree < k) {

            simpleInsert(&largestRoot, *numsIt);
            numInTree++;

            if(numInTree == k) 
                findSmallest(&largestRoot, pathToKth);
        }

        // Current number is greater than current kth largest.
        else if (*numsIt > pathToKth.top() -> value) {
            simpleInsert(&largestRoot, *numsIt);
            moveKthLargest(pathToKth);
        }

    }

    return pathToKth.top() -> value;
}

void Solution::simpleInsert(node *current, int value) {

    while(current != NULL) {
        if(current -> value < value) {
            if(current -> right != NULL)
                current = current -> right;
            else {
                current -> right = new node;
                current -> right -> value = value;
                return;
            }
        }
        else {
            if(current -> left != NULL)
                current = current -> left;
            else {
                current -> left = new node;
                current -> left -> value = value;
                return;
            }
        }
    }

}

void Solution::findSmallest(node *current, stack<node*> &path) {

    while(current != NULL) {

        path.push(current);
        current = current -> left;

    }

}

void Solution::moveKthLargest(stack<node*> &path) {
    node *last, *current;
    bool kthFound;

    // First check to see if there is anything to the right of
    // the current kth largest.

    current = path.top();
    if(current -> right != NULL) {
        current = current -> right;
        findSmallest(current, path);        
        return;
    }

    // Nothing to the right of kth largest, so we must pull back.
    // The new kth largest has been found when we are no longer backing up from the right direction.
    last = path.top();
    path.pop();
    current = path.top();
    while(last == current -> right) {
        last = current;
        path.pop();
        current = path.top();
    }
}

void Solution::printPath(stack<node*> path) {

    node *current;

    cout << "Path = ";
    while(!path.empty()) {
        current = path.top();
        cout << current -> value << " <- ";
        path.pop();
    }    
    cout << endl;
    
}

void Solution::printTree(node* root) {
    
    node* current;
    queue<node*> toPrint;

    cout << "Tree = ";
    toPrint.push(root);
    while(!toPrint.empty()) {
        current = toPrint.front();
        toPrint.pop();
        cout << current -> value << ", ";
        if (current -> left != NULL)
            toPrint.push(current -> left);
        else
            cout << "NL, ";
        if (current -> right != NULL)
            toPrint.push(current -> right);
        else
            cout << "NR, ";
    }
    cout << endl;
}
