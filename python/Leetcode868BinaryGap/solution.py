class Solution(object):
    def binaryGap(self, N):
        """
        Compute the largest gap between consecutive 1's in the binary representation of a positive
        integer N. If there aren't any consecutve 1's, then return 0. 

        :type N: int
            Positive
        :rtype: int
        """
        if N < 1:
           return 0 

        largest = 0 

        # First find the first 1, guaranteed to find it.

        while N % 2 == 0 and N > 0:
           N //= 2 

        while N > 0:
            N //= 2 # Remove the current 1.
            gap = 1
            while N % 2 == 0 and N > 0:
                N //= 2
                gap += 1            

            # Make sure to test that we didn't just hit the end of the bits.
            if N > 0 and gap > largest: 
                largest = gap
                
        return largest
