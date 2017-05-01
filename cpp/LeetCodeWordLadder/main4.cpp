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
        int distance(string* x, string* y);

    private:

        void possiblyAddToGraph(nodeInfo* inGraph, nodeInfo* target);
        int traceDistance();
        queue<nodeInfo*> toProcess;
        bool found;
        nodeInfo* midpoint;
};

int main() {
    string wordArray[] = {"hot", "dot", "dog", "lot", "log", "cog"};
    vector<string> wordList(wordArray, wordArray + 6);
    Solution s;
    int chainlength;

    cout << "The word list is {";
    for (int i = 0; i < wordList.size() - 1; i++)
        cout << wordList[i] << ", ";
    cout << wordList[wordList.size()-1];
    cout << "}" << endl;

    chainlength = s.ladderLength(string("hit"), string("cog"), wordList);
    cout << "ladder length = " << chainlength << endl;

    return 0;
}

int Solution::ladderLength(string beginWord, string endWord, vector<string>& wordList) {

    int beginDistance, endDistance, stringDistance;
    vector<nodeInfo> nodeList(wordList.size());
    vector<nodeInfo>::iterator nodeIt;
    vector<string>::iterator wordIt;
    nodeInfo swapper, begin, end, dummy, *current;

    // Initialize node info list.

    for(nodeIt = nodeList.begin(), wordIt = wordList.begin(); nodeIt != nodeList.end(); nodeIt++, wordIt++) {
        nodeIt -> word = &*wordIt; 
        nodeIt -> beginParent = NULL;
        nodeIt -> endParent = NULL;
    }

    // Set up begin info and end info. For processing purposes, begin info and end info point to a dummy node.
    begin.word = &beginWord;
    begin.beginParent = &dummy;
    begin.endParent = NULL;

    end.word = &endWord;
    end.beginParent = NULL;
    end.endParent = &dummy; 

    dummy.word = NULL;
    dummy.beginParent = NULL;
    dummy.endParent = NULL;
    
    // First put beginWord and endWord into processing queue.
    toProcess = queue<nodeInfo*>();
    toProcess.push(&begin);
    toProcess.push(&end);

    // Now start processing until empty or found.

    found = false;
    beginDistance = 0;
    endDistance = 0;
    midpoint = NULL;
    while(!toProcess.empty() && !found) {

        current = toProcess.front();
        toProcess.pop();

        for(nodeIt = nodeList.begin(); nodeIt != nodeList.end(); nodeIt++) 
           possiblyAddToGraph(current, &*nodeIt); 
    }

    if( midpoint == NULL)
        return 0;
    else
        return traceDistance();
        
}

void Solution::possiblyAddToGraph(nodeInfo *inGraph, nodeInfo *target) {
    nodeInfo **inGraphParent, **foundParent;
    int *distanceToUpdate;
    if(inGraph -> beginParent != NULL && target -> beginParent == NULL) {
        inGraphParent = & (target -> beginParent);
        foundParent = & (target -> endParent);
    }
    else if (inGraph -> endParent != NULL && target -> endParent == NULL) {
        inGraphParent = & (target -> endParent);
        foundParent = & (target -> beginParent);
    }
    else
        return;

    if(distance( inGraph -> word, target -> word)) {
        *inGraphParent = inGraph;
        toProcess.push(target);
        if(*foundParent != NULL) {
            found = true;
            midpoint = target;
        }
    }

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

    return distance - 2; // Will count dummy edges that we artificially added.
}

int Solution::distance(string* x, string* y) {

    int numdifference = 0;
    string::iterator xIt, yIt;

    for(xIt = x -> begin(), yIt = y -> begin(); xIt != x -> end(); xIt++, yIt++)
        if(*xIt != *yIt)
            numdifference++;

    return numdifference;
}
