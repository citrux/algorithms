#include <iostream>
#include "linalg.hpp"
#include "eigens.hpp"

int main()
{
    mat A = {{60,30,20},{30,20,15},{20,15,12}};
    vec b = {110, 65, 47};
    std::cout << "Проверка метода Якоби:" << std::endl;
    auto x = jacobi( A, b );
    std::cout << x << std::endl;

    std::cout << "Проверка метода Зейделя:" << std::endl;
    x = seidel( A, b );
    std::cout << x << std::endl;

    std::cout << "Проверка метода верхней релаксации:" << std::endl;
    x = sor( A, b, 1.5 );
    std::cout << x << std::endl;

    std::cout << "Проверка собственных значений:" << std::endl;
    std::cout << getEigens(A) << std::endl;
}
