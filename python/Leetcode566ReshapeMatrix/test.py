from solution4 import *
import unittest

class TestSolutionMethods(unittest.TestCase):

    def test_reshape_empty(self):
        cases = [('0 by * -> 0 by *', True, 0, 5, []),
                 ('1 by 0 -> 0 by *', False, 0, 6, []),
                 ('1 by 0 -> 3 by 0', False, 3, 0, [[], [], []])
                ]
        for description, orig_empty_rows, new_rows, new_cols, true_matrix in cases:
            print('Testing _reshape_empty()', description)
            computed_matrix = Solution._reshape_empty(orig_empty_rows, new_rows, new_cols)
            self.assertEqual(computed_matrix, true_matrix)

    def test_matrixReshape(self):
        cases = [('0 by * -> 3 by 0', [], 3, 0, [[], [], []]),
                 ('2 by 0 -> 0 by 2', [[], []], 0, 2, []),
                 ('2 by 3 -> 3 by 2', [[1, 2, 3], [4, 5, 6]], 3, 2, [[1, 2], [3, 4], [5, 6]]),
                 ('2 by 3 -> 1 by 4', [[1, 2, 3], [4, 5, 6]], 1, 4, [[1, 2, 3], [4, 5, 6]]),
                 ('2 by 3 -> 1 by 6', [[1, 2, 3], [4, 5, 6]], 1, 6, [[1, 2, 3, 4, 5, 6]]),
                 ('2 by 3 -> 6 by 1', [[1, 2, 3], [4, 5, 6]], 6, 1, [[1], [2], [3], [4], [5], [6]]) ]

        for description, original, new_row, new_col, true_reshape in cases:
            print('Testing matrixReshape()', description)
            computed_reshape = Solution().matrixReshape(original, new_row, new_col)
            self.assertEqual(computed_reshape, true_reshape)

if __name__ == '__main__':
    unittest.main()
