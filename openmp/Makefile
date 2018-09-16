# @file Makefile
# @brief openmp example
# @author Jeff Perry <jeffsp@gmail.com>
# @version 1.0
# @date 2013-07-16

.SUFFIXES:
.PHONY: all run clean

CXX=icpc
OPTS=-O2 -std=c++11
OMP_OPTS=-qopenmp
SZ=10000000
N=256

all: f pf

%:: %.cc Makefile
	$(CXX) $(OPTS) -o "$@" "$<"

pf: f.cc Makefile
	$(CXX) $(OPTS) $(OMP_OPTS) -o pf f.cc

run: all
	./f $(N) $(SZ)
	./pf $(N) $(SZ)

clean:
	rm -f f pf
