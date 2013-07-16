/// @file isprime.h
/// @brief determine if a number is prime
/// @author Jeff Perry <jeffsp@gmail.com>
/// @version 1.0
/// @date 2013-07-16

#ifndef ISPRIME_H
#define ISPRIME_H

#include <cstdlib>
#include <cmath>

/// @brief naive way to determine if a number is prime
/// @param x
/// @return true if x is prime, false otherwise
bool isprime (const size_t x)
{
    const size_t n = std::sqrt (static_cast<long double> (x));
    for (size_t i = 2; i <= n; ++i)
        if (x % i == 0)
            return false;
    return true;
}

#endif // ISPRIME_H
