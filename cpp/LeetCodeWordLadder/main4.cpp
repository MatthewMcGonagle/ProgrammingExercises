#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct nodeInfo {
    string* word;
    nodeInfo* beginParent;
    nodeInfo* endParent;
};

class Solution {
    public:
        int ladderLength(string beginWord, string endWord, vector<string>& wordList);
        int stringDistance(string* x, string* y);

    private:

        void possiblyAddToGraph(nodeInfo* inGraph, nodeInfo* target);
        bool addWhenClose(nodeInfo* inGraph, nodeInfo* target, nodeInfo **parent);
        int traceDistance();
        queue<nodeInfo*> toProcess;
        nodeInfo* midpoint;
};

int main() {
    string wordArray[] = {"hot", "dot", "dog", "lot", "log", "cog"};
    //string wordArray[] = {"a", "b", "c"};
    vector<string> wordList(wordArray, wordArray + 6);
    Solution s;
    int chainlength;

    cout << "The word list is {";
    for (int i = 0; i < wordList.size() - 1; i++)
        cout << wordList[i] << ", ";
    cout << wordList[wordList.size()-1];
    cout << "}" << endl;

    chainlength = s.ladderLength(string("hit"), string("cog"), wordList);
    //chainlength = s.ladderLength(string("a"), string("c"), wordList);
    cout << "ladder length = " << chainlength << endl;

    return 0;
}

int Solution::ladderLength(string beginWord, string endWord, vector<string>& wordList) {

    int stringDistance;
    vector<nodeInfo> nodeList(wordList.size());
    vector<nodeInfo>::iterator nodeIt;
    vector<string>::iterator wordIt;
    nodeInfo swapper, begin, dummy, *current;
    bool foundBegin, foundEnd;

    // Initialize node info list. Search for beginWord and endWord in the list. When encountering either, 
    // add it to the processing queue.

    toProcess = queue<nodeInfo*>();
    foundBegin = false;
    foundEnd = false;
    for(nodeIt = nodeList.begin(), wordIt = wordList.begin(); nodeIt != nodeList.end(); nodeIt++, wordIt++) {
        nodeIt -> word = &*wordIt; 
        nodeIt -> beginParent = NULL;
        nodeIt -> endParent = NULL;

        if(*wordIt == endWord) {
            toProcess.push(&*nodeIt);
            nodeIt -> endParent = &dummy;
            foundEnd = true;        
        }
        else if(*wordIt == beginWord) {
            toProcess.push(&*nodeIt);
            nodeIt -> beginParent = &dummy;
            foundBegin = true;
        }
        
    }

    // If endWord wasn't found in list then return failure with length 0.

    if(!foundEnd)
        return 0;

    // If beginning word wasn't found, then it isn't in wordList. This is okay. We 
    // just need to set up an external node for it. 
    // Also set up dummy node pointed to by beginning and end nodes.
    
    if(!foundBegin) {
        begin.word = &beginWord;
        begin.beginParent = &dummy;
        begin.endParent = NULL;

        toProcess.push(&begin);
    }

    dummy.word = NULL;
    dummy.beginParent = NULL;
    dummy.endParent = NULL;
    
    // Now start processing until empty or found.

    midpoint = NULL;
    while(!toProcess.empty() && midpoint == NULL) {

        current = toProcess.front();
        toProcess.pop();

        for(nodeIt = nodeList.begin(); nodeIt != nodeList.end() && midpoint == NULL; nodeIt++) 
           possiblyAddToGraph(current, &*nodeIt); 
    }

    if( midpoint == NULL)
        return 0;
    else
        // Number of vertices is one more than the length from start to end.
        return 1 + traceDistance();
        
}

void Solution::possiblyAddToGraph(nodeInfo *inGraph, nodeInfo *target) {

    bool targetAdded;

    if(inGraph -> beginParent != NULL && target -> beginParent == NULL) {

        targetAdded = addWhenClose(inGraph, target, &(target -> beginParent));
        if( targetAdded ) { 
            if(target -> endParent != NULL) {
                midpoint = target;
            }         
        } 
    }

    else if (inGraph -> endParent != NULL && target -> endParent == NULL) {
        targetAdded = addWhenClose(inGraph, target, &(target -> endParent));
        if ( targetAdded) {
            if(target -> beginParent != NULL) {
                midpoint = target;
            }
        } 
        
    }

}

bool Solution::addWhenClose(nodeInfo *inGraph, nodeInfo *target, nodeInfo **targetParent) {
    if(stringDistance(inGraph -> word, target -> word) == 1) {
        toProcess.push(target);
        *targetParent = inGraph;
        return true;
    }
    else
        return false;
}

int Solution::traceDistance() {
    nodeInfo* current;
    int distance = 0;

    current = midpoint;
    while(current != NULL) {
        current = current -> beginParent;
        distance++;
    }

    current = midpoint;
    while(current != NULL) {
       current = current -> endParent;
       distance++;
    }

    // Will count dummy edges that we artificially added. We also count two edges for both times we
    // we move from the dummy to its NULL parent (once for beginnning and once for end). So we subtract 
    // four total.

    return distance - 4; 
}

int Solution::stringDistance(string* x, string* y) {

    int numdifference = 0;
    string::iterator xIt, yIt;

    for(xIt = x -> begin(), yIt = y -> begin(); xIt != x -> end(); xIt++, yIt++)
        if(*xIt != *yIt)
            numdifference++;

    return numdifference;
}
