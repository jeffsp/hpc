# @file Makefile
# @brief mpi example
# @author Jeff Perry <jeffsp@gmail.com>
# @version 1.0
# @date 2011-08-09

.SUFFIXES:
.PHONY: all run clean

CXX=mpicxx
OPTS=-xhost -O2
CMD=sbatch job.sh

all:
	$(CXX) $(OPTS) -o f f.cc

run:
	$(CMD)

clean:
	rm -f ./f err.* out.*
