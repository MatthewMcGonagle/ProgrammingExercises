// Will construct the graph and a map between the keys and the nodes.

#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<stack>
#include<queue>

using namespace std;

struct WordNode {

    string name;
    vector<WordNode*> adjacents, parentNodes;
    bool processed, addedToNext;
    bool wasInCurrent;
    WordNode(string val) : name(val), processed(false), addedToNext(false), wasInCurrent(false) {}
};



class Solution {
    public:
       Solution() : begin(NULL), end(NULL), endFound(false) {}
       vector<vector<string> > findLadders(string beginWord, string endWord, vector<string>& wordList); 
       void printGraph();

    private:
        WordNode *begin, *end;
        vector<WordNode *> nodes;
        map<string, WordNode*> lookUp;
        bool endFound;
        bool inGraph(string &word);
        void makeNodes(string beginWord, vector<string> &wordList);
        void makeAdjacents();
        void findParents();
        void findPaths(WordNode *finalNode, vector<vector<string> > &result);
};

// Debug Functions

void myPrint(WordNode *node) {

    vector<WordNode*>::iterator nodeIt;
    WordNode *otherNode;

    cout << node -> name << endl
         << "Adjacents -> ";
    for(nodeIt = node -> adjacents . begin(); nodeIt != node -> adjacents . end(); nodeIt++) {
        otherNode = *nodeIt; 
        cout << otherNode -> name << ", "; 
    }
    cout << endl
         << "Parents <- ";
    for(nodeIt = node -> parentNodes. begin(); nodeIt != node -> parentNodes. end(); nodeIt++) {
        otherNode = *nodeIt;
        cout << otherNode -> name << ", ";
    }
    cout << endl;
}

void myPrint(vector<WordNode*> &nodes) {

    vector<WordNode*>::iterator nodeIt, adjIt, parIt;
    
    for(nodeIt = nodes.begin(); nodeIt != nodes.end(); nodeIt++) { 
        myPrint(*nodeIt);
        cout << endl;
    }
    cout << endl;
}


int main() {

    string beginWord("hit"), endWord("cog");
    const char* wordsInit[] = {"hot", "dot", "dog", "lot", "log", "cog", "zzz"};
    vector<string> words(wordsInit, wordsInit + sizeof(wordsInit) / sizeof(char*));
    vector<string>::iterator wordIt;
    vector<vector<string> > paths;
    vector<vector<string> >::iterator pathsIt;

    Solution s;

    for(wordIt = words.begin(); wordIt != words.end(); wordIt++)
        cout << *wordIt << ", ";
    cout << endl;

    paths = s.findLadders( beginWord, endWord, words);
    s.printGraph();

    cout << endl << "The paths are: " << endl;
    for(pathsIt = paths.begin(); pathsIt != paths.end(); pathsIt++) {
        for(wordIt = pathsIt -> begin(); wordIt != pathsIt -> end(); wordIt++)
            cout << *wordIt << " -> ";
        cout << endl;
    }
    return 1;

}

vector<vector<string> > Solution::findLadders(string beginWord, string endWord, vector<string>& wordList) {

    vector<vector<string> > paths;
    map<string, WordNode*>::iterator lookUpIt;
    
    if(wordList.empty())
        return paths;

    makeNodes(beginWord, wordList);
    lookUpIt = lookUp.find(endWord);
    end = lookUpIt -> second;

    makeAdjacents();
    findParents();

    // If no connecting path was found, then return empty list.

    if(!endFound)
        return vector<vector<string> >(0);

    findPaths(end, paths);
    
    return paths;
}

void Solution::printGraph() {

    myPrint(nodes);

    cout << "Begin = " << begin -> name << endl
         << "End = " << end -> name << endl;
}

bool Solution::inGraph(string &word) {

    map<string, WordNode*>::iterator lookUpIt;
    
    lookUpIt = lookUp.find(word);
    return (lookUpIt != lookUp.end());
}

void Solution::makeNodes(string beginWord, vector<string> &wordList) {

    WordNode *newNode;
    vector<string>::iterator wordIt;    
    map<string, WordNode*>::iterator lookUpIt;

    for(wordIt = wordList.begin(); wordIt != wordList.end(); wordIt++) 

        if(!inGraph(*wordIt)) {

            newNode = new WordNode(*wordIt);
            nodes.push_back(newNode);
            lookUp.insert(pair<string, WordNode*> (*wordIt, newNode));
        }

    // If the beginning word isn't in the word list, then we need to add it.    

    lookUpIt = lookUp . find (beginWord);
    if (lookUpIt == lookUp.end()) {
        begin = new WordNode(beginWord);
        nodes.push_back(begin);
        lookUp.insert(pair<string, WordNode*> (beginWord, begin));
    }
    else
        begin = lookUpIt -> second;
        
}

void Solution::makeAdjacents() {

    vector<WordNode*>::iterator nodesIt; 
    map<string, WordNode*>::iterator lookUpIt;
    string word, testWord;
    string::iterator charIt;
    char origChar;

    for(nodesIt = nodes.begin(); nodesIt != nodes.end(); nodesIt++) {

        word = (*nodesIt) -> name;
        for(charIt = word.begin(); charIt != word.end(); charIt++) {
            origChar = *charIt;
            for(char newChar = 'a'; newChar < origChar; newChar++) {
                *charIt = newChar;
                lookUpIt = lookUp.find(word);
                if(lookUpIt != lookUp.end()) 
                    (*nodesIt) -> adjacents . push_back (lookUpIt -> second);
            } 
            for(char newChar = origChar + 1; newChar <= 'z'; newChar++) {
                *charIt = newChar;
                lookUpIt = lookUp.find(word);
                if(lookUpIt != lookUp.end()) 
                    (*nodesIt) -> adjacents . push_back (lookUpIt -> second);
            }
                 
            *charIt = origChar;
        } 
    }
}

void Solution::findParents() {

    queue<WordNode*> processBuffer1, processBuffer2, 
                     *toProcessCurrent = &processBuffer1, *toProcessNext = &processBuffer2,
                     *switcher,
                     toMark;
    WordNode *current, *neighbor;
    vector<WordNode*>::iterator adjIt;
    bool pathsFound = false;
    endFound = false;
   
    toProcessCurrent -> push(begin); 
    begin -> wasInCurrent = true;

    // Everything in current buffer should have wasInCurrent marked as true.

    while(!pathsFound && !toProcessCurrent -> empty()) {

        current = toProcessCurrent -> front();
        toProcessCurrent -> pop();

        if (current == end)
            endFound = true;

        // Only add to processing queues if we haven't found the end yet

        for (adjIt = current -> adjacents.begin(); adjIt != current -> adjacents.end(); adjIt++) { 
            neighbor = *adjIt;
            if( ! neighbor -> wasInCurrent) { 
                neighbor -> parentNodes.push_back(current);
                if (! neighbor -> addedToNext ) {
                    toProcessNext -> push(neighbor);
                    toMark .  push(neighbor);
                    neighbor -> addedToNext = true;
                }

            }
            
        }
 
        // Check if we need to switch buffers.

        if(toProcessCurrent -> empty() && !toProcessNext -> empty()) { 
            while(!toMark.empty()) {
                current = toMark.front();
                toMark.pop();
                current -> wasInCurrent = true;
            }

            switcher = toProcessCurrent;
            toProcessCurrent = toProcessNext;
            toProcessNext = switcher;

            if(endFound)
                pathsFound = true;
        }
    } 
    
    
}


// Use a depth first search of parent tree.

void Solution::findPaths(WordNode *finalNode, vector<vector<string> > &result) {

    vector<vector<string> > subpaths;    
    vector<vector<string> >::iterator pathIt;
    vector<string> path;
    vector<WordNode*>::iterator parentIt;
    WordNode *parent;
 
    // Trivial case of no parents.

    if(finalNode -> parentNodes.empty()) {
        path = vector<string>(1, finalNode -> name);
        result = vector<vector<string> >(1, path);
        return;
    } 

    for(parentIt = finalNode -> parentNodes . begin(); parentIt != finalNode -> parentNodes.end(); parentIt++) {

        parent = *parentIt;
        subpaths = vector<vector<string> >(0);
        findPaths(parent, subpaths);
        for(pathIt = subpaths.begin(); pathIt != subpaths.end(); pathIt++) {
            pathIt -> push_back(finalNode -> name);
            result . push_back(*pathIt);
        }
    } 
}
