//Depth first search solution. Accepted with benchmark of beating 55.49% of all cpp submissions.
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
        void process(TreeNode* current, vector<TreeNode*> &cParents, TreeNode* target, vector<TreeNode*> &tPath);
        void addToQueue(TreeNode* current, queue<TreeNode*> &toProcess);
        void printParents(vector<TreeNode*> &parents);
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
    vector<TreeNode*> pPath, qPath, cParents;
    vector<bool> isLeftChild;
    bool visitedRightTree = false;

    // Trivial case of emtpy tree.

    if(root == NULL)
        return NULL;

    // First add root to processing queue. Then process while queue is empty
    // until we have found both p and q. Note we allow that both p and q can be the same.

    current = root;

    // isLeftChild.back() holds whether the current node is a left child. For stopping purposes,
    // we declare the root to be a left child.
    isLeftChild.push_back(true);
    
    do {

       
       // Non-null, so process and move onto left child.
       if(current != NULL) {

            if(pPath.empty()) 
                process(current, cParents, p, pPath);
            if(qPath.empty())
                process(current, cParents, q, qPath);
            
            // Update parents info. 
            cParents.push_back(current);

            // Update info for current node.
            current = current -> left;
            isLeftChild.push_back(true);

       }
       // current is NULL, so we need to back up. Back up until current position is a left child.
       else {
          
            while(!isLeftChild.back()) {
                isLeftChild.pop_back();
                current = cParents.back();
                cParents.pop_back();
            }

            // Look at case of current being root of tree and being any other left child. Also
            // take into account if we have already visited the Right Tree.
            // Now the current is a left child. If it is not the root, then switch to the right child of parent.
            // If it is the root, then move into the right half of tree and mark that we have visited there.

            if(current != root) {
                current = cParents.back() -> right;
                isLeftChild.back() = false;
                if(cParents.back() == root)
                    visitedRightTree = true;
            }
            else if( current == root && !visitedRightTree) {
                current = root -> right;
                cParents.push_back(root);
                isLeftChild.push_back(false); 
            }

       } 
        
    } while (!cParents.empty() && (pPath.empty() || qPath.empty())); 


    // In the case that we can't find both numbers in the tree, then return a NULL result.
    if(pPath.empty() || qPath.empty())
        return NULL;

    for(int pi = pPath.size()-1; pi >-1; pi--) {
        for(int qi = qPath.size() - 1; qi > -1; qi--) {
            if(pPath[pi] -> val == qPath[qi] -> val)
                return pPath[pi]; 
        }
    }
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

void Solution::process(TreeNode* current, vector<TreeNode*> &cParents, TreeNode* target, vector<TreeNode*> &tPath) {

    if( current -> val == target -> val ) {
        tPath = cParents;
        tPath.push_back(current);
    }
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
