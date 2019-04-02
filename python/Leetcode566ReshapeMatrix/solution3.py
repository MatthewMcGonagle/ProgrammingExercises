class MatrixElements(object):

    def __init__(self, matrix):
        '''
        Matrix should be non-empty.
        '''
        self.rows = iter(matrix)
        self.current_row = next(self.rows)
        self.current_elements = iter(self.current_row)

    def __iter__(self):
        return self

    def __next__(self):
        try:
            element = next(self.current_elements)
            return element
        except(StopIteration):
            self.current_row = next(self.rows)
            self.current_elements = iter(self.current_row) 
            element = next(self.current_elements)
            return element

    def next(self): # For Python 2 support, which apparently leetcode needs.
        return self.__next__()

class Solution(object):
    '''
    Use iterators to get values from original matrix.
    '''
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

        orig_elements = MatrixElements(nums)
        new_matrix = [[element for _, element in zip(range(c), orig_elements)] for _ in range(r)]

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
