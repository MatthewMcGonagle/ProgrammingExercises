#include "Solution1.h"
#include <string>

bool operator<(const charCount &a, const charCount &b) {

    return a.myCount < b.myCount;

}


std::string Solution::frequencySort( std::string s ) {

    std::string sorted;

    // Trivial case.
    if( s.size() < 2)
        return s;

    getCounts( s );
    orderCounts(); 

    while( !myOrderedCounts.empty()) {
        const charCount& newChar = myOrderedCounts.top();
        sorted.append( std::string(newChar.myCount, newChar . myChar) );
        myOrderedCounts.pop();

    }

    // Clean up.

    myCounts = countsTable();
    myOrderedCounts = orderedCounts();

    return sorted;
}

void Solution::getCounts( std::string &s ) {

    countsTable::iterator toIncrement;

    for( char& toCount : s ) {

       toIncrement = myCounts.find(toCount);
       if (toIncrement != myCounts.end())
         (toIncrement->second)++; 
       else 
         myCounts.insert( std::pair<char, unsigned int> (toCount, 1) );
    }
}

void Solution::orderCounts() {

    for(auto toAdd : myCounts) {
        myOrderedCounts.push( charCount( toAdd ) ); 
    }    
}
