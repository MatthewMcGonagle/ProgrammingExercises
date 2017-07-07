#include<iostream>
#include<vector>

using namespace std;

class Solution {

    public:
        void moveZeroes(vector<int> &nums);

};

int main() {

    int numsArray[] = {0, 1, 0, 3, 12};
    vector<int> nums(numsArray, numsArray + sizeof(numsArray) / sizeof(int));
    Solution s;

    for(vector<int>::iterator iT = nums.begin(); iT != nums.end(); iT++)
        cout << *iT << ", ";
    cout << endl;

    s.moveZeroes(nums);

    for(vector<int>::iterator iT = nums.begin(); iT != nums.end(); iT++)
        cout << *iT << ", ";
    cout << endl;


    return 0;

}

void Solution::moveZeroes(vector<int> &nums) {

    vector<int>::iterator writeIt, readIt;

    for(writeIt = nums.begin(), readIt = nums.begin();
        readIt != nums.end();
        readIt++) {

            if (*readIt != 0) {
                *writeIt = *readIt;
                writeIt++;
            }
    }

    for( ; writeIt != nums.end(); writeIt++)
        *writeIt = 0;
}
