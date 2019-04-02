class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution(object):
    def deleteNode(self, node):
        """
        :type node: ListNode
        :rtype: void Do not return anything, modify node in-place instead.
        """
        if node.next is None:
            pass # Can't delete the tail.
        else:
            to_delete = node.next
            node.val = to_delete.val
            node.next = to_delete.next
            del to_delete
