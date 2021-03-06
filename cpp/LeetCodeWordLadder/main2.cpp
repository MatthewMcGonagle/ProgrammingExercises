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
    bool found;
    int length;
    vector<bool> inGraph = vector<bool>(wordList.size(), false);
    vector<bool>::iterator inGraphIt;
    vector<string>::iterator wordIt;
    string *currentInGraph, *lengthChange, *nextLengthChange;

    found = false;
    edgeWords.push(&beginWord);
    lengthChange = &beginWord;
    length = 0;
    while(!edgeWords.empty() && !found) {
        currentInGraph = edgeWords.front();
        edgeWords.pop();
       
        for( wordIt = wordList.begin(), inGraphIt = inGraph.begin()
           ; wordIt != wordList.end() && !found; wordIt++, inGraphIt++) {

           if(!*inGraphIt && connected(*currentInGraph, *wordIt)) {

                if(*wordIt == endWord) { 
                    found = true;
                    length++;
                }

                else {
                    edgeWords.push(&*wordIt);
                    *inGraphIt = true;
                    nextLengthChange = &*wordIt;
                }
           } 
        } 
        if(currentInGraph == lengthChange && !found) {
            length++;
            lengthChange = nextLengthChange;
        }

    }
    
    if(!found)
        return 0;

    return length + 1; // Count is length plus one for the beginWord. 
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
