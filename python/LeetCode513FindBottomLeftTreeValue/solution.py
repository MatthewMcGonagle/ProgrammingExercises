'''
Find the left most value on the bottom row of a binary tree.

Solution uses depth first search. Keep track of value and depth of values
for left and right children. Then use their depths to figure out which one
to keep.
'''
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def findBottomLeftValue(self, root: TreeNode) -> int:
        val, _ = self._findWithDepth(root)
        return val

    def _findWithDepth(self, root: TreeNode) -> (int, int):
        '''
        Returns
        -------
        value : int
        depth : int
        '''
        if root.left is None and root.right is None:
            return root.val, 0 
        elif root.left is None:
            val, depth = self._findWithDepth(root.right)
            return val, depth + 1
        elif root.right is None:
            val, depth = self._findWithDepth(root.left)
            return val, depth + 1
        else:
            val_left, depth_left = self._findWithDepth(root.left)
            val_right, depth_right = self._findWithDepth(root.right)
            if depth_right > depth_left:
                val, depth = val_right, depth_right + 1
            else:
                val, depth = val_left, depth_left + 1
            return val, depth
            
