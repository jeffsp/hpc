/// @file f.cc
/// @brief test mpi functionality
/// @author Jeff Perry <jeffsp@gmail.com>
/// @version 1.0
/// @date 2013-07-16

#include <mpi.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace MPI;

int main (int argc, char **argv)
{
    try
    {
        Init ();
        const int NPROCS = COMM_WORLD.Get_size();
        const int ID = COMM_WORLD.Get_rank();
        if (ID == 0)
        {
            clog << "nprocs " << NPROCS << endl;
            for (int dest_id = 1; dest_id < NPROCS; ++dest_id)
            {
                vector<unsigned long> msg (1);
                msg[0] = dest_id;
                clog << "id " << ID << " sending " << msg[0] << " to id " << dest_id << endl;
                COMM_WORLD.Send (&msg[0], msg.size (), MPI_UNSIGNED_LONG, dest_id, 0);
            }
        }
        else
        {
            vector<unsigned long> msg (1);
            int src_id = 0;
            COMM_WORLD.Recv (&msg[0], msg.size (), MPI_UNSIGNED_LONG, src_id, 0);
            clog << "id " << ID << " received " << msg[0] << " from id " << src_id << endl;
        }
        Finalize ();
    }
    catch (const exception &e)
    {
        cerr << e.what () << endl;
        return -1;
    }

    return 0;
}
