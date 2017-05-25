#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);
        double findMedianOne(int begin, int end, vector<int>& nums);

    private:
        int findNumToRemove(int begin, int end);
        vector<int> findAroundMedian(int begin, int end, vector<int>& nums);
};

int main() {

    int list1[] = {0, 2, 4, 5, 6},
        list2[] = {1, 2, 2, 3, 3, 4, 5, 6, 7, 8};
    vector<int> vector1 = vector<int>(list1, list1 + sizeof(list1) / sizeof(int)),
                vector2 = vector<int>(list2, list2 + sizeof(list2) / sizeof(int)),
                vector3; 
    vector<int>::iterator vectIt;
    Solution s;

    cout << "vector 1 = ";
    for( vectIt = vector1.begin(); vectIt != vector1.end(); vectIt++) 
        cout << *vectIt << ", ";
    cout << endl;

    cout << "vector 2 = ";
    for( vectIt = vector2.begin(); vectIt != vector2.end(); vectIt++) 
        cout << *vectIt << ", ";
    cout << endl;

    cout << "Median of both vectors using Solution class = " << s.findMedianSortedArrays(vector1, vector2) << endl;

    vector3 = vector1;
    for(int i = 0; i < vector2.size(); i++)
        vector3.push_back(vector2[i]);
    sort(vector3.begin(), vector3.end());
    cout << "Combined Vectors vector3 = ";
    for(vectIt = vector3.begin(); vectIt != vector3.end(); vectIt++)
        cout << *vectIt << ", ";
    cout << endl;

    cout << "True Median of combined = " << s.findMedianOne(0, vector3.size(), vector3) << endl;
    return 0;
}

double Solution::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int begin1, end1, begin2, end2, med1, med2;
    int numToRemove; 

    vector<int> smallList1, smallList2; 

    begin1 = 0; 
    begin2 = 0; 
    end1 = nums1.size(); 
    end2 = nums2.size(); 

    if (end1 == 0)
        return findMedianOne(begin2, end2, nums2);

    if (end2 == 0)
        return findMedianOne(begin1, end1, nums1);

    while(end1 - begin1 > 2 && end2 - begin2 > 2) {
        med1 = findMedianOne(begin1, end1, nums1);
        med2 = findMedianOne(begin2, end2, nums2);
        if( end1 - begin1 < end2 - begin2)
            numToRemove = findNumToRemove(begin1, end1);
        else
            numToRemove = findNumToRemove(begin2, end2);

        if( med1 <= med2 ) {
           begin1 += numToRemove;
           end2 -= numToRemove; 
        }
        if( med1 >= med2 ) {
           begin2 += numToRemove;
           end1 -= numToRemove;
        }
    }

    // Should be left with the case that one of arrays is of size 2 or size 1. If both inequalities satisfied
    // inside loop, can get one of the new arrays being of size 1.

    // Only need to look at three or four elements around largest arrays median, depends on size of array modulo 2. Don't need to full array.

    smallList1 = findAroundMedian(begin1, end1, nums1);
    smallList2 = findAroundMedian(begin2, end2, nums2);

    for(int i = 0; i < smallList2.size(); i++)
        smallList1.push_back(smallList2[i]);

    sort(smallList1.begin(), smallList1.end());
    
    return findMedianOne(0, smallList1.size(), smallList1);
}

double Solution::findMedianOne(int begin, int end, vector<int>& nums) {

    int size;

    size = end - begin;
    if(size == 1)
        return nums[begin];
    else if (size % 2 == 1)
        return nums[size / 2];
    else 
        return (nums[size / 2] + nums[size / 2 + 1]) / 2.0; 
        
}

int Solution::findNumToRemove(int begin, int end) {
    int size = end - begin;

    if (size < 3)
        return 0;
    else if (size % 2 == 1)
        return size / 2;
    else 
        return size / 2 - 1;
}

vector<int> Solution::findAroundMedian(int begin, int end, vector<int>& nums) {

    vector<int> smallList(0);
    int size = end - begin;

    if(size < 5) {
        for(int i = begin; i < end; i++)
            smallList.push_back(nums[i]);
    }
    else if (size % 2 == 1) {
        begin += size / 2 - 1;
        end = begin + 3;
        for( int i = begin; i < end; i++)
            smallList.push_back(nums[i]); 
    } 
    else {
        begin += size / 2 - 2;
        end = begin + 4;
        for( int i = begin; i < end; i++)
            smallList.push_back(nums[i]);
    }

    return smallList;
}
