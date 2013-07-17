/// @file pcf3.cc
/// @brief compute prime counting function
/// @author Jeff Perry <jeffsp@gmail.com>
/// @version 1.0
/// @date 2013-07-16

#include "isprime.h"
#include <mpi.h>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;
using namespace MPI;

const char *usage = "compute number of primes less than or equal to N\nusage: pcf <N>\n";

size_t pcf (size_t start, size_t inc, size_t end)
{
    size_t total = 0;
#ifdef _OPENMP
#pragma omp parallel for schedule (dynamic)
#endif
    for (size_t i = start; i <= end; i += inc)
    {
        const bool p = isprime (i);
#ifdef _OPENMP
#pragma omp atomic
#endif
        total += p;
    }
    return total;
}

int main (int argc, char **argv)
{
    try
    {
        if (argc != 2)
            throw runtime_error (usage);

        Init ();
        const int NPROCS = COMM_WORLD.Get_size();
        const int ID = COMM_WORLD.Get_rank();
        if (ID == 0)
        {
            // divide the problem into NPROCS sub-problems
            const size_t N = atol (argv[1]);
            size_t total = 0;
            total += pcf (2, NPROCS, N);

            // send the parameters to each proc
            for (int dest_id = 1; dest_id < NPROCS; ++dest_id)
            {
                vector<unsigned long> msg (3);
                msg[0] = 2 + dest_id; // start
                msg[1] = NPROCS; // inc
                msg[2] = N; // end
                COMM_WORLD.Send (&msg[0], msg.size (), MPI_UNSIGNED_LONG, dest_id, 0);
            }

            // get back the answers
            for (int dest_id = 1; dest_id < NPROCS; ++dest_id)
            {
                unsigned long msg;
                COMM_WORLD.Recv (&msg, 1, MPI_UNSIGNED_LONG, dest_id, 0);
                total += msg;
            }

            cout << total << endl;
        }
        else
        {
            // get parameters from ID 0
            vector<unsigned long> msg (3);
            int src_id = 0;
            COMM_WORLD.Recv (&msg[0], msg.size (), MPI_UNSIGNED_LONG, src_id, 0);

            // send back the answer
            msg[0] = pcf (msg[0], msg[1], msg[2]);
            COMM_WORLD.Send (&msg[0], 1, MPI_UNSIGNED_LONG, 0, 0);
        }
        Finalize ();

        return 0;
    }
    catch (const exception &e)
    {
        cerr << e.what () << endl;
        return -1;
    }
}
