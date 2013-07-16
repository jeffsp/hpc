#!/bin/bash

# @file job.sh
# @brief hybrid job submission shell script
# @author Jeff Perry <jeffsp@gmail.com>
# @version 1.0
# @date 2013-07-16

# see: see http://www.tacc.utexas.edu/user-services/user-guides/stampede-user-guide#running-envs-hybrid

# ranger: 3936x16-way 32GB SMP compute nodes (62,976 total cores)
# lonestar: 1888x12-way 12GB SMP compute nodes (22,656 total cores)
# stampede(E5): 6400x16-way 32GB SMP compute nodes (102,400 total cores)
# stampede(MIC Phi): 6400x61-way 8GB SMP compute nodes (i390,400 total cores)

#SBATCH -J hpc_hybrid                           # job name
#SBATCH -o out.%j                               # output file name
#SBATCH -e err.%j                               # error file name
export OMP_NUM_THREADS=16  						# number of threads per task
#SBATCH -n 8                                    # number of tasks
#SBATCH -N 8                                    # number of nodes, n/N=tasks per node
#SBATCH -p development                          # queue
#SBATCH -t 00:10:00                             # run time (hh:mm:ss)
#SBATCH --mail-user=jeffsp+stampede@gmail.com   # filter messages with +stampede in the to: field
#SBATCH --mail-type=begin                       # email me when the job starts
#SBATCH --mail-type=end                         # email me when the job finishes

ibrun tacc_affinity ./pcf3		 10000000
