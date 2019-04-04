#include "solution.h"
#include <stdexcept>
#include <string>
#include <sstream>

int main(int argc, char *argv[]) {

    std::string input_bits(argv[1]),
                output_bits(argv[2]);
    int input = std::stoi(input_bits, nullptr, 2),
        computed = input,
        true_output = std::stoi(output_bits, nullptr, 2); 

    remove_leading_zeros(computed);
    if( computed != true_output ) {
        std::ostringstream oss;
        oss << "\tinput_bits = " << input_bits <<
               "\n\tinput = " << input <<
               "\n\toutput = " << computed <<
               "\n\ttrue_output = " << true_output <<
               "\n\ttrue_output_bits = " << output_bits;
        throw std::runtime_error(oss.str());
    }  
}
