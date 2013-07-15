# @file Makefile
# @brief openmp example
# @author Jeff Perry <jeffsp@gmail.com>
# @version 1.0
# @date 2011-08-09

.SUFFIXES:
.PHONY: all run clean

CXX=icpc
OPTS=-O3 -std=c++0x
OMP_OPTS=-openmp

all:
	$(CXX) $(OPTS) -o f f.cc
	$(CXX) $(OPTS) $(OMP_OPTS) -o pf f.cc

run:
	./f 256 10000000
	./pf 256 10000000

clean:
	rm -f f pf
