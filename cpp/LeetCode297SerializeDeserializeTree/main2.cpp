// Solution that only keeps track of null-pointers that need to be changed to a non-null value. That is, we only keep track of non-emtpy nodes. Instead of using a regular uniform separating character such as  ',' we will use ending characters either denoting a two non-empty children, only left non-empty child, only right non-empty child, or a leaf (two empty children). We can do this by using queues of pointers to pointers.
// Passes with beating 89.06% of all cpp submissions.
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<sstream>
#include<iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
    
    public:
        
        string serialize(TreeNode* root);
        TreeNode* deserialize(string data);
    
};

// Functions for setting up test cases.

TreeNode* buildTree(vector<int> nums, int nullVal);
void printTree(TreeNode* root);
void deleteTree(TreeNode* root);

int main() {

    int nullVal = -100,
        numsArray[] = {1, 2, 10, 3, -100, 5, 6, 3, 1, -100, 2, 4, -100, 6};
    vector<int> nums = vector<int>(numsArray, numsArray + sizeof(numsArray) / sizeof(int));
    TreeNode *root, *deserialized;
    Codec codec;
    string serialization;

    root = buildTree(nums, nullVal);
    printTree(root);

    cout << "Now let's print the serialization of the tree." << endl;
    serialization = codec.serialize(root);
    cout << serialization << endl;

    deserialized = codec.deserialize(serialization); 
    printTree(deserialized);

    deleteTree(root);
    deleteTree(deserialized);
    return 0;
}

////////// Function definitions

string Codec::serialize( TreeNode* root ) {

    ostringstream ss;
    queue<TreeNode*> toProcess;
    TreeNode *current;

    if(root == NULL)
        return string("]");

    toProcess.push(root);

    while(!toProcess.empty()) {

        current = toProcess.front();
        toProcess.pop();

        ss << current -> val;
        if (current -> left != NULL && current -> right != NULL){ 
            ss << 'T';
            toProcess.push(current -> left);
            toProcess.push(current -> right);
        }
        else if (current -> left != NULL) { 
            ss << 'L';
            toProcess.push(current -> left);
        }
        else if (current -> right != NULL) {
            ss << 'R';
            toProcess.push(current -> right);
        }
        else 
            ss << 'E';
        
    }

    ss << ']';

    return ss.str();   
}

TreeNode* Codec::deserialize(string data) {

    TreeNode *root, *newNode, **newParent;
    queue<TreeNode**> parents;
    stringstream ss(data);
    int val;
    char nodeType;

    if(data.size() == 0)
        return NULL;

    if(ss.peek() == ']')
        return NULL;

    // Set up the initial root.

    ss >> val;
    ss >> nodeType;
    root = new TreeNode(val);
    newNode = root;

    if (nodeType == 'T') {
        parents.push(&(newNode -> left));
        parents.push(&(newNode -> right));
    }
    else if (nodeType == 'L') 
        parents.push(&(newNode -> left));
    else if (nodeType == 'R') 
        parents.push(&(newNode -> right));

    while (ss.peek() != ']') {

        ss >> val;
        ss >> nodeType;
        
        newNode= new TreeNode(val);
        
        if(!parents.empty()) {
            newParent = parents.front();
            parents.pop();
            *newParent = newNode;
        }
        
        if (nodeType == 'T') {
            parents.push(&(newNode -> left));
            parents.push(&(newNode -> right));
        }
        else if (nodeType == 'L') 
            parents.push(&(newNode -> left));
        else if (nodeType == 'R') 
            parents.push(&(newNode -> right));

    } 

    return root;
}

TreeNode* buildTree(vector<int> nums, int nullVal) {

    TreeNode *root, *current;
    queue<TreeNode*> leafnodes;
    vector<int>::iterator iT = nums.begin() + 1;

    if (nums.size() == 0)
        return NULL;

    root = new TreeNode(nums[0]);
    leafnodes.push(root);

    while(iT != nums.end()) {

        current = leafnodes.front();
        leafnodes.pop();

        if(*iT != nullVal) {
            current -> left = new TreeNode(*iT);
            leafnodes.push(current -> left);
        }
        iT++;

        if(iT != nums.end()) {
       
            if(*iT != nullVal) { 
                current -> right = new TreeNode(*iT);
                leafnodes.push(current -> right);
            }
            iT++;
        } 
    }

    return root;
    
}

void printTree(TreeNode* root) {

    // Use two queues. At any given time one queue holds nodes to print on current
    // level while other holds values on next level.

    queue<TreeNode*> toPrintA, toPrintB;
    queue<TreeNode*> *toPrintNow, *toPrintNext, *swapper;
    TreeNode* current;

    if(root == NULL) {
        cout << "NULL";
        return;
    }

    toPrintNow = &toPrintA;
    toPrintNext = &toPrintB;    
    toPrintNow -> push(root);

    while(!toPrintNow -> empty()) {

        current = toPrintNow -> front();
        toPrintNow -> pop();

        if(current == NULL)
            cout << "NULL, ";
        else {
            cout << current -> val << ", ";
            toPrintNext -> push(current -> left);
            toPrintNext -> push(current -> right);
        }

        if(toPrintNow -> empty()) {
            // Swap pointer values.
            swapper = toPrintNow;
            toPrintNow = toPrintNext;
            toPrintNext = swapper;
            cout << endl; 
        }

    } 
    
}

void deleteTree(TreeNode* root) {

    queue<TreeNode*> toDelete;
    TreeNode *current;

    if(root == NULL)
        return;
    
    toDelete.push(root);
    while(!toDelete.empty()) {
        
        current = toDelete.front();
        toDelete.pop();

        if ( current -> left != NULL )
            toDelete.push( current -> left );
        if ( current -> right != NULL )
            toDelete.push( current -> right );
        
        delete current;
    }
}
