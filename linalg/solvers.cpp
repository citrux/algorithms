#include "linalg.hpp"

v jacobi( m A, v b, double eps )
{
    auto n = b.size();
    v x(n);
    v delta(n);
    do {
        for (auto i = 0u; i < n; ++i)
        {
            double sum = 0;
            for (auto j = 0u; j < n; ++j)
                if (i != j)
                    sum += A[i][j] * x[j];
            delta[i] = (b[i] - sum) / A[i][i] - x[i];
        }
        for (auto i = 0u; i < n; ++i)
            x[i] += delta[i];
    }
    while ( norm( delta ) > eps && norm( delta ) / norm( x ) > eps );
    return x;
}

v seidel( m A, v b, double eps )
{
    auto n = b.size();
    v x(n);
    v delta(n);
    do {
        for (auto i = 0u; i < n; ++i)
        {
            double sum = 0;
            for (auto j = 0u; j < n; ++j)
                if (i != j)
                    sum += A[i][j] * x[j];
            delta[i] = (b[i] - sum) / A[i][i] - x[i];
            x[i] += delta[i];
        }
    }
    while ( norm( delta ) > eps && norm( delta ) / norm( x ) > eps );
    return x;
}
