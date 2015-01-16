#pragma once
#include <cmath>
#include <vector>

typedef std::vector< double > v;
typedef std::vector< v > m;

v jacobi( m A, v b, double eps = 1e-5 );
double norm ( v x );
double norm ( m A );

