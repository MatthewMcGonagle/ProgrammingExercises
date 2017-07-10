// Recursive solution. Should be much more simple than non-recursive version.

#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left, *right;
};

class Solution {

    public:
        bool isValidBST(TreeNode* root);

    private:
        void processSubTree(TreeNode *node, bool &isValid, int &min, int &max);
};

int main() {

    return 0;
}

bool Solution::isValidBST(TreeNode* root) {

    bool isValid;
    int min, max;
    if (root == NULL)
        return true;

    processSubTree(root, isValid, min, max);
    return isValid;
}

void Solution::processSubTree(TreeNode *node, bool &isValid, int &min, int &max) {

    int rightMin, rightMax;

    if (node -> left == NULL && node -> right == NULL) {
        isValid = true;
        min = node -> val;
        max = min; 
        
    }

    else if (node -> left != NULL && node -> right != NULL) {

       processSubTree(node -> left, isValid, min, max); 
       if(!isValid)
            return;

       processSubTree(node -> right, isValid, rightMin, rightMax);
       if(!isValid)
            return;

       if (!(max < node -> val))  
            isValid = false;

       else if (!(node -> val < rightMin)) 
            isValid = false;

       // Subtree is valid and max is actually the max of right side.
       else
            max = rightMax;

    }

    else if (node -> left != NULL) {
        processSubTree(node -> left, isValid, min, max);
        if(!isValid)
            return;
        if (!(max < node -> val))
            isValid = false;
        else
            max = node -> val;
    }

    else {
        processSubTree(node -> right, isValid, min, max);
        if(!isValid)
            return;
        if (!(node -> val < min))
            isValid = false;
        else
            min = node -> val;
    }

}
