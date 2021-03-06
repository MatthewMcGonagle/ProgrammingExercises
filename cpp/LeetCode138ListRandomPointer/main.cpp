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

    s.deleteRandomList(head);
    s.deleteRandomList(copyHead);
    return 0;
}

RandomListNode* Solution::copyRandomList(RandomListNode *head) {

    RandomListNode *newhead, *currentOld, *currentNew, *currentChild;
    map<RandomListNode*, RandomListNode*> addressMap;
    pair<RandomListNode*, RandomListNode*> addressConversion;

    if(head == NULL)
        return NULL;

    // Now know that head is non-null. Initialize list without random pointer. For now, set random pointer to address in original list. Also set up address map.

    newhead = new RandomListNode(head -> label);
    currentOld = head;
    currentNew = newhead;
    currentNew -> random = currentOld -> random;
    addressConversion = pair<RandomListNode*, RandomListNode*> (currentOld, currentNew);
    addressMap.insert(addressConversion);

    while(currentOld -> next != NULL) {
        currentChild = new RandomListNode(currentOld -> next -> label);
        currentNew -> next = currentChild; 
        currentNew = currentChild;
        currentOld = currentOld -> next;

        currentNew -> random = currentOld -> random;
        addressConversion = pair<RandomListNode*, RandomListNode*> (currentOld, currentNew);
        addressMap.insert(addressConversion);
    }

    // Now add in random pointers.

    currentNew = newhead;
    while(currentNew != NULL) {
        if(currentNew -> random != NULL) {
            addressConversion = *addressMap.find(currentNew -> random);
            currentNew -> random = addressConversion.second;
        }
        currentNew = currentNew -> next;
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
    cout << endl;

}

void Solution::deleteRandomList(RandomListNode *node) {

    RandomListNode *toDelete;

    while(node != NULL) {
        toDelete = node;
        node = node -> next;
        delete toDelete;
    }
}
