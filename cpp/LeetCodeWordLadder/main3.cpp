#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
    public:
        int ladderLength(string beginWord, string endWord, vector<string>& wordList);
};

int stringdistance(string& x, string&y);
    
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
    int length, currentDistance;
    vector<bool> inGraph = vector<bool>(wordList.size(), false);
    vector<bool>::iterator inGraphIt;
    vector<string>::iterator wordIt;
    vector<int> distanceLowerBound = vector<int>(wordList.size(), 0);
    vector<int>::iterator distanceIt;
    queue<int> lengthToProcess;
    string *currentInGraph;


    // Initialize lower bounds on distances
    for( wordIt = wordList.begin(), distanceIt = distanceLowerBound.begin()
       ; wordIt != wordList.end(); wordIt++, distanceIt++) 
        
        *distanceIt = stringdistance(*wordIt, beginWord); 

    found = false;
    edgeWords.push(&beginWord);
    length = 0;
    lengthToProcess.push(0);
    while(!edgeWords.empty() && !found) {
        currentInGraph = edgeWords.front();
        edgeWords.pop();
        length = lengthToProcess.front();
        lengthToProcess.pop();
       
        for( wordIt = wordList.begin(), inGraphIt = inGraph.begin(), distanceIt = distanceLowerBound.begin()
           ; wordIt != wordList.end() && !found; wordIt++, inGraphIt++, distanceIt++) {

           if(!*inGraphIt && *distanceIt < length + 2 ) {
            
                currentDistance = stringdistance(*currentInGraph, *wordIt);

                if( currentDistance > 1)
                    *distanceIt = length + currentDistance;

                else {

                    if(*wordIt == endWord) { 
                        found = true;
                        length++;
                    }

                    else {
                        edgeWords.push(&*wordIt);
                        *inGraphIt = true;
                        lengthToProcess.push(length + 1);
                    }
                }
           } 
        } 

    }
    
    if(!found)
        return 0;

    return length + 1; // Count is length plus one for the beginWord. 
}

int stringdistance(string& x, string& y) {
    string::iterator xIt, yIt;
    int stringdistance = 0;

    for(xIt = x.begin(), yIt = y.begin(); xIt != x.end(); xIt++, yIt++) {
        if(*xIt != *yIt) {
            stringdistance++;
        }
    }
    
    return stringdistance;
}
