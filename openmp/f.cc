/// @file f.cc
/// @brief openmp parallelization test
/// @author Jeff Perry <jeffsp@gmail.com>
/// @version 1.0
/// @date 2013-07-15

#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>

using namespace std;
using namespace chrono;

typedef vector<unsigned char> buf_t;
typedef vector<size_t> dist_t;

const string usage = "./f <#_of_buffers> <buffer_size>";

int main (int argc, char **argv)
{
    try
    {
        // parse args
        if (argc != 3)
            throw runtime_error (usage);

        const size_t N = atoi (argv[1]);
        const size_t SZ = atoi (argv[2]);
        const size_t K = 1 << (8*sizeof(buf_t::value_type));

        clog << "buffers " << N << endl;
        clog << "size " << SZ << endl;
        clog << "values " << K << endl;

        // create N buffers of size SZ
        vector<buf_t> a (N, buf_t (SZ));

        // create a uniformly distributed random number generator
        std::mt19937 eng;
        std::uniform_int<unsigned> d (0, K-1);

        high_resolution_clock::time_point t1 = high_resolution_clock::now ();

        // fill the buffers with random data
#ifdef _OPENMP
#pragma omp parallel for
#endif
        for (size_t i = 0; i < a.size (); ++i)
        {
            int r = d (eng);
            for (size_t j = 0; j < a[i].size (); ++j)
            {
                // d(eng) is a critical section, so don't call it often
                if (!(j%1000))
                    r = d (eng);
                a[i][j] = r;
            }
        }

        // create N distribution tables
        vector<dist_t> b (a.size (), dist_t (K));

        // compute the distribution for each buffer
#ifdef _OPENMP
#pragma omp parallel for
#endif
        for (size_t i = 0; i < a.size (); ++i)
            for (size_t j = 0; j < a[i].size (); ++j)
                ++b[i][a[i][j]];

        // combine N distributions into one
        dist_t c (K);
        for (size_t i = 0; i < b.size (); ++i)
            for (size_t j = 0; j < c.size (); ++j)
                c[j] += b[i][j];

        high_resolution_clock::time_point t2 = high_resolution_clock::now ();

        // print the combined distribution
        //for (size_t i = 0; i < c.size (); ++i)
        //    clog << ' ' << int (c[i]);
        //clog << endl;

        // check answer
        const size_t n = accumulate (c.begin (), c.end (), 0ul);

        if (n != N * SZ)
            throw runtime_error ("failed");
        else
            clog << "success" << endl;

        // report time
        duration<double> diff = duration_cast<duration<double>> (t2 - t1);
        std::cout << diff.count() << "s elapsed" << endl;

        return 0;
    }
    catch (const exception &e)
    {
        cerr << e.what () << endl;
        return -1;
    }
}
