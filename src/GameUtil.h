#pragma once

#include <string>
#include <sstream>
#include <cmath>
#include <SFML/System.hpp>

float randRangef(float min, float max);

// https://en.sfml-dev.org/forums/index.php?topic=2424.0
template <typename T>
std::string str(const T& x)
{
    std::ostringstream oss;
    oss << x;

    return oss.str();
}

/*
Bound
    Takes a reference variable, lower bound, upper bound.
    Clamps value to within bounds.
    Also needs to check that bounds are valid.
*/
template <typename T>
int bound(T& x, T lower, T upper)
{
    if (lower > upper)      // equal to is valid
        return 1;
    if (x < lower)
        x = lower;
    else if (x > upper)
        x = upper;
    return 0;
}
