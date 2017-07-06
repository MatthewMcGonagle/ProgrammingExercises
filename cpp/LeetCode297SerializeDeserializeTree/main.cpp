#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<sstream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Unit {

    public:

        Unit(bool x, int y) : isNulls(x), val(y) {} 
        string str();

        bool isNulls;
        int val;
};

Unit newNullUnit() { return Unit(true, 1);}
Unit newIntUnit(int x) { return Unit(false, x);}

class Codec {
    
    public:
        
        string serialize(TreeNode* root);
        TreeNode* deserialize(string data);
    
    private:
    
        void serializeUnits(TreeNode* root, vector<Unit> &units);

};

// Functions for setting up test cases.

TreeNode* buildTree(vector<int> nums, int nullVal);
void printTree(TreeNode* root);
void deleteTree(TreeNode* root);

int main() {

    int nullVal = -100,
        numsArray[] = {1, 2, 10, 3, -100, 5, 6, 3, 1, -100, 2, 4, -100, 6};
    vector<int> nums = vector<int>(numsArray, numsArray + sizeof(numsArray) / sizeof(int));
    TreeNode *root;
    Codec codec;
    string serialization;

    root = buildTree(nums, nullVal);
    printTree(root);

    cout << "Now let's print the serialization of the tree." << endl;
    serialization = codec.serialize(root);
    cout << serialization << endl;

    deleteTree(root);
    return 0;
}

////////// Function definitions

string Unit::str() {

    ostringstream ss;
    if(isNulls)
        ss << "N";
    ss << val;
    return ss.str();
}

string Codec::serialize( TreeNode* root ) {

    ostringstream ss;
    vector<Unit> serialUnits;

    if(root == NULL)
        return string("N");
  
    serializeUnits(root, serialUnits);

    ss << serialUnits.begin() -> str();
 
    for(vector<Unit>::iterator iT = serialUnits.begin() + 1;
        iT != serialUnits.end();
        iT++) 
            ss << "," << iT -> str();

    ss << ']';
    return ss.str();
    
}

void Codec::serializeUnits(TreeNode* root, vector<Unit> &units) {

    queue<TreeNode*> toProcess;
    TreeNode* current;

    if(root == NULL)
        return;
    
    units.push_back(newIntUnit(root -> val));
    
    toProcess.push(root -> left );
    toProcess.push(root -> right );

    while(!toProcess.empty()) {

        current = toProcess.front();
        toProcess.pop();

        if(current == NULL && units.back().isNulls)
            units.back().val++;

        else if(current == NULL)
            units.push_back(newNullUnit());

        else {
            units.push_back(newIntUnit(current -> val));
            toProcess.push(current -> left);
            toProcess.push(current -> right);
        }

    }
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
