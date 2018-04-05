/**
LeetCode 169 Majority Element
Matthew McGonagle

This is a solution based on keeping the counts of the values in std::map. As we increase counts of keys, we check
to see if the total count of this key so far is greater than half. This is only possible for majority element. 

Solution accepted with high variance in performance on LeetCode. Benchmarked as between being faster than 96.01% of all C++ submissions
and 68% of all C++ submissions.
**/

#include<vector>
#include<map>
#include<iostream>

class Solution {

    public:
    int majorityElement(std::vector<int> &nums);

};

int main() {

    int numsArray[] = {0, 2, 1, 1, 0, 0, 5, 0, 0, 0};
    int majority;
    std::vector<int> nums(numsArray, numsArray + sizeof(numsArray) / sizeof(int));
    Solution s;

    std::cout << "Length of nums = " << nums.size() << std::endl;
    std::cout << "Running solution." << std::endl;
    majority = s.majorityElement(nums);
    std::cout << "The majority element is " << majority << std::endl;
    

}

int Solution::majorityElement(std::vector<int> &nums) {

    std::map<int, int> counts;
    std::map<int, int>::iterator keyIt;
    int current, count, halfCount = nums.size() / 2;

    // First handle some trivial cases.

    if (nums.size() == 0)
        return 0;

    if (nums.size() < 3)
        return nums[0];

    // For each number, if it isn't already in the counts map, then add it.  Else, update the count.
    for (std::vector<int>::iterator numIt = nums.begin(); numIt != nums.end(); numIt++) {

        current = *numIt;
        keyIt = counts.find(current); 

        if(keyIt == counts.end())
            counts.insert(std::pair<int, int>(current, 1));

        else 
            (keyIt -> second)++;
    }

    // Now search throught the map for the majority count.

    for(keyIt = counts.begin(); keyIt != counts.end(); keyIt++) {
  
        current = keyIt -> first; 
        count = keyIt -> second; 
        if(count > halfCount)
            return current; 
    }

    return -12345;
}
