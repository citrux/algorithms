#include <iostream>
#include "linalg.hpp"

int main()
{
    m A = {{3,1,1},{3,6,2},{1,5,9}};
    v b = {5, 11, 15};
    std::cout << "Проверка метода Якоби:" << std::endl;
    auto x = jacobi( A, b );
    for ( auto i: x )
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "Проверка метода Зейделя:" << std::endl;
    x = seidel( A, b );
    for ( auto i: x )
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "Проверка метода верхней релаксации:" << std::endl;
    x = sor( A, b, 1.5 );
    for ( auto i: x )
        std::cout << i << " ";
    std::cout << std::endl;


}
