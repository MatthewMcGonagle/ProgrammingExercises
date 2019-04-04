#include "solution.h"
#include <stdexcept> // For std::runtime_error
#include <string>
#include <sstream>

int main(int argc, char* argv[]) {

    // Recall that one argument is the name of the process.
    if (argc < 3) {
        throw std::runtime_error("Test case missing arguments.");
    }

    std::string input_bits(argv[1]);
    int input = std::stoi(input_bits, nullptr, 2), 
        true_gap = std::stoi(std::string(argv[2])),
        computed_gap = Solution().binaryGap(input); 

    if (computed_gap != true_gap) {
        std::ostringstream message;
        message << "Solution.binaryGap(" << input_bits << 
                   ")\n\tinput = " << input << 
                   "\n\tcomputed = " << computed_gap << 
                   "\n\ttrue = " << true_gap; 
        throw std::runtime_error(message.str());
    } 
    
    return 0;
}
