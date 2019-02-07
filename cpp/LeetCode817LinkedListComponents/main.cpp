#include <iostream>
#include <vector>
#include "solution1.h"

int main() {

    std::vector< std::vector<int>> lists ( { std::vector<int>({0, 1, 2}),
                                             std::vector<int>( {2, 3} ),
                                             std::vector<int>( {1, 3, 5, 9, 11, 23, 14, 156} )
                                           } );

    std::vector< std::vector<int>> Gs ( { std::vector<int>( {0, 1} ),
                                          std::vector<int>( {3} ),
                                          std::vector<int>( {3, 5, 23, 14, 156} )
                                        } );
    Solution s;
    int nComponents;

    for( int i = 0; i < lists.size(); i++ ) {
        LinkedList linked( lists[i] ); 
        std::cout << linked << std::endl;
        nComponents = s.numComponents(linked.root, Gs[i]);
        std::cout << "n components = " << nComponents << std::endl;
    } 

    return 0;
}
