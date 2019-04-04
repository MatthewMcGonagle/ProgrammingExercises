#include "solution.h"

int Solution::binaryGap(int N) {

    // First check the trivial case.
    if(N < 2)
        return 0;

    // Now we are guaranteed to have atleast one binary 1.
    remove_leading_zeros(N);
    int largest_gap = 0, gap = 0;
    while(N > 0) {
       // Use the last gap found.
       if(gap > largest_gap)
            largest_gap = gap;
       gap = remove_gap(N);
    }

    return largest_gap;
}

void remove_leading_zeros(int &N) {

    // Only do something for positive N.
    if (N < 1)
        return;

    while( N % 2 != 1 ) 
        N /= 2;
}

int remove_gap(int &N) {
    int gap = 0;
    do {
        gap++;
        N /= 2;
    } while( N % 2 != 1 && N > 0);
    return gap++; 
}
