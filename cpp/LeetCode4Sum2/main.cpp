// Solution using standard library map to make hashes of combinations from pairs of array.
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {

    public:
        int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D);

};

int main() {

    int Aarray[] = {1, 2},
        Barray[] = {-2, -1},
        Carray[] = {-1, 2},
        Darray[] = {0, 2};
    vector<int> A(Aarray, Aarray + sizeof(Aarray) / sizeof(int)),
                B(Barray, Barray + sizeof(Barray) / sizeof(int)),
                C(Carray, Carray + sizeof(Carray) / sizeof(int)),
                D(Darray, Darray + sizeof(Darray) / sizeof(int));
    Solution s;

    cout << "Arrays are: " << endl;
    cout << "A = ";
    for (vector<int>::iterator iT = A.begin(); iT != A.end(); iT++)
        cout << *iT << ", ";
    cout << endl;
    cout << "B = ";
    for (vector<int>::iterator iT = B.begin(); iT != B.end(); iT++)
        cout << *iT << ", ";
    cout << endl;
    cout << "C = ";
    for (vector<int>::iterator iT = C.begin(); iT != C.end(); iT++)
        cout << *iT << ", ";
    cout << endl;
    cout << "D = ";
    for (vector<int>::iterator iT = D.begin(); iT != D.end(); iT++)
        cout << *iT << ", ";
    cout << endl;
    cout << "The number of possible 4-tuples are " << s.fourSumCount(A, B, C, D) << endl;


    return 0;

}

int Solution::fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D) {

    map<int, int> sumCnt1, sumCnt2; 
    int n = A.size(), count1, count2, possibilities = 0; 
    vector<int>::iterator iT, jT;
    map<int, int>::iterator mapIt;
  
    for (iT = A.begin(); iT != A.end(); iT++)
        for (jT = B.begin(); jT != B.end(); jT++) 
            sumCnt1[*iT + *jT]++;

    for (iT = C.begin(); iT != C.end(); iT++)
        for (jT = D.begin(); jT != D.end(); jT++)
            sumCnt2[*iT + *jT]++; 

    for (mapIt = sumCnt1.begin(); mapIt != sumCnt1.end(); mapIt++) {
        count1 = mapIt -> second;
        count2 = sumCnt2[-mapIt -> first];
        possibilities += count1 * count2;
    } 

    return possibilities;
}

