#pragma once
#include <vector>
#include <iostream>

using namespace std;

using vec = vector<double>;

double operator * (const vec & a, const vec & b);
vec & operator *= (vec & a, const double b);
vec operator * (vec a, const double b);
vec & operator /= (vec & a, const double b);
vec operator / (vec a, const double b);
vec & operator -= (vec & a, vec b);
vec operator - (vec a, const vec & b);
inline double norm(const vec & a) {return sqrt(a * a);}

template <typename T>
ostream & operator << (ostream &os, const vector<T> &v)
{
    for(auto i : v)
        os << to_string(i) << " ";
    return os;
}

template <typename T>
string to_string(const vector<T> &v)
{
    string out = "{ ";
    for(auto i : v)
        out += to_string(i) + ", ";
    out += " }";
    return out;
}
