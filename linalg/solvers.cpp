#include "linalg.hpp"

vec jacobi( mat A, vec b, double eps )
{
    auto n = b.size();
    vec x(n);
    vec delta(n);
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

vec seidel( mat A, vec b, double eps )
{
    auto n = b.size();
    vec x(n);
    vec delta(n);
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

vec sor( mat A, vec b, double w, double eps )
{
    auto n = b.size();
    vec x(n);
    vec delta(n);
    do {
        for (auto i = 0u; i < n; ++i)
        {
            double sum = 0;
            for (auto j = 0u; j < n; ++j)
                if (i != j)
                    sum += A[i][j] * x[j];
            delta[i] = (b[i] - sum) / A[i][i] - x[i];
            x[i] += w * delta[i];
        }
    }
    while ( norm( delta ) > eps && norm( delta ) / norm( x ) > eps );
    return x;
}
