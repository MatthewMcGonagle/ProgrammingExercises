// Store vertices as a map (i.e. dictionary). Construction of graph is then optimized
// by looking for specific adjacents so that the entire list of vertices don't need to be iterated over.
// This is assuming word size is small compared to the number of words, which seems reasonable.
// Then do a bi-directional breadth first search. 

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Vertex {
    string* word;
    Vertex *beginParent, *endParent;
    vector<Vertex*> adjacents;
};

class Solution {
    public:
        int ladderLength(string beginWord, string endWord, vector<string> &wordList);
        void printGraph();

    private:
        bool constructGraph(string &beginWord, string &endWord, vector<string> &wordList);
        void findAdjacents(Vertex *vertex);
        void findSpanningTree(Vertex *beginVertex, Vertex *endVertex);
        int traceNumVertices();

        map<string, Vertex> graph;
        Vertex *midVertex;
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

    s.printGraph();

    return 0;

}

int Solution::ladderLength(string beginWord, string endWord, vector<string> &wordList) {

    bool endFound;
    map<string, Vertex>::iterator mapIt;
    Vertex *endVertex, *beginVertex;

    endFound = constructGraph(beginWord, endWord, wordList);
    if(!endFound)
        return 0;

    mapIt = graph.find(endWord);
    if(mapIt == graph.end())
        return 0;
    endVertex = & mapIt -> second;

    mapIt = graph.find(beginWord);
    if(mapIt == graph.end())
        return 0;
    beginVertex = & mapIt -> second;

    findSpanningTree(beginVertex, endVertex);

    if(midVertex == NULL) 
        return 0;

    return traceNumVertices();

}

void Solution::printGraph() {
    map<string, Vertex>::iterator mapIt;
    vector<Vertex*>::iterator adjacentIt;

    for(mapIt = graph.begin(); mapIt != graph.end(); mapIt++) {
        cout << "Vertex " << mapIt -> first << endl;
        cout << "       Adjacents size = " << mapIt -> second.adjacents.size() << endl;
        cout << "       Adjacents: ";
        for(adjacentIt = mapIt -> second.adjacents.begin(); adjacentIt != mapIt -> second.adjacents.end(); adjacentIt++)
            cout << * (*adjacentIt) -> word << ", ";
        cout << endl; 
    }

}

bool Solution::constructGraph(string &beginWord, string &endWord, vector<string> &wordList) {
  
    vector<string>::iterator wordIt;
    Vertex toAdd;
    map<string, Vertex>::iterator mapIt;
    
    graph = map<string, Vertex>(); 

    toAdd.beginParent = NULL;
    toAdd.endParent = NULL;
    toAdd.adjacents = vector<Vertex*>(0);
    for(wordIt = wordList.begin(); wordIt!=wordList.end(); wordIt++) {
        toAdd.word = &*wordIt;
        graph.insert( pair<string, Vertex>(*wordIt, toAdd) );
    }

    // endWord was not found in the wordList. Therefore a complete path is impossible.
    if(graph.count(endWord) != 1) {
        return false;
    }

    // beginWord was not found in the wordList. So manually add it to the graph.
    if(graph.find(beginWord) == graph.end()) {
        toAdd.word = &beginWord;
        graph.insert( pair<string, Vertex>(beginWord, toAdd)); 
    }

    // Set up adjacents.
    for(mapIt = graph.begin(); mapIt != graph.end(); mapIt++) 
        findAdjacents(& mapIt -> second);

    return true;
}

void Solution::findAdjacents(Vertex* vertex) {
    string::iterator stringIt;
    string key, possible; 
    map<string, Vertex>::iterator mapIt;
    char currentChar;

    key = * vertex -> word;
    possible = key;

    // Iterate through possible changes to string.

    for(stringIt = possible.begin(); stringIt != possible.end(); stringIt++) {

        possible = key;
        currentChar = *stringIt;

        for(char change = 'a'; change < currentChar; change++) {
            possible.replace(stringIt, stringIt+1, string(1, change));
            mapIt = graph.find(possible);
            if(mapIt != graph.end()) 
                vertex -> adjacents.push_back(& mapIt -> second);
        }

        for(char change = currentChar + 1; change < 'z' + 1; change++) {
            possible.replace(stringIt, stringIt+1, string(1, change));
            mapIt = graph.find(possible);
            if(mapIt != graph.end()) 
                vertex -> adjacents.push_back(& mapIt -> second);
        }

    }

}

void Solution::findSpanningTree(Vertex *beginVertex, Vertex *endVertex) {

    queue<Vertex*> toProcess = queue<Vertex*>();
    Vertex *current, anchor;
    vector<Vertex*>::iterator adjacentIt;
    bool found;

    beginVertex -> beginParent = &anchor;
    endVertex -> endParent = &anchor;

    toProcess.push(beginVertex);
    toProcess.push(endVertex);
    found = false;
    midVertex = NULL;
    while(!toProcess.empty() && !found) { 
        current = toProcess.front();
        toProcess.pop();

        for(adjacentIt = current -> adjacents.begin(); adjacentIt != current -> adjacents.end(); adjacentIt++) {
            if( current -> beginParent != NULL && (*adjacentIt) -> beginParent == NULL) {
                (*adjacentIt) -> beginParent = current;
                toProcess.push(*adjacentIt);
            }
            else if ( current -> endParent != NULL && (*adjacentIt) -> endParent == NULL) {
                (*adjacentIt) -> endParent = current;
                toProcess.push(*adjacentIt);
            }

            if(current -> beginParent != NULL && current -> endParent != NULL) {
                found = true;
                midVertex = current;
            }
        } 
        
    }

    beginVertex -> beginParent = NULL;
    endVertex -> endParent = NULL;
}

int Solution::traceNumVertices() {

    int numVertices= 0;
    Vertex *current;

    current = midVertex;
    while(current != NULL) {
        current = current -> beginParent;
        numVertices++;
    }

    current = midVertex;
    while(current != NULL) {
        current = current -> endParent;
        numVertices++;
    }

    // Counted midVertex twice.
    return numVertices - 1;
}
