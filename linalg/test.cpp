#include <iostream>
#include "linalg.hpp"

int main()
{
    m A = {{3,2,1},{4,6,5},{7,8,9}};
    v b = {6, 15, 24};
    auto x = jacobi( A, b );
    for ( auto i: x )
        std::cout << i << " ";
}
