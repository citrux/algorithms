#include <cmath>
#include "vector.hpp"

using namespace std;

double operator * (const vec & a, const vec & b)
{
    double res = 0;
    double eps = 1e-4;
    for (size_t i = 0; i < a.size(); ++i)
        if (abs(a[i]) > eps && abs(b[i]) > eps)
            res += a[i] * b[i];
    return res;
}

vec & operator *= (vec & a, const double b)
{
    for (auto & i : a)
        i *= b;
    return a;
}

vec operator * (vec a, const double b) { return a *= b; }

vec & operator /= (vec & a, const double b)
{
    for (size_t i = 0; i < a.size(); ++i)
        a[i] /= b;
    return a;
}

vec operator / (vec a, const double b) { return a /= b; }

vec & operator -= (vec & a, vec b)
{
    for (size_t i = 0; i < a.size(); ++i)
        a[i] -= b[i];
    return a;
}

vec operator - (vec a, const vec & b)
{
    return a -= b;
}
