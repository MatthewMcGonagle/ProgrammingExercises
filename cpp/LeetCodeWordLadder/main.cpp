#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
struct vertex {
    vertex() { word = string(""); adjacents = vector<vertex*>(0); searchParent = NULL;}
    string word;
    vector<vertex*> adjacents; 

    // Search parameters.
    vertex* searchParent;
};

struct wordGraph {
    wordGraph() {vertices = vector<vertex>(0);}
    vector<vertex> vertices; 
};

class Solution {
    public:
        int ladderLength(string beginWord, string endWord, vector<string>& wordList);
        wordGraph g;
        vertex* endv;
}; 
 
void makeGraph(vector<string>& wordList, wordGraph& graph);
void printGraph(wordGraph& g);
void printParentChain(vertex* v);

int main() {
    string wordArray[] = {"hot", "dot", "dog", "lot", "log", "cog"};
    vector<string> wordList(wordArray, wordArray + 6);
    wordGraph g;
    Solution s;
    int chainlength;

    cout << "The word list is {";
    for (int i = 0; i < wordList.size() - 1; i++)
        cout << wordList[i] << ", ";
    cout << wordList[wordList.size()-1];
    cout << "}" << endl;

    makeGraph(wordList, g);
    printGraph(g);
    chainlength = s.ladderLength(string("hit"), string("cog"), wordList);
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

void makeGraph(vector<string>& wordList, wordGraph &graph) {
    vector<vertex>::iterator vertexIt, vertexJt;
    vector<string>::iterator wordIt, wordJt;
     
    // Initialize graph to so that every vertex is a word from wordList
    graph.vertices = vector<vertex>(wordList.size());

    for (wordIt = wordList.begin(), vertexIt = graph.vertices.begin(); wordIt != wordList.end(); wordIt++, vertexIt++)
        vertexIt -> word = *wordIt;
    

    // Loop through to find adjacencies (which is when word distance == 1).

    for( wordIt = wordList.begin(), vertexIt = graph.vertices.begin()
       ; wordIt != wordList.end(); wordIt++, vertexIt++) {
        for( wordJt = wordIt + 1, vertexJt = vertexIt + 1; wordJt != wordList.end(); wordJt++, vertexJt++) {
            if(stringDistance(*wordIt, *wordJt) == 1) {
                vertexIt -> adjacents.push_back(& *vertexJt);
                vertexJt -> adjacents.push_back(& *vertexIt);
            }
        }
    } 

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
    vector<vertex>::iterator vertexIt;
    vector<vertex*>::iterator adjIt;
    vector<string>::iterator wordIt;
    queue<vertex*> toProcess;
    vertex *current, *startv;

    // See if beginWord needs to be added to the wordList
    found = false;
    for(wordIt = wordList.begin(); wordIt != wordList.end() && !found; wordIt++)
        if(*wordIt == beginWord) 
            found = true;
    if(!found)
        wordList.push_back(beginWord);
    
    makeGraph(wordList, g);
    
    // Find position of beginWord in vertex list. Also initialize the search parents to be
    // NULL.
    for( vertexIt = g.vertices.begin(); vertexIt != g.vertices.end(); vertexIt++) {
        if(vertexIt -> word == beginWord) 
            startv = & (*vertexIt);
        vertexIt -> searchParent = NULL; 
    }
    
    // Do a breadth first search. Start with *startIt.
    toProcess.push(startv);
    found = false;
    
    while(!toProcess.empty() && !found) {
        current = toProcess.front();
        toProcess.pop();

        // Check if current is the desired endWord. Else process adjacents of current vertex.
        if(current -> word == endWord) 
            found = true;
        else {
            for(adjIt = current -> adjacents.begin(); adjIt != current -> adjacents.end(); adjIt++) {
                if( (*adjIt) != startv && (*adjIt) -> searchParent == NULL) {
                    (*adjIt) -> searchParent = current;
                    toProcess.push(*adjIt);
                }
            }
        }

    }

    // Check if not found. In this case, return 0.
    if(!found)
        return 0;

    // endWord should be a current. Problem assumes endWord does occur in graph. So the above loop must have
    // terminated by finding endWorld. Now backtrack along parents.

    endv = current;
    length = 1;
    while(current -> searchParent != NULL ) {
        length++;
        current = current -> searchParent;
    }
    
    return length;
}
