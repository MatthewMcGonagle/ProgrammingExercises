'''
Find the product of all elements in an array except self for each element of an array.

The solution is to do two passes. First find the products of all elements before each 
element. Can do this left to right (i.e. from 0 to N-1) using an accumulator.

Then do a second pass where we multiply by all elements after each element. This is
done from right to left and can also be done using an accumulator.

The performance is O(N) and constant space (excluding memory for output).
 
Performance:
92 ms Better than 98.49% of all Python3 solutions.
20.5 MB Better than 73.24% of all Python3 solutions.
'''

class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        # We do a first pass to find products[i] = product of all elements
        # nums[j] where j < i. This first pass is from left to right (i.e. i = 0
        # to i = N - 1).

        # Then we do a second pass where we find multiply by products of elements
        # nums[j] with j > i. This is done from the right to the left (i.e. i = N - 1
        # to i = 0).
        result = Solution._find_product_elements_before(nums)
        Solution._find_product_elements_after(nums, result)

        return result

    @staticmethod
    def _find_product_elements_before(nums : List[int]) -> List[int]:
        products = [1]
        accumulator = 1
        for x in nums[:-1]: 
            accumulator = accumulator * x
            products.append(accumulator)

        return products 

    @staticmethod
    def _find_product_elements_after(nums : List[int], result : List[int]) -> None:
        accumulator = nums[-1] 
        for i, x in enumerate(nums[-2::-1]): 
            result[-2-i] *= accumulator
            accumulator *= x
