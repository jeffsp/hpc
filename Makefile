# @file Makefile
# @brief hpc example
# @author Jeff Perry <jeffsp@gmail.com>
# @version 1.0
# @date 2013-07-16

.SUFFIXES:
.PHONY: all run clean

all:
	$(MAKE) -C openmp
	$(MAKE) -C mpi
	$(MAKE) -C hybrid

run: all
	$(MAKE) -C openmp run
	$(MAKE) -C mpi run
	$(MAKE) -C hybrid run

clean:
	$(MAKE) -C openmp clean
	$(MAKE) -C mpi clean
	$(MAKE) -C hybrid clean
