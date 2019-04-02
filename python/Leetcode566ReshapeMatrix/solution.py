class Solution(object):
    def matrixReshape(self, nums, r, c):
        """
        :type nums: List[List[int]]
        :type r: int
        :type c: int
        :rtype: List[List[int]]
        """
        n_orig_rows = len(nums)
        if n_orig_rows == 0: # 1 by 0.
            return Solution._reshape_empty(True, r, c)

        n_orig_cols = len(nums[0])
        if n_orig_cols == 0:
            return Solution._reshape_empty(False, r, c)

        # Test if possible when nonempty.
        if n_orig_rows * n_orig_cols != r * c:
            return nums

        orig_row = 0
        orig_col = 0
        new_matrix = []

        for _ in range(r):
            new_row = []
            for _ in range(c):
                element = nums[orig_row][orig_col]
                new_row.append(element)

                orig_col += 1
                if orig_col == n_orig_cols:
                    orig_col = 0
                    orig_row += 1
            new_matrix.append(new_row)

        return new_matrix 
                    
    def _reshape_empty(original_has_empty_rows, r, c):
        if r > 0 and c > 0:
            if original_has_empty_rows:
                return []
            else:
                return [[]]  

        if r == 0:
            return []
        else:
            return [[] for _ in range(r)]
