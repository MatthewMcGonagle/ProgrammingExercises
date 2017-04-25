#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
struct vertex {
    string word;
    vector<vertex*> adjacents;

    // Search parameters.
    vertex* searchParent = NULL;
};

struct wordGraph {
    vector<vertex> vertices; 
};

class Solution {
    public:
        int ladderLength(string beginWord, string endWord, vector<string>& wordList);
        wordGraph g;
        vertex* endv;
}; 
 
wordGraph makeGraph(vector<string>& wordList);
void printGraph(wordGraph& g);
void printParentChain(vertex* v);

int main() {
    string wordArray[] = {"hot", "dot", "dog", "lot", "log", "cog", "kog", "zot"};
    vector<string> wordList(wordArray, wordArray + 8);
    wordGraph g;
    Solution s;
    int chainlength;

    cout << "The word list is {";
    for (int i = 0; i < wordList.size() - 1; i++)
        cout << wordList[i] << ", ";
    cout << wordList[wordList.size()-1];
    cout << "}" << endl;

    g = makeGraph(wordList);
    printGraph(g);
    chainlength = s.ladderLength(string("hot"), string("kog"), wordList);
    cout << "ladder length = " << chainlength << endl
         << "Ladder chain (backwards) is:" << endl;
    printParentChain(s.endv);

    return 0;
}


int stringDistance(string& x, string& y) {
    string::iterator xIt, yIt;
    int numDifference = 0;

    for(xIt = x.begin(), yIt = y.begin(); xIt != x.end(); xIt++, yIt++)
        if (*xIt != *yIt)
            numDifference++;

    return numDifference;
}

wordGraph makeGraph(vector<string>& wordList) {
    wordGraph graph;
    vector<vertex> vertices(wordList.size()); 
    vector<vertex>::iterator vertexIt, vertexJt;
    vector<string>::iterator wordIt, wordJt;
     
    // Initialize graph to so that every vertex is a word from wordList

    for (wordIt = wordList.begin(), vertexIt = vertices.begin(); wordIt != wordList.end(); wordIt++, vertexIt++)
        vertexIt -> word = *wordIt;
        vertexIt -> adjacents = vector<vertex*>(0);

    // Loop through to find adjacencies (which is when word distance == 1).

    for( wordIt = wordList.begin(), vertexIt = vertices.begin(); wordIt != wordList.end(); wordIt++, vertexIt++) {
        for( wordJt = wordIt + 1, vertexJt = vertexIt + 1; wordJt != wordList.end(); wordJt++, vertexJt++) {
            if(stringDistance(*wordIt, *wordJt) == 1) {
                vertexIt -> adjacents.push_back(& *vertexJt);
                vertexJt -> adjacents.push_back(& *vertexIt);
            }
        }
    } 

    graph.vertices = vertices;
    return graph;

}

void printGraph(wordGraph& g) {
    vector<vertex>::iterator vertexIt;
    vector<vertex*>::iterator adjacentIt;

    for(vertexIt = g.vertices.begin(); vertexIt != g.vertices.end(); vertexIt++) {
        cout << "vertex " << vertexIt -> word << ": ";
        for(adjacentIt = vertexIt -> adjacents.begin(); adjacentIt != vertexIt -> adjacents.end(); adjacentIt++) {
           cout << (*adjacentIt) -> word << ", "; 
        } 
        cout << endl;
    }
    
}

void printParentChain(vertex* v) {
    cout << v -> word << endl;
    while(v -> searchParent != NULL) {
        v = v -> searchParent;
        cout << v -> word << endl;
    } 
}

int Solution::ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    int length;
    bool found;
    vector<vertex>::iterator startIt, vertexIt;
    vector<vertex*>::iterator adjIt;
    queue<vertex*> toProcess;
    vertex* current;
    g = makeGraph(wordList);
    
    // Find position of beginWord in vertex list. Also initialize the search parents to be
    // NULL.
    for( vertexIt = g.vertices.begin(); vertexIt != g.vertices.end(); vertexIt++) {
        if(vertexIt -> word == beginWord) 
            startIt = vertexIt;
        vertexIt -> searchParent = NULL; 
    }
    
    // Do a breadth first search. Start with *startIt.
    toProcess.push(& (*startIt));
    found = false;
    
    while(!toProcess.empty() && !found) {
        current = toProcess.front();
        toProcess.pop();

        // Check if current is the desired endWord. Else process adjacents of current vertex.
        if(current -> word == endWord) 
            found = true;
        else {
            for(adjIt = current -> adjacents.begin(); adjIt != current -> adjacents.end(); adjIt++)
                if( (*adjIt) != & (*startIt) && (*adjIt) -> searchParent == NULL) {
                    (*adjIt) -> searchParent = current;
                    toProcess.push(*adjIt);
                }
        }

    }

    // endWord should be a current. Problem assumes endWord does occur in graph. So the above loop must have
    // terminated by finding endWorld. Now backtrack along parents.

    endv = current;
    length = 0;
    while(current -> searchParent != NULL ) {
        length++;
        current = current -> searchParent;
    }
    
    return length;
}
