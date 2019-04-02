from solution import *
import unittest

class TestSolutionMethods(unittest.TestCase):

    test_cases = [{'description' : 'LeetCode Example 1',
                   'binary' : int('0b10110', 2),
                   'true_gap' : 2},

                  {'description' : 'LeetCode Example 2',
                   'binary' : int('0b101', 2),
                   'true_gap' : 2},

                  {'description' : 'LeetCode Example 3',
                   'binary' : int('0b110', 2),
                   'true_gap' : 1},

                  {'description' : 'LeetCode Example 4',
                   'binary' : int('0b1000', 2),
                   'true_gap' : 0},

                   {'description' : '0b010010',
                   'binary' : int('0b010010', 2),
                   'true_gap' : 3},

                  {'description' : 'Only one 1',
                   'binary' : int('0b0010000', 2),
                   'true_gap' : 0},

                  {'description' : 'Endpoints',
                   'binary' : int('0b10001', 2),
                   'true_gap' : 4}]

    def test_binaryGap(self):

        for case in TestSolutionMethods.test_cases:
            print(case['description'])
            computed_gap = Solution().binaryGap(case['binary'])
            self.assertEqual(computed_gap, case['true_gap'])

if __name__ == '__main__':
    unittest.main()
