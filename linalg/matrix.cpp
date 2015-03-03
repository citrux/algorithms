#include <algorithm>
#include "matrix.hpp"

vec operator * (const smat & a, const vec & b)
{
    vec res(b.size());
    for (size_t i = 0; i < b.size(); ++i)
        for (auto el : a[i])
            res[i] += el.second * b[el.first];
    return res;
}

double & getFromSRow(srow & r, const size_t index)
{
    // линейный поиск по строке
    sort(r.begin(), r.end());
    auto iter = r.begin();
    while (iter < r.end() and (*iter).first < index)
        ++iter;
    if (iter == r.end() or (*iter).first == index)
    {
        r.emplace_back(index, 0);
        iter = r.end() - 1;
    }
    return (*iter).second;
}

smat operator + (smat a, const smat & b)
{
    for (size_t i = 0; i < b.size(); ++i)
        for (auto el : b[i])
            getFromSRow(a[i], el.first) += el.second;
    return a;
}

smat I(const size_t n)
{
    smat res(n);
    for (size_t i = 0; i < n; ++i)
        res[i].emplace_back(i, 1);
    return res;
}

vec operator * (const mat & a, const vec & b)
{
    vec res(b.size());
    for (size_t i = 0; i < a.size(); ++i)
        res[i] = a[i] * b;
    return res;
}

mat operator * (mat a, const double b)
{
    for (size_t i = 0; i < a.size(); ++i)
        a[i] *= b;
    return a;
}

smat operator * (smat a, const double b)
{
    for (auto & row : a)
        for (auto & el : row)
            el.second *= b;
    return a;
}
