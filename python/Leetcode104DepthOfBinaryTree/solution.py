class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution(object):
    def maxDepth(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """

        if root is None:
            return 0

        return self._max_subtree_depth(root) 

    def _max_subtree_depth(self, sub_root):
        sub_tree_depths = [ self._max_subtree_depth(child) if child is not None 
                            else 0
                            for child in [sub_root.left, sub_root.right]] 
        
        return 1 + max(sub_tree_depths) 
        
