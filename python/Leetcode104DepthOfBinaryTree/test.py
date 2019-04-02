from solution import *
from heapq import heappush, heappop
import unittest

class Tree(object):

    def __init__(self, values):

        if not values:
            self.root = None
            return

        self.root = TreeNode(values[0])
        self._priority = 0
        self._to_add_children = []
        self._push_to_add_children(self.root)

        for value in values[1:]:
            # Still need to pop even if no node added.
            next_node, direction = self._pop_to_add_children()
            if value != 'null' and direction == 'L':
               next_node.left = TreeNode(value)
               self._push_to_add_children(next_node.left)
            elif value != 'null' and direction == 'R':
               next_node.right = TreeNode(value) 
               self._push_to_add_children(next_node.right)

    def _push_to_add_children(self, node): 
        self._priority += 1
        heappush(self._to_add_children, [self._priority, node, 'L'])
        self._priority += 1
        heappush(self._to_add_children, [self._priority, node, 'R'])

    def _pop_to_add_children(self):
        _, node, direction = tuple(heappop(self._to_add_children))
        return node, direction

class TestSolutionMethods(unittest.TestCase):

    test_cases = [{'description' : 'Leetcode Example',
                   'values' : [3, 9, 20, 'null', 'null', 15, 7],
                   'true_depth' : 3},

                  {'description' : 'All Left',
                   'values' : [1, 2, 'null', 3, 'null', 4, 'null'],
                   'true_depth' : 4},

                  {'description' : 'One Node',
                   'values' : [1],
                   'true_depth' : 1},

                  {'description' : 'All Right',
                   'values' : [1, 'null', 2, 'null', 3, 'null', 4],
                   'true_depth' : 4},

                  {'description' : 'Empty',
                   'values' : [],
                   'true_depth' : 0}
                  ]

    def test_maxDepth(self):
        for case in TestSolutionMethods.test_cases:
            print('Testing', case['description'])
            tree = Tree(case['values'])
            computed_depth = Solution().maxDepth(tree.root)
            self.assertEqual(computed_depth, case['true_depth']) 

if __name__ == '__main__':
    unittest.main()
