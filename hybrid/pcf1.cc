/// @file pcf1.cc
/// @brief compute prime counting function
/// @author Jeff Perry <jeffsp@gmail.com>
/// @version 1.0
/// @date 2013-07-16

#include "isprime.h"
#include <iostream>
#include <stdexcept>

using namespace std;

const char *usage = "compute number of primes less than or equal to N\nusage: pcf <N>\n";

size_t pcf (size_t x)
{
    size_t total = 0;
    while (x > 1)
        total += isprime (x--);
    return total;
}

int main (int argc, char **argv)
{
    try
    {
        if (argc != 2)
            throw runtime_error (usage);

        cout << pcf (atol (argv[1])) << endl;

        return 0;
    }
    catch (const exception &e)
    {
        cerr << e.what () << endl;
        return -1;
    }
}
