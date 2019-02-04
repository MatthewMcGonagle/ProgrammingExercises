#include <iostream>
#include <vector>
#include <string>
#include "solution1.h"

int main() {

    std::vector<std::string> inputs( { std::string(),
                                       std::string("a"),
                                       std::string("hello"), 
                                       std::string("aabBBc"),
                                       std::string("tree") } );
    std::string sorted;

    Solution s;
    for(int i = 0; i < inputs.size(); i++) {
        std::cout << inputs[i] << std::endl; 
        sorted = s.frequencySort(inputs[i]);
        std::cout << sorted << "\n\n";        
    }
}
