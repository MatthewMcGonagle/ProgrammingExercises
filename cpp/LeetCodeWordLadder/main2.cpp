#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
    public:
        int ladderLength(string beginWord, string endWord, vector<string>& wordList);
};

bool connected(string& x, string& y);
    
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
    queue<string*> edgeWords;
    queue<int> inGraphDistance;
    bool found = false;
    int currentInDistance;
    vector<bool> inGraph = vector<bool>(wordList.size(), false);
    vector<bool>::iterator inGraphIt;
    vector<string>::iterator wordIt;
    string *currentInGraph;

    edgeWords.push(&beginWord);
    inGraphDistance.push(0);

    while(!edgeWords.empty() && !found) {
        currentInGraph = edgeWords.front();
        edgeWords.pop();
        currentInDistance = inGraphDistance.front();
        inGraphDistance.pop();
       
        for( wordIt = wordList.begin(), inGraphIt = inGraph.begin()
           ; wordIt != wordList.end() && !found; wordIt++, inGraphIt++) {

           if(!*inGraphIt && connected(*currentInGraph, *wordIt)) {

                if(*wordIt == endWord) { 
                    found = true;
                }
                else {
                    edgeWords.push(&*wordIt);
                    inGraphDistance.push(currentInDistance + 1);
                    *inGraphIt = true;
                }
           } 
        } 

    }
    
    if(!found)
        return 0;

    return currentInDistance + 2; // Count is distance plus two endpoints.
}

bool connected(string& x, string& y) {
    string::iterator xIt, yIt;
    bool smallDistance = true;
    int distance = 0;

    for(xIt = x.begin(), yIt = y.begin(); xIt != x.end() && smallDistance; xIt++, yIt++) {
        if(*xIt != *yIt) {
            distance++;
            if(distance > 1)
                smallDistance = false;
        }
    }
    
    return smallDistance;
}
