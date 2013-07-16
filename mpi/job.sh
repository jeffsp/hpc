#!/bin/bash

# @file job.sh
# @brief mpi job submission shell script
# @author Jeff Perry <jeffsp@gmail.com>
# @version 1.0
# @date 2011-08-09

# see: http://www.tacc.utexas.edu/user-services/user-guides/stampede-user-guide#running-envs-mpi

#SBATCH -J hpc_mpi                              # job name
#SBATCH -o out.%j                               # output file name
#SBATCH -e err.%j                               # error file name
#SBATCH -n 64                                   # total tasks, divide by 16 to get number of nodes
#SBATCH -p development                          # queue
#SBATCH -t 00:01:00                             # run time (hh:mm:ss)
#SBATCH --mail-user=jeffsp+stampede@gmail.com   # filter messages with +stampede in the to: field
#SBATCH --mail-type=begin                       # email me when the job starts
#SBATCH --mail-type=end                         # email me when the job finishes
ibrun ./f
