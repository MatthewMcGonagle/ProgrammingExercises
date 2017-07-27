// Use two copies of a map between the old pointers and the new pointers.

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
        
};

UndirectedGraphNode* buildGraph(string symbols); 
void printGraph(UndirectedGraphNode *node);

int main() {

    string symbols("0,1,2#1,2#2,2");
    Solution s;
    UndirectedGraphNode *node;

    cout << "Symbols = " << symbols << endl;
    node = buildGraph(symbols);
    printGraph(node);
 
    return 1;

}

UndirectedGraphNode* cloneGraph(UndirectedGraphNode *node) {

}

UndirectedGraphNode* Solution::allocateNewNodes(UndirectedGraphNode* node) {

    queue<UndirectedGraphNode*> toProcess;
    UndirectedGraphNode *current, *newNode;
    map<UndirectedGraphNode*, UndirectedGraphNode*>::iterator mapIt;
    pair<UndirectedGraphNode*, UndirectedGraphNode*> mapPair;
    vector<UndirectedGraphNode*>::iterator nbrIt;

    if (node == NULL)
        return NULL;

    toProcess.push(node);

    while(!toProcess.empty()) {

        current = toProcess.front();
        toProcess.pop();

        newNode = new UndirectedGraphNode(current -> label);
        mapPair = pair<UndirectedGraphNode*, UndirectedGraphNode*>(current, newNode);
        pointerMap.insert(mapPair); 
   
        for(nbrIt = current -> neighbors . begin(); nbrIt != current -> neighbors . end(); nbrIt++) {
            mapIt = pointerMap.find(*nbrIt);
            if(mapIt != pointerMap.end())
                toProcess.push(*nbrIt);
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

    if (node == NULL)
        cout << "node is NULL" << endl;

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
