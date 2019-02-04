/*/!
    Solution1.h
    Matthew McGonagle

    Problem: Sort the characters in a string according to frequency. Don't need to respect ordering of characters
        in the initial string. So there are multiple acceptable solutions.

    This Solution:
    Use an unordered_map (hash map) to get the letter counts, and then put the counts in a priority queue. Use
    the priority queue to do sort the letters by count (this will NOT be a proper sort that respects the ordering
    of the characters in the initial string).

 */
#pragma once
#include <string>
#include <unordered_map>
#include <queue>

struct charCount {

    charCount(std::pair<char, unsigned int> pair) {
        myChar = pair.first;
        myCount = pair.second;
    }

    charCount(char myChar_, unsigned int myCount_) : myChar(myChar_), myCount(myCount_) {} 
    char myChar;
    unsigned int myCount;

};

bool operator<(const charCount &a, const charCount &b);

class Solution {

public:
    std::string frequencySort( std::string s );

private:
    typedef std::unordered_map<char, unsigned int> countsTable;
    typedef std::priority_queue< charCount > orderedCounts;
    
    void getCounts( std::string &s );
    void orderCounts();

    countsTable myCounts;
    orderedCounts myOrderedCounts;
};
