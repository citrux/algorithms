#pragma once
#include <cmath>
#include "matrix.hpp"

vec jacobi( mat A, vec b, double eps = 1e-5 );
vec seidel( mat A, vec b, double eps = 1e-5 );
vec sor( mat A, vec b, double w, double eps = 1e-5 );
