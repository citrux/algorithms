#include "linalg.hpp"

double norm( v x )
{
    double res = 0;
    for ( auto i: x )
        if ( std::abs( i ) > res )
            res = std::abs( i );
    return res;
}

double norm( m A )
{
    double res = 0;
    for ( auto i: A )
    {
        double s = 0;
        for ( auto j: i )
            s += std::abs( j );
        if ( s > res )
            res = s;
    }
    return res;
}

