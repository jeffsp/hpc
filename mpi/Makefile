# @file Makefile
# @brief mpi example
# @author Jeff Perry <jeffsp@gmail.com>
# @version 1.0
# @date 2013-07-16

.SUFFIXES:
.PHONY: all run clean

CXX=mpicxx
OPTS=-xhost -O2 -std=c++0x
CMD=sbatch job.sh

all: f

%:: %.cc Makefile
	$(CXX) $(OPTS) -o "$@" "$<"

run: all
	$(CMD)

clean:
	rm -f ./f err.* out.*
