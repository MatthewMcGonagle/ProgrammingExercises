#include <iostream>
#include <vector>

using namespace std;

class Solution {

public:

    bool canPlaceFlowers(vector<int>& flowerbed, int n);

private:

    bool isFilled(int flowerPlot);
};

int main() {

    int flowerbedArray[] = {0, 1, 1, 1, 0};
    vector<int> flowerbed(flowerbedArray, flowerbedArray + sizeof(flowerbedArray) / sizeof(int));
    int n = 1;
    Solution s;
    bool canPlant;

    cout << "Flower bed is = ";
    for(int i = 0; i < flowerbed.size(); i++) 
        cout << flowerbed[i] << ", ";
    cout << endl
         << "n = " << n << endl; 

    canPlant = s.canPlaceFlowers(flowerbed, n);
    cout << "Can place flowers is " << canPlant << endl; 

    return 1;

}

bool Solution::canPlaceFlowers(vector<int>& flowerbed, int n) {

    bool last = false, current, next; // Booleans representing if there are flowers in these positions.
    vector<int>::iterator flowerIt, flowerEnd;

    // First handle some trivial cases.
    if (n < 0)
        return false;
    if (n == 0)
        return true;
    if(flowerbed.size() == 0)
        return false;

    if(flowerbed.size() == 1) {
        if(*flowerbed.begin() == 0)
            return true;
        else
            return false;
    }

    // Loop until the next to last element. The conditions for the last element are different. Also
    // note that last has been initialized to 0, so that at the beginning of the flowerbed, conditions
    // will really only depend on first and second element.

    for (flowerIt = flowerbed.begin(), flowerEnd = flowerbed.end() - 1; 
         flowerIt != flowerEnd && n != 0;
         flowerIt++ ) {

        current = isFilled(*flowerIt);
        next = isFilled(*(flowerIt + 1));        

        if(!last && !next && !current) {
           
            last = true;
            n--; 
        } 
        else
            last = current;
    }
    
    // When n = 0, we planted all flowers, and so it is true that we can plant them all.

    if(n == 0)
        return true;

    // Now test the last position. At the end of above loop, last will hold whether the
    // next to last position has a flower.

    flowerIt = flowerbed.end() - 1;
    current = isFilled(*flowerIt);

    if(!last && !current)
        n--;

    if(n == 0)
        return true;
    else
        return false;
    
}

bool Solution::isFilled(int flowerPlot) {

    if(flowerPlot > 0)
        return true;
    else
        return false;
}
