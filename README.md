hpc
===

High performance C++ computing examples developed for resources available from the Texas Advanced Computing Center at the University of Texas

These examples were developed for the Stampede system.

The TACC Stampede system is a 10 PFLOPS (PF) Dell Linux Cluster based on 6,400+ Dell PowerEdge server nodes, each
outfitted with 2 Intel Xeon E5 (Sandy Bridge) processors and an Intel Xeon Phi Coprocessor (MIC Architecture).

openmp
------

Simple example of running a shared memory application using OpenMP.

mpi
---

Simple example of running a distributed, single-program multiple-data (SPMD) application using MPI.

hybrid
------

Example of combining the above two applications.  The application program implements an extremely naive prime counting
function and allows the user to run it either as a single threaded, multi-threaded (OpenMP), or hybrid application
(OpenMP+MPI).
