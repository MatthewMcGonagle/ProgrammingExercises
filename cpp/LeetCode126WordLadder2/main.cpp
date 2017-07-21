// Will construct the graph and a map between the keys and the nodes.

#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<stack>

using namespace std;

struct WordNode {

    string name;
    vector<WordNode*> adjacents;
    WordNode(string val) : name(val) {}
};

class Solution {
    public:
       Solution() : begin(NULL), end(NULL) {}
       vector<vector<string> > findLadders(string beginWord, string endWord, vector<string>& wordList); 

    private:
        WordNode *begin, *end;
        vector<WordNode *> nodes;
        map<string, WordNode*> lookUp;
        bool inGraph(string &word);
        void makeNodes(vector<string> &wordList);
        void makeAdjacents();
};

int main() {

    string beginWord("hot"), endWord("dog");
    const char* wordsInit[] = {"hot", "dot", "dog", "lot", "log", "cog"};
    vector<string> words(wordsInit, wordsInit + sizeof(wordsInit) / sizeof(char*));
    vector<string>::iterator wordIt;
    vector<vector<string> > paths;
    vector<vector<string> >::iterator pathsIt;

    Solution s;

    for(wordIt = words.begin(); wordIt != words.end(); wordIt++)
        cout << *wordIt << ", ";
    cout << endl;

    paths = s.findLadders( beginWord, endWord, words);

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

    makeNodes(wordList);

    // Adjacency info not set up yet, but first double check that the beginning word
    // is in the graph. If not, then we have empty list of paths.

    lookUpIt = lookUp.find(beginWord);
    if(lookUpIt == lookUp.end())
        return paths;
    else
        begin = lookUpIt -> second;  

    makeAdjacents();
}

bool Solution::inGraph(string &word) {

    map<string, WordNode*>::iterator lookUpIt;
    
    lookUpIt = lookUp.find(word);
    return (lookUpIt != lookUp.end());
}

void Solution::makeNodes(vector<string> &wordList) {

    WordNode *newNode;
    vector<string>::iterator wordIt;    

    for(wordIt = wordList.begin(); wordIt != wordList.end(); wordIt++) 

        if(!inGraph(*wordIt)) {

            newNode = new WordNode(*wordIt);
            nodes.push_back(newNode);
            lookUp.insert(pair<string, WordNode*> (*wordIt, newNode));
        }
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
