// Solution that simply keeps track of distance for each node. This way, there is no need to use a double 
// buffering system if we do a simple breadth first search.
 
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
    int distance;
    bool addedToProcess;
    WordNode(string val) : name(val), distance(-1), addedToProcess(false) {}
};



class Solution {
    public:
       Solution() : begin(NULL), end(NULL), endDistance(-1) {}
       vector<vector<string> > findLadders(string beginWord, string endWord, vector<string>& wordList); 
       void printGraph();

    private:
        WordNode *begin, *end;
        vector<WordNode *> nodes;
        map<string, WordNode*> lookUp;
        int endDistance;
        bool inGraph(string &word);
        void makeNodes(string beginWord, vector<string> &wordList);
        void makeAdjacents();
        void findParents();
        void addAdjacents(WordNode *node, queue<WordNode*> &toProcess);
        bool needToProcessAdj(WordNode *node, WordNode *adjacent);
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

    // string beginWord("hit"), endWord("cog");
    // const char* wordsInit[] = {"hot", "dot", "dog", "lot", "log", "cog", "zzz"};
    string beginWord("red"), endWord("tax");
    const char* wordsInit[] = {"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"};
    // Solution: [["red","ted","tad","tax"],["red","ted","tex","tax"],["red","rex","tex","tax"]]
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

    if(endDistance < 0)
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

    queue<WordNode*> toProcess;
    vector<WordNode*>::iterator adjacentIt;
    WordNode *current, *adjacent;

    toProcess . push(begin);
    begin -> distance = 0;

    while(!toProcess.empty()) {

        current = toProcess.front();
        toProcess.pop();

        if(current == end) 
            endDistance = current -> distance;

        if(endDistance < 0 || current -> distance < endDistance) 
            addAdjacents(current, toProcess);
                 
    } 

}

void Solution::addAdjacents(WordNode *node, queue<WordNode*> &toProcess) {

    vector<WordNode*>::iterator adjacentIt;
    WordNode *adjacent;    

    for(adjacentIt = node -> adjacents.begin(); adjacentIt != node -> adjacents.end(); adjacentIt++) {
        adjacent = *adjacentIt;
        if(needToProcessAdj(node, adjacent)) {
            adjacent -> distance = node -> distance + 1;
            adjacent -> parentNodes . push_back(node);
            if(! adjacent -> addedToProcess) {
                toProcess.push(adjacent); 
                adjacent -> addedToProcess = true;
            }
        }
    }
}

bool Solution::needToProcessAdj(WordNode *node, WordNode *adjacent) {

    if(endDistance < 0 || (endDistance > -1 && node -> distance < endDistance)) {

        if(adjacent -> distance < 0 || node -> distance < adjacent -> distance)
            return true;
        else
            return false;
    }
    else
        return false;
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
