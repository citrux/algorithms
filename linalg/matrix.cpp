#include <algorithm>
#include "matrix.hpp"

vec operator * (const smat & a, const vec & b)
{
    vec res(b.size());
    for (size_t i = 0; i < b.size(); ++i)
        for (auto el : a[i].data)
            res[i] += el.second * b[el.first];
    return res;
}

double & srow::operator[](const size_t index)
{
    // линейный поиск по строке
    sort(data.begin(), data.end());
    auto iter = data.begin();
    while (iter < data.end() and (*iter).first < index)
        ++iter;
    if (iter == data.end() or (*iter).first != index)
    {
        data.emplace_back(index, 0);
        iter = data.end() - 1;
    }
    return (*iter).second;
}

smat & operator += (smat & a, const smat & b)
{
    for (size_t i = 0; i < b.size(); ++i)
        for (auto el : b[i].data)
            a[i][el.first] += el.second;
    return a;
}

smat operator + (smat a, const smat & b) { return a += b; }

smat operator - (smat a) { return a * (-1); }
smat & operator -= (smat & a, const smat & b) {return a +=-b; }
smat operator - (smat a, const smat & b) { return a -= b; }


smat I(const size_t n)
{
    smat res(n);
    for (size_t i = 0; i < n; ++i)
        res[i][i] = 1;
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
        for (auto & el : row.data)
            el.second *= b;
    return a;
}
