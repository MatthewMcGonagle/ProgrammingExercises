// Implement solution using node creation and insertion.

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
    public:
        RandomListNode* copyRandomList(RandomListNode *head);

        RandomListNode* constructRandomList(vector<int> labelList, vector<int> indexList);
        void printRandomList(RandomListNode *head);
        void deleteRandomList(RandomListNode *head);
};

int main() {

    int labelList[] = {0, 1, 2, 3, 4, 5, 6, 7},
        indexList[] = {1, 2, 3, 4, 5, 6, 7, -1};
    vector<int> labelVector(labelList, labelList + sizeof(labelList) / sizeof(int)),
                indexVector(indexList, indexList + sizeof(indexList) / sizeof(int));
    vector<int>::iterator labelIt, indexIt;

    RandomListNode *head, *copyHead;

    Solution s;

    // Construct Random Linked List using the vectors of labels and indices.

    cout << "labelVector = " << endl << "    ";
    for(labelIt = labelVector.begin(), indexIt = indexVector.begin(); labelIt!= labelVector.end(); labelIt++, indexIt++) {

        cout << "(" << *labelIt << ", " << *indexIt << "),    ";
    } 
    cout << endl;

    head = s.constructRandomList(labelVector, indexVector);
    cout << "Random List = " << endl << "     ";
    s.printRandomList(head);

    // Copy Random List
    
    copyHead = s.copyRandomList(head);
    cout << "Copy of Random List = " << endl << "      ";
    s.printRandomList(copyHead);
    cout << "After copying, original Random List = " << endl << "       ";
    s.printRandomList(head);

    s.deleteRandomList(head);
    cout << "Successfully deleted head" << endl;
    s.deleteRandomList(copyHead);
    cout << "Successfully deleted copyHead" << endl;
    return 0;
}

RandomListNode* Solution::copyRandomList(RandomListNode *head) {

    RandomListNode *newhead, *oldCurrent, *newCurrent;

    if(head == NULL)
        return NULL;

    // First pass to weave in new nodes amongst the old nodes. Alternates old -> new -> old -> new -> ...
    oldCurrent = head;

    while(oldCurrent != NULL) {

        newCurrent = new RandomListNode(oldCurrent -> label);
    
        // Switch original next pointer with address of new current node. Also, new node currently
        // has a copy of old random pointer.
        newCurrent -> next = oldCurrent -> next;
        newCurrent -> random = oldCurrent -> random;

        oldCurrent -> next = newCurrent; 

        // Now move to original next as recorded in the new node. 
        oldCurrent = newCurrent -> next;
    }

    // Now set up new random pointers.

    oldCurrent = head;
    while(oldCurrent != NULL) {

        // New random is successor of original random.
        newCurrent = oldCurrent -> next;
        if(newCurrent -> random != NULL)
            newCurrent -> random = newCurrent -> random -> next;

        oldCurrent = oldCurrent -> next -> next;

    }

    // Now separate old and new nodes. Also restore old nodes next field to original values.
    // newCurrent records the previous node in the new list.

    oldCurrent = head;
    newhead = oldCurrent -> next;
    newCurrent = newhead;
    oldCurrent -> next = newCurrent -> next;
    oldCurrent = newCurrent -> next;

    while(oldCurrent != NULL) {
        newCurrent -> next = oldCurrent -> next;
        newCurrent = newCurrent -> next;

        oldCurrent -> next = newCurrent -> next;
        oldCurrent = oldCurrent -> next;
    }

    return newhead;
}

RandomListNode* Solution::constructRandomList(vector<int> labelList, vector<int> indexList) {

    RandomListNode *head, *current;
    vector<int>::iterator labelIt, indexIt;
    vector<RandomListNode*> addressList;
    vector<RandomListNode*>::iterator addressIt;

    if(labelList.size() == 0 || labelList.size() != indexList.size())
        return NULL;

    addressList = vector<RandomListNode*>(labelList.size());
    head = new RandomListNode(labelList[0]);
    current = head;
    addressList[0] = head;
    
    for( labelIt = labelList.begin() + 1, addressIt = addressList.begin() + 1
       ; labelIt != labelList.end(); labelIt++, addressIt++) {
       
       current -> next = new RandomListNode(*labelIt);
       current = current -> next; 
       *addressIt = current;
        
    }

    current = head;
    for( indexIt = indexList.begin(); indexIt != indexList.end(); indexIt++) {
    
        if(*indexIt < 0)
            current -> random = NULL;
        else
            current ->  random = addressList[*indexIt];

        current = current -> next;

    }
    
    return head;

}

void Solution::printRandomList(RandomListNode *node) {

    if(node == NULL) {
        cout << "Head node is NULL" << endl;
        return;
    }

    while(node != NULL) {
    
        cout << "(" << node -> label << ", ";
        if(node -> random != NULL)
            cout << node -> random -> label;
        else
            cout << "NULL";
        cout << "),     ";
        node = node -> next;
    }
    cout << "FINISHED" << endl;

}

void Solution::deleteRandomList(RandomListNode *node) {

    RandomListNode *toDelete;

    while(node != NULL) {
        toDelete = node;
        node = node -> next;
        delete toDelete;
    }
}
