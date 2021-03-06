#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Vertex {

    string *word;
    Vertex *beginParent, *endParent;
    vector<Vertex*> adjacents;
};

class Solution {
    public:
        int ladderLength(string beginWord, string endWord, vector<string>& wordList);
        int stringDistance(string *x, string *y);
        void printGraph();

    private:
        vector<Vertex> graph;
        Vertex *beginVertex, *endVertex, *midVertex, dummy;
        bool setUpGraph(string &beginWord, string &endWord, vector<string>& wordList);
        bool connectBeginEnd(Vertex* connected, Vertex* target);
        bool beginDistClose(int x, int y);
        void findMidVertex();
        int traceDistance();
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
    
    bool endFound, found;
    queue<Vertex*> toProcess;
    vector<Vertex*>::iterator vertexIt;
    Vertex *current, *target;

    endFound = setUpGraph(beginWord, endWord, wordList);

    if(!endFound)
        return 0;

    findMidVertex();

    if(midVertex == NULL) {
        cout << "midVertex == NULL" << endl;
        return 0;
        }

    return 1 + traceDistance();

}

int Solution::stringDistance(string *x, string *y) {

    int numdifference = 0;
    string::iterator xIt, yIt;

    for(xIt = x -> begin(), yIt = y -> begin(); xIt != x -> end(); xIt++, yIt++)
        if(*xIt != *yIt)
            numdifference++;

    return numdifference;
}

void Solution::printGraph() {

    vector<Vertex>::iterator vertexIt;
    vector<Vertex*>::iterator adjacentIt;

    for(vertexIt = graph.begin(); vertexIt != graph.end(); vertexIt++) {
        cout << "Vertex: " << *(vertexIt -> word) << endl;
        cout << "     Adjacents: ";
        for(adjacentIt = vertexIt -> adjacents.begin(); adjacentIt != vertexIt -> adjacents.end(); adjacentIt++)
            cout << *(*adjacentIt) -> word << ", ";
        cout << endl;
    } 
    
    if(beginVertex != NULL) {
        cout << "Beginning Vertex: " << * beginVertex -> word << endl; 
        cout << "      Adjacents: ";
        for(adjacentIt = beginVertex -> adjacents.begin(); adjacentIt != beginVertex -> adjacents.end(); adjacentIt++)
            cout << *(*adjacentIt) -> word << ", ";
        cout << endl;
    }
    else
        cout << "Beginning Vertex = NULL" << endl;

    if(endVertex != NULL) {
        cout << "End Vertex: " << * endVertex -> word << endl; 
        cout << "      Adjacents: ";
        for(adjacentIt = endVertex -> adjacents.begin(); adjacentIt != endVertex -> adjacents.end(); adjacentIt++)
            cout << *(*adjacentIt) -> word << ", ";
        cout << endl;
    }
    else
        cout << "End Vertex = NULL" << endl;
}

bool Solution::setUpGraph(string &beginWord, string &endWord, vector<string> &wordList) {
    int graphSize, wordDistance;
    bool beginFound = false, endFound = false;
    vector<string>::iterator wordIt;
    vector<Vertex>::iterator vertexIt, vertexJt;
    vector<int> distanceToBegin;
    vector<int>::iterator distIt, distJt;
    Vertex temporary;

    // Initialize the graph.
    graph = vector<Vertex>(wordList.size());    
    beginVertex = NULL;
    endVertex = NULL;
    for (wordIt = wordList.begin(), vertexIt = graph.begin(); wordIt != wordList.end(); wordIt++, vertexIt++) {
        vertexIt -> word = &*wordIt;
        if(*wordIt == beginWord) {
            beginFound = true;
            beginVertex = &*vertexIt;
        }
       vertexIt -> beginParent = NULL;
       vertexIt -> endParent = NULL;
       vertexIt -> adjacents = vector<Vertex*>(0);
    }
   
   // Add beginning word if necessary.
   if(!beginFound) {
        temporary.word = &beginWord; 
        temporary.beginParent = NULL;
        temporary.endParent = NULL;
        graph.push_back(temporary);
        beginVertex = &*(graph.end()-1);
        beginVertex -> adjacents = vector<Vertex*>(0);
   }

   for(vertexIt = graph.begin(); vertexIt != graph.end(); vertexIt++) {
        if(* vertexIt -> word == endWord) {
            endFound = true;
            endVertex = &*vertexIt;
        }
    }

    // If no endWord in wordList, then unnecessary to continue. Return false;
    if(!endFound)
        return false;

   // Set up list of distances to beginning vertex.

    distanceToBegin = vector<int>(graph.size());
    for(vertexIt = graph.begin(), distIt = distanceToBegin.begin(); vertexIt != graph.end(); vertexIt++, distIt++) 
        *distIt = stringDistance(vertexIt -> word, beginVertex -> word);
         
   // Set up adjacencies. 
   for(vertexIt = graph.begin(), distIt = distanceToBegin.begin(); vertexIt != graph.end(); vertexIt++, distIt++) {

       for(vertexJt = vertexIt + 1, distJt = distIt + 1; vertexJt != graph.end(); vertexJt++, distJt++) {

           if(beginDistClose(*distIt, *distJt)) { 
                wordDistance = stringDistance(vertexIt -> word, vertexJt -> word);
                if(wordDistance == 1) {

                    vertexIt -> adjacents.push_back(&*vertexJt);
                    vertexJt -> adjacents.push_back(&*vertexIt);
                }
           }
       }
   } 

   return true;
}

bool Solution::connectBeginEnd(Vertex *connected, Vertex *target) {

    if(connected -> beginParent != NULL && target -> beginParent == NULL) {
        target -> beginParent = connected;
        return true;
    }
    else if(connected -> endParent != NULL && target -> endParent == NULL) {
        target -> endParent = connected;
        return true;
    }
    return false;

}

bool Solution::beginDistClose(int x, int y) {

    if( x < y + 2 && x > y - 2)
        return true;
    else
        return false;
}

void Solution::findMidVertex() {
    bool found;
    queue<Vertex*> toProcess;
    vector<Vertex*>::iterator vertexIt;
    Vertex *current, *target;

   // Set Up dummy vertex and parents of beginVertex and endVertex. Will keep track of vertex as connecting to beginning or end 
    // by using the non-nullity of the appropriate parent pointer. So we will need to 
    // set parents of beginVertex and endVertex to non-null values.

    dummy.word = NULL;
    dummy.beginParent = NULL;
    dummy.endParent = NULL;
    beginVertex -> beginParent = &dummy;
    endVertex -> endParent = &dummy;

    // Now process the vertices starting from beginVertex and endVertex in a breadth first fashion.
    toProcess.push(beginVertex);
    toProcess.push(endVertex);
    found = false;
    midVertex = NULL;

    while(!toProcess.empty() && !found) {
        current = toProcess.front();
        toProcess.pop(); 
        
        for(vertexIt = current -> adjacents.begin(); vertexIt != current -> adjacents.end(); vertexIt++) {
            target = *vertexIt;
            if(connectBeginEnd(current, target)) {
                toProcess.push(target);
            }
            if(target -> beginParent != NULL && target -> endParent != NULL) {
                found = true;
                midVertex = target;
            }
        }
    }

}

int Solution::traceDistance() {
    int distance;
    Vertex *current;
    
    // Find distance from midVertex to beginning dummy.
    distance = 0;
    current = midVertex;
    while(current != NULL) {
        distance++;
        current = current -> beginParent;
    }

    // Find the distance from midVertex to end dummy.
    current = midVertex;
    while(current != NULL) {
        distance++;
        current = current -> endParent;
    }

    // True distance is four less than distance computed as the above counts the dummy twice.
    return distance - 4;
}
