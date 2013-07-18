/// @file f.cc
/// @brief Simple MPI example
/// @author Jeff Perry <jeffsp@gmail.com>
/// @version 1.0
/// @date 2013-07-16

#include <algorithm>
#include <cstdint>
#include <mpi.h>
#include <numeric>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;
using namespace MPI;

int main (int argc, char **argv)
{
    try
    {
        // initialize MPI
        Init ();
        COMM_WORLD.Set_errhandler (MPI::ERRORS_THROW_EXCEPTIONS);

        // get information about our world
        const int NPROCS = COMM_WORLD.Get_size ();
        const int ID = COMM_WORLD.Get_rank ();

        // number of tasks
        const size_t NTASKS = NPROCS - 1;

        // size of each task
        const size_t SZ = 1024 * 1024;

        if (ID == 0)
        {
            // generate a vector of random numbers
            vector<uint32_t> n (SZ * NTASKS);
            generate (n.begin (), n.end (), rand);

            cout << "problem size is " << n.size () << endl;
            cout << "dividing problem into " << NTASKS
                << " tasks of size " << SZ << endl;

            // send a piece of the vector to each task
            for (int task = 0; task < NTASKS; ++task)
            {
                clog << "sending " << SZ << " numbers to id " << task + 1 << endl;
                COMM_WORLD.Send (&n[task * SZ], SZ, MPI_UINT32_T, task + 1, 0);
            }

            // get back results from each task and update our final result
            uint32_t sum = 0;
            for (int task = 0; task < NTASKS; ++task)
            {
                uint32_t x;
                COMM_WORLD.Recv (&x, 1, MPI_UINT32_T, task + 1, 0);
                clog << "received result from id " << task + 1 << endl;
                // update results
                sum += x;
            }

            // check our answer
            if (sum != accumulate (n.begin (), n.end (), uint32_t (0)))
                throw runtime_error ("failed");

            // success
            cout << "success, the answer is " << sum << endl;
        }
        else
        {
            // read a vector from ID 0
            vector<uint32_t> n (SZ);
            COMM_WORLD.Recv (&n[0], n.size (), MPI_UINT32_T, 0, 0);

            // perform the task
            uint32_t sum = accumulate (n.begin (), n.end (), uint32_t (0));

            // send back the results
            COMM_WORLD.Send (&sum, 1, MPI_UINT32_T, 0, 0);
        }
        Finalize ();
    }
    catch (Exception e )
    {
        cerr << "MPI error: " << e.Get_error_string() << e.Get_error_code() << endl;
        MPI::COMM_WORLD.Abort (-1);
        return -1;
    }
    catch (const exception &e)
    {
        cerr << e.what () << endl;
        return -1;
    }

    return 0;
}
