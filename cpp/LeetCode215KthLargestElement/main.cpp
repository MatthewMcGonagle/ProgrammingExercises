// Build binary tree from values and find kth largest value in tree. 

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct node { 
    int value;
    node *left = NULL, *right = NULL;
};

class Solution {
    public:

        int findKthLargest(vector<int>& nums, int k);

    private:

        void insertValue(node *root, int value);
        void findPathLargest(node* root, stack<node*> &path);
        int traceKthLargest(stack<node*> &path, int k);
        void addLeftPath(stack<node*> &path, node* current);
        void printTree(node* root);
        void printPath(stack<node*> path);
};

int main() {

    int numsArray[] = {-1, 2, 0}; 
    vector<int> numsVector(numsArray, numsArray + sizeof(numsArray) / sizeof(int));
    int k = 3; 
    Solution s;

    cout << "numsVector = ";
    for(int i = 0; i < numsVector.size(); i++)
        cout << numsVector[i] << ", ";
    cout << endl;

    cout << "k = " << k << endl;
    cout << "kth largest element = " << s.findKthLargest(numsVector, k) << endl;
    cout << "For double check, numsVector in order is" << endl;
    sort(numsVector.begin(), numsVector.end());
    cout << "      ";
    for(int i = 0; i < numsVector.size(); i++)
        cout << numsVector[i] << ", ";
    cout << endl;

    return 0;
}

int Solution::findKthLargest(vector<int>& nums, int k) {
    vector<int>::iterator numsIt;
    node valuesRoot; 
    stack<node*> pathLargest;

    valuesRoot.value = nums[0];

    for(numsIt = nums.begin() + 1; numsIt != nums.end(); numsIt++ ) 
        insertValue(&valuesRoot, *numsIt);

    findPathLargest(&valuesRoot, pathLargest);
    
    return traceKthLargest(pathLargest, k); 
}

// Return True if value inserted, else false if value is already in tree.
void Solution::insertValue(node *root, int value) {

    while(root != NULL) {
        if(value < root -> value) {
            if(root -> left != NULL)
                root = root -> left;
            else {
                root -> left = new node;
                root = root -> left;
                root -> value = value;
                return;
            }
        }
        else {
            if(root -> right != NULL)
                root = root -> right;
            else {
                root -> right = new node;
                root = root -> right;
                root -> value = value;
                return;
            }

        }
    }

}

void Solution::findPathLargest(node* root, stack<node*> &path) {

    path = stack<node*>();

    while(root != NULL) {
        path.push(root);
        root = root -> right;
    }

}

int Solution::traceKthLargest(stack<node*> &path, int k) {

    int currentK = 0;
    node* current;

    while (currentK < k) {

        current = path.top();
        currentK++;

        path.pop();

        if(current -> left != NULL)
            addLeftPath(path, current); 
    }    

    return current -> value;
}

void Solution::addLeftPath(stack<node*> &path, node* current) {
   
    current = current -> left;
 
    while (current != NULL) {
        path.push(current);
        current = current -> right;
    }
}

void Solution::printTree(node* root) {
    
    stack<node*> toPrint;
    node *current;

    toPrint.push(root);

    while(!toPrint.empty()) {
        current = toPrint.top();
        toPrint.pop();
        cout << current -> value << ", ";        

        if(current -> left != NULL)
            toPrint.push(current -> left);
        else
            cout << "NL, ";

        if(current -> right != NULL)
            toPrint.push(current -> right); 
        else
            cout << "NR, ";
    }
}

void Solution::printPath(stack<node*> path) {
    node *current;

    while(!path.empty()) {
        current = path.top();
        cout << current -> value << " <- ";
        path.pop();
    }
}
