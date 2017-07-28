// When allocating the clone nodes, simply push the clone pointer to the back of originals neighbors, and then
// store pointer to the original in the front of the clone's neighbors.
// Do one final pass to fix the neighbors in each.

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <stdlib.h>
#include <set>

using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};

};

class Solution {

    public:
        
        UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node); 

    private:

        map<UndirectedGraphNode*, UndirectedGraphNode*> pointerMap;
        UndirectedGraphNode* allocateNewNodes(UndirectedGraphNode* node);
        void setNeighbors(UndirectedGraphNode* clone);
        void fixNeighborsClone(UndirectedGraphNode* clone);
        void fixNeighborsOriginal(UndirectedGraphNode* original);
        void pushNeighbors(vector<UndirectedGraphNode*> &neighbors, 
                           queue<UndirectedGraphNode*> &toProcess,
                           set<UndirectedGraphNode*> &dontAdd);
        
};

UndirectedGraphNode* buildGraph(string symbols); 
void printGraph(UndirectedGraphNode *node);
void multiplyGraph(UndirectedGraphNode *node, int scaling);

int main() {

    string symbols("0,1,2#1,2#2,2");
    Solution s;
    UndirectedGraphNode *node, *clone;

    cout << "Symbols = " << symbols << endl;
    node = buildGraph(symbols);

    cout << "Original Graph is " << endl;
    printGraph(node);
    
    clone = s.cloneGraph(node);
    multiplyGraph(node, 10);

    cout << "Multiplied graph is " << endl;
    printGraph(node);
    cout << "Cloned original is " << endl;
    printGraph(clone);
 
    return 1;

}

UndirectedGraphNode* Solution::cloneGraph(UndirectedGraphNode *node) {

    UndirectedGraphNode *cloneNode;

    if(node == NULL)
        return NULL;

    cloneNode = allocateNewNodes(node);
    setNeighbors(cloneNode);
    fixNeighborsClone(cloneNode);
    fixNeighborsOriginal(node);

    return cloneNode;
}

UndirectedGraphNode* Solution::allocateNewNodes(UndirectedGraphNode* original) {

    queue<UndirectedGraphNode*> toProcess;
    UndirectedGraphNode *newNode,  *result;
    vector<UndirectedGraphNode*>::iterator nbrIt;
    set<UndirectedGraphNode*> addedToQueue;
    bool firstNode = true;

    toProcess.push(original);
    addedToQueue.insert(original);

    while(!toProcess.empty()) {

        original = toProcess.front();
        toProcess.pop();

        newNode = new UndirectedGraphNode(original -> label);
        newNode -> neighbors . push_back(original);

        if(firstNode) {
            
            result = newNode;
            firstNode = false;

        }  

        pushNeighbors(original -> neighbors, toProcess, addedToQueue);
        original -> neighbors . push_back(newNode);


    }

    return result; 
    
}

void Solution::setNeighbors(UndirectedGraphNode* clone) {

    set<UndirectedGraphNode*> addedToQueue;
    queue<UndirectedGraphNode *> toProcess;
    vector<UndirectedGraphNode*>::iterator origNbrIt;
    UndirectedGraphNode *original, *cloneNbr;

    toProcess.push(clone);
    addedToQueue.insert(clone);

    while(!toProcess.empty()) {

        clone = toProcess.front();
        toProcess.pop();

        original = *(clone -> neighbors . begin());

        for (origNbrIt = original -> neighbors . begin(); origNbrIt != original -> neighbors.end() - 1; origNbrIt++) {

            cloneNbr = *((*origNbrIt) -> neighbors . end() - 1);
            clone -> neighbors.push_back(cloneNbr);
            if(addedToQueue.count(cloneNbr) == 0) {
                toProcess.push(cloneNbr);
                addedToQueue.insert(cloneNbr);
            }
            
        } 
          
    }
}

void Solution::fixNeighborsClone(UndirectedGraphNode* clone) {

    set<UndirectedGraphNode*> addedToQueue;
    queue<UndirectedGraphNode*> toProcess;

    toProcess.push(clone);
    addedToQueue.insert(clone);

    while(!toProcess.empty()) {

        clone = toProcess.front();
        toProcess.pop();
        clone -> neighbors.erase(clone -> neighbors . begin());
        pushNeighbors(clone -> neighbors, toProcess, addedToQueue);

    }
}

void Solution::fixNeighborsOriginal(UndirectedGraphNode* original) {

    set<UndirectedGraphNode*> addedToQueue;
    queue<UndirectedGraphNode*> toProcess;

    toProcess.push(original);
    addedToQueue.insert(original);

    while(!toProcess.empty()) {

        original = toProcess.front();
        toProcess.pop();
        original -> neighbors.erase(original -> neighbors . end() - 1);
        pushNeighbors(original -> neighbors, toProcess, addedToQueue);

    }

}

void Solution::pushNeighbors(vector<UndirectedGraphNode*> &neighbors, 
                           queue<UndirectedGraphNode*> &toProcess,
                           set<UndirectedGraphNode*> &dontAdd) {

    vector<UndirectedGraphNode*>::iterator nbrIt;

    for(nbrIt = neighbors.begin(); nbrIt != neighbors.end(); nbrIt++) {
    
         if(dontAdd.count(*nbrIt) == 0) {
             toProcess.push(*nbrIt);
             dontAdd.insert(*nbrIt);
         }
    } 
}

UndirectedGraphNode* buildGraph(string symbols) {

    string::iterator charIt, beginNumIt = symbols.begin();
    int num, nbrIndex;
    vector<UndirectedGraphNode*> nodes;
    vector<vector<int> > neighbors;
    vector<int>::iterator nbrIt;
    map<int, int> labelToIndex;
    map<int, int>::iterator mapIt;
    pair<int, int> key;
    bool findingNodeLabel = true;
    UndirectedGraphNode* current;

    // Need to put in trivial case of symbols size is 1.

    // Now handle case of non-trivial symbols size is atleast 2.

    for(charIt = symbols.begin(); charIt != symbols.end(); charIt++) {

        if(*charIt == ',' || *charIt == '#') {

            num = atoi(string(beginNumIt, charIt).c_str()); 
            if (findingNodeLabel) {
                current = new UndirectedGraphNode(num); 
                key = pair<int, int> (num, nodes.size());
                labelToIndex.insert(key);
                nodes.push_back(current);
                neighbors.push_back(vector<int>(0));
            }
            else {
                (neighbors.end() - 1) -> push_back(num);
            }
            
            if(*charIt == ',')
                findingNodeLabel = false;
            else
                findingNodeLabel = true;

            beginNumIt = charIt + 1;
        }

    } 

    // Another number to process for when we reach the end of the string.
    num = atoi(string(beginNumIt, charIt).c_str()); 
    cout << num << ", ";
    if (findingNodeLabel) {
        current = new UndirectedGraphNode(num); 
        key = pair<int, int> (num, nodes.size());
        labelToIndex.insert(key);
        nodes.push_back(current);
        neighbors.push_back(vector<int>(0));
    }
    else {
        (neighbors.end() - 1) -> push_back(num);
    }

    // Now set up neighbors.
    for(mapIt = labelToIndex.begin(); mapIt != labelToIndex.end(); mapIt++) {
    
        current = nodes[mapIt -> second];
        for(nbrIt = neighbors[mapIt -> first].begin(); nbrIt != neighbors[mapIt -> first].end(); nbrIt++) {
            nbrIndex = labelToIndex.find(*nbrIt) -> second;
            current -> neighbors.push_back(nodes[nbrIndex]);
        }
    }

    return *(nodes.begin());

}


void printGraph(UndirectedGraphNode *node) {

    queue<UndirectedGraphNode *> toPrint;
    set<UndirectedGraphNode*> alreadyPrinted;
    UndirectedGraphNode* current;
    vector<UndirectedGraphNode*>::iterator nbrIt;

    if (node == NULL) {
        cout << "node is NULL" << endl;
        return;
    }

    toPrint.push(node);
    alreadyPrinted.insert(current);

    while(!toPrint.empty()) {

        current = toPrint.front();
        toPrint.pop(); 

        cout << "Node " << current -> label << endl
             << "Neighbors <- ";

        for(nbrIt = current -> neighbors.begin(); nbrIt != current -> neighbors.end(); nbrIt++) {

            cout << (*nbrIt) -> label << ", ";
            
            if(alreadyPrinted.count(*nbrIt) == 0){
                toPrint.push(*nbrIt);
                alreadyPrinted.insert(*nbrIt);
            }
        }
        cout << endl;
    }
    cout << endl;
}

void multiplyGraph(UndirectedGraphNode *node, int scaling) {

    queue<UndirectedGraphNode *> toScale;
    set<UndirectedGraphNode*> alreadyScaled;
    UndirectedGraphNode* current;
    vector<UndirectedGraphNode*>::iterator nbrIt;

    if (node == NULL)
        cout << "node is NULL" << endl;

    toScale.push(node);
    alreadyScaled.insert(current);

    while(!toScale.empty()) {

        current = toScale.front();
        toScale.pop(); 

        current -> label *= scaling;
        for(nbrIt = current -> neighbors.begin(); nbrIt != current -> neighbors.end(); nbrIt++) {

            if(alreadyScaled.count(*nbrIt) == 0){
                toScale.push(*nbrIt);
                alreadyScaled.insert(*nbrIt);
            }
        }
        cout << endl;
    }
    cout << endl;

}
