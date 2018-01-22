/**

    Leet Code 174 : Dungeon Game

    A dungeon is composed of a matrix of integers (can be negative). 
    Knight starts in the upper left, gains (or loses) health equal to value in the square 
    upon entering the sqaure, can not live if health drops below 1, and must 
    reach the princess in the lower right corner of the matrix. Find the minimum startin health that
    the knight must have to make it alive to the princess.

    Solution going across rows from right to left starting with the bottom row and working upwards. Only need to 
    store the values of the row below.

    Passes as faster than 22.84% of all cpp submissions.

**/

#include<vector>
#include<string>
#include<sstream>
#include<iostream>

/**

    Class for implementing solution to problem. The format of the member function calculateMinimumHP is
    specified by Leet Code.

**/

class Solution {
public:
    /**
    Calculate the minimuim starting HP of the knight to reach the princess alive for a given dungeon.
    
    @param dungeon The table holding the values of health gain/lost in each cell of the dungeon. It is assumed
        to be a matrix, i.e. each row has the same size.
    **/
    int calculateMinimumHP(std::vector<std::vector<int> >& dungeon);

private:

    /**
    Calculate the minimum health needed for each cell in a row given the calculations of the minimums 
    for the row below. This shouldn't be used to find the minimum for the bottom row.
    
    @param boardRow The row on the board we are calculating for.
    @param rowBelow The minimum values for the row below. 
    @param newMins A vector to hold the calculated minimum values for the current row.
    **/
    void useRowBelow(std::vector<int>& boardRow, std::vector<int>& rowBelow, std::vector<int>& newMins);

    /**
    Calculate the minimum health needed for the last row.

    @param boardRow The last row on the board.
    @param newMins A vector to hold the calculated minimum values for the last row.
    **/
    void calculateLastRow(std::vector<int>& boardRow, std::vector<int>& newMins); 
   
    /**
    Find the minimum HP needed for one position given only one possible move.

    @param board The health gain/loss on the board for the current position.
    @param moveMin The minimum HP of the only spot that can be moved to. 
    @returns The minimum for the board position.
    **/ 
    inline int getMinOneMove(int board, int moveMin); 

    /**
    Find the minimum HP needed for a position when there are two possible moves.

    @param board The health gain/loss on the board for the current position.
    @param moveMin1 The minimum HP needed for the first possible move.
    @param moveMin2 The minimum HP needed for the secondn possible move. 
    @returns The minimum for the board position.
    **/
    inline int getMinTwoMoves(int board, int moveMin1, int moveMin2);

    /**
    Simple switch of row indices for storing calculated minimums. Each index is 
    either 0 or 1, so calculation is simplified.
    
    @param a The first index.
    @param b The second index.
    **/
    inline void switchRowIndex(int& a, int& b); 
};

/**
Make a dungeon from a m by n matrix of healt gain/loss valus. Essentially just does conversion
to 2D vector type. This function is for testing purposes.

@param table Pointer to the beginning of the table (matrix). 
@param m The number of rows.
@param n The number of cols.
@returns A 2D vector conversion of the matrix.
**/
std::vector<std::vector<int> > makeDungeon(int *table, int m, int n);

/**
Convert a dungeon row to a string. This is for testing purposes.

@param dungeon Reference to the 2D vector representation of the dungeon.
@returns The string representation of the dungeon gain/loss of life values.
**/
std::string makeStr(std::vector<std::vector<int> > &dungeon);

/** 
Convert a row to a string. This is for testing purposes.

@param row The row to convert.
@returns The string representing the row.
**/
std::string makeStr(std::vector<int> &row);

////////////////////////////////////////
////////// The main executable
////////////////////////////////////////

int main() {

    const int m = 3, n = 3;
    int table[m][n] = {{-2, -3, 3},
                       {-5, -10, 1},
                       {10, 30, -5}};
    std::vector<std::vector<int> > dungeon = makeDungeon((int*)table, m, n);
    Solution s;

    std::cout << "The table is " << std::endl
              << makeStr(dungeon) << std::endl
              << "The mininmum HP is " << s.calculateMinimumHP(dungeon) << std::endl;
     
    return 0;
}

/////////////////////////////////////////////////
////////// Function Definitions /////////////////
/////////////////////////////////////////////////

int Solution::calculateMinimumHP(std::vector<std::vector<int> >& dungeon) {
    
    std::vector<int> newRows[2];
    int below = 0, current = 1; 
    std::vector<std::vector<int> >::reverse_iterator rowIt = dungeon.rbegin();

    // First check the trivial case that the dungeon is empty.
    
    if(dungeon.size() < 1)
        return 1;
    else if(dungeon.begin() -> size() < 1)
        return 1;

    // Now set up our calculation rows.

    for( int i = 0; i < 2; i++)
        newRows[i].resize(dungeon.begin() -> size());

     
    calculateLastRow(*rowIt, newRows[current]);  

    // Handle the case that there is only one row.

    if(dungeon.size() == 1) 
        return *(newRows[current]).begin();

    // Now work from bottom to top to compute the minimum.    

    for( rowIt++; rowIt != dungeon.rend(); rowIt++) {

        switchRowIndex(current, below);
        useRowBelow(*rowIt, newRows[below], newRows[current]);        
    }

    return *(newRows[current]).begin();
}

void Solution::useRowBelow(std::vector<int>& boardRow, std::vector<int>& belowRow, std::vector<int>& newMins) {

    std::vector<int>::reverse_iterator boardIt = boardRow.rbegin(), 
                                       belowIt = belowRow.rbegin(), 
                                       newIt = newMins.rbegin(),
                                       rightIt;

    // First deal with last element in new row.

    *newIt = getMinOneMove(*boardIt, *belowIt);
    rightIt = newIt;

    // Now use the values from the right and below to calculate new minimums.

    for ( newIt++, belowIt++, boardIt++;
          newIt != newMins.rend();
          boardIt++, belowIt++, newIt++, rightIt++ ) {

        *newIt = getMinTwoMoves(*boardIt, *belowIt, *rightIt);
        
    }
}

void Solution::calculateLastRow(std::vector<int>& boardRow, std::vector<int>& newMins) {

    std::vector<int>::reverse_iterator boardIt = boardRow.rbegin(),
                                       newIt = newMins.rbegin(),
                                       rightIt;

    // First handle the last position.

    *newIt = 1 -*boardIt;
    if (*newIt < 1)
        *newIt = 1;
   
    // Now use the position to the right to determine the min value of each position. 

    rightIt = newIt;

    for(newIt++, boardIt++; newIt != newMins.rend(); newIt++, boardIt++, rightIt++) 
        *newIt = getMinOneMove(*boardIt, *rightIt);
                                       
}

int Solution::getMinOneMove(int board, int lastMin) {

    int newMin = lastMin - board;

    if (newMin < 1)
        newMin = 1;

    return newMin;
}

int Solution::getMinTwoMoves(int board, int lastMin1, int lastMin2) {

    int newMin; 

    if (lastMin1 < lastMin2)
        newMin = lastMin1;
    else
        newMin = lastMin2;

    newMin = newMin - board;

    if (newMin < 1)
        newMin = 1;

    return newMin;
}

void Solution::switchRowIndex(int& a, int& b) {

    a = b;
    if(a == 0)
        b = 1;
    else
        b = 0;
}

std::vector<std::vector<int> > makeDungeon(int *table, int m, int n) {

    std::vector<std::vector<int> > dungeon;
    int *rowBegin, *rowEnd;

    for(int i = 0; i < m; i++) {
        rowBegin = table + i * n; 
        rowEnd = table + (i + 1) * n; 
        dungeon.push_back(std::vector<int>(rowBegin, rowEnd));
    }

    return dungeon;
}

std::string makeStr(std::vector<std::vector<int> > &dungeon) {

    std::ostringstream output;

    for(int m = 0; m< dungeon.size(); m++) {

        for(int n = 0; n < dungeon[m].size(); n++)
            output << dungeon[m][n] << " ";

        output << std::endl;
    }    

    return output.str();
}

std::string makeStr(std::vector<int> &row) {

    std::ostringstream output;
    
    for(int i = 0; i < row.size(); i++) {

        output << row[i] << ", ";
    }
    output << std::endl;

    return output.str();
}
