#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {

public:

    TreeNode* constructMaximumBinaryTree(vector<int> &nums);

private:

    TreeNode* constructTree(vector<int>::iterator begin, vector<int>::iterator end);
    vector<int>::iterator maxPosition(vector<int>::iterator begin, vector<int>::iterator end);
};

void myPrint(TreeNode *root) {

    queue<TreeNode*> toPrint;
    TreeNode *current;
    int counter, counterinit = 1;

    counter = counterinit;
    toPrint.push(root);
    while(!toPrint.empty()) {

        current = toPrint.front();
        toPrint.pop();

        if(current == NULL) { 
            cout << "N, ";
            counterinit--;
        }
        else {
            cout << current -> val << ", ";
            toPrint.push(current -> left);
            toPrint.push(current -> right);
        }  

        counter--;
        if(counter == 0) {
            cout << endl;
            counterinit *= 2;
            counter = counterinit;
        } 
    }

    cout << endl;
}

int main() {

    int numArray[] = {3, 2, 1, 6, 0, 5};
    vector<int> nums(numArray, numArray + sizeof(numArray) / sizeof(int));
    TreeNode *root;
    Solution s;

    root = s . constructMaximumBinaryTree(nums);

    myPrint(root);

    return 1;

}

TreeNode* Solution::constructMaximumBinaryTree(vector<int> &nums) {

    return constructTree(nums.begin(), nums.end());

}

TreeNode* Solution::constructTree(vector<int>::iterator begin, vector<int>::iterator end) {

    vector<int>::iterator pivot;
    TreeNode* newNode;

    // When array is empty, return NULL.

    if(begin == end)
        return NULL;

    pivot = maxPosition(begin, end);
    newNode = new TreeNode(*pivot);
    newNode -> left = constructTree(begin, pivot);
    newNode -> right = constructTree(pivot + 1, end);

    return newNode;
}

// Function maxPosition should only be called when begin < end.

vector<int>::iterator Solution::maxPosition(vector<int>::iterator begin, vector<int>::iterator end) {

    int max = *begin;
    vector<int>::iterator numIt, maxIt = begin; 

    for(numIt = begin + 1; numIt != end; numIt++) {
    
        if(*numIt > max) {
            max = *numIt;
            maxIt = numIt;
        }
    } 

    return maxIt;
} 
