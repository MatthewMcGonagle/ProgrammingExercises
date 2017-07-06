// More direct comparison solution using the fact that it is a binary search tree. Accepted as
// beating 93.90% of all cpp submissions.
#include<iostream>
#include<queue>
#include<vector>
#include<sstream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {

    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode*  q);
        void addToTree(TreeNode* &root, int num);
        void deleteTree(TreeNode *root);
        void printTree(TreeNode *root);

    private:
        void addToQueue(TreeNode* current, queue<TreeNode*> &toProcess);
        void printParents(vector<TreeNode*> &parents);
        bool inTree(int val, TreeNode* start);
};

string printNode(TreeNode* p);

int main() {

    int numArray[] = {6, 2, 8, 0, 4, 7, 9, 3, 5},
        pValsArray[] = {2, 2},
        qValsArray[] = {8, 4};
    vector<int> numVector(numArray, numArray + sizeof(numArray) / sizeof(int)),
                pVals(pValsArray, pValsArray + sizeof(pValsArray) / sizeof(int)),
                qVals(qValsArray, qValsArray + sizeof(qValsArray) / sizeof(int));
    Solution s;
    TreeNode *root = NULL, *p = new TreeNode(0), *q = new TreeNode(0), *result;

    for (int i = 0; i < numVector.size(); i++)
        s.addToTree(root, numVector[i]);

    s.printTree(root);

    for( vector<int>::iterator pIt = pVals.begin(), qIt = qVals.begin();
         pIt != pVals.end();
         pIt++, qIt++) { 
            p -> val = *pIt;
            q -> val = *qIt;
            result = s.lowestCommonAncestor(root, p, q);
            cout << "Lowest Common Ancestor of " << printNode(p) 
                 << " and " << printNode(q) 
                 << " = " << printNode(result) << endl;
    }

    s.deleteTree(root);
    delete p, q;
    return 0;
}

// Function for printing output of running solution.

string printNode(TreeNode* p) { 

    ostringstream ss;

    if(p == NULL)
        return string("NULL");
    else {
        ss << p -> val;
        return ss.str();
    }
}

// Do a depth first search for p and q. Then search upwards to lowest common ancestor.

TreeNode* Solution::lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

    TreeNode* current;
    int small, large;
    bool smallOnLeft, largeOnLeft;

    if(p -> val < q -> val) {

        small = p -> val;
        large = q -> val;
    }

    else {

        small = q -> val;
        large = p -> val;
    }

    // Trivial case of empty tree.

    if(root == NULL)
        return NULL;

    // Now we leverage the fact that the lowest common ancestor is first element where
    // small is on left and large is on right. Before that, both are always on the same side.

    current = root;

    // We loop while the current node isn't null.

    do {
    
        // First check the cases of equality in p or q. Then need to search the tree to make sure
        // other value occurs in tree. Doesn't cost too much to just search for both.

        if (small == current -> val || large == current -> val) {
           
            if( inTree(small, current) && inTree(large, current) ) 
                return current;
            else
                return NULL;
        }

        // Cases of no equality.

        if( small < current -> val)
            smallOnLeft = true;
        else 
            smallOnLeft = false;

        if( large < current -> val)
            largeOnLeft = true;
        else
            largeOnLeft = false;

        if(smallOnLeft != largeOnLeft && inTree(small, current) && inTree(large, current))
            return current;
        else if (smallOnLeft)
            current = current -> left;
        else
            current = current -> right;

    } while(current != NULL);

    // If we encountered a null value, then there is no way both numbers are in tree.
    // So we return null.
    
    return NULL;

}

void Solution::addToTree(TreeNode* &root, int num) {

    TreeNode *current = root, *parent;
    bool isLeftChild;


    // Trivial case of empty tree.

    if( root == NULL) {
        root = new TreeNode(num);
        return;
    }

    parent = root;

    while ( current != NULL ) {
        if (num < current -> val) {
            parent = current;
            current = current -> left;
            isLeftChild = true;
        }
        else if (num > current -> val) {
            parent = current;
            current = current -> right;
            isLeftChild = false;
        }
        else // num is already in tree, so return.
            return;
    }    

    if(isLeftChild) 
        parent -> left = new TreeNode(num);
    else
        parent -> right = new TreeNode(num); 

}

void Solution::deleteTree(TreeNode *root) {

    TreeNode* current;
    queue<TreeNode*> toDelete;

    // Breadth first deletion. Add root to queue, and then keep deleting until none left.
    toDelete.push(root);

    while(!toDelete.empty()) {
    
        current = toDelete.front();
        toDelete.pop();
       
        if(current -> left != NULL)
            toDelete.push(current -> left);
        if(current -> right != NULL)
            toDelete.push(current -> right);
        delete current;      
    }

}

void Solution::printTree(TreeNode* root) {

    queue<TreeNode*> toPrint;
    TreeNode *current;

    toPrint.push(root);

    while(!toPrint.empty()) {

       current = toPrint.front();
       toPrint.pop();

       if(current == NULL)
            cout << "N, ";
       else {
            cout << current -> val << ", ";
            toPrint.push(current -> left);
            toPrint.push(current -> right); 
       }
 
    }

    cout << endl;
}


void Solution::addToQueue(TreeNode* current, queue<TreeNode*> &toProcess) {

    if(current != NULL)
        toProcess.push(current);
    
}

void Solution::printParents(vector<TreeNode*> &parents) {

    for (int i = 0; i < parents.size(); i++) {
        
        if(parents[i] != NULL)
            cout << parents[i] -> val << ", ";
        else
            cout << "N, ";
    }
    
    cout << endl;
}

bool Solution::inTree(int val, TreeNode* start) {

    TreeNode* current;

    current = start;

    do {

        if (val == current -> val)
            return true;
        else if (val < current -> val)
            current = current -> left;
        else
            current = current -> right;
    } while(current != NULL);

    return false;
}
