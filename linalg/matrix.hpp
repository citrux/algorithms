#pragma once
#include "vector.hpp"

typedef vector<vec> mat;
typedef vector<pair<size_t, double>> srow; // sparse row
typedef vector<srow> smat; // sparse matrix

vec operator * (const smat & a, const vec & b);
vec operator * (const mat & a, const vec & b);
mat operator * (mat a, const double b);
smat operator * (smat a, const double b);
smat operator + (const smat a, const smat & b);
smat I(const size_t n);
