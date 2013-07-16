# @file Makefile
# @brief hybrid hpc example
# @author Jeff Perry <jeffsp@gmail.com>
# @version 1.0
# @date 2013-07-16

# Compute the prime counting function using a naive method of testing for
# primality.  Benchmark the function using different HPC methods.
#
# Here are values for pcf(x) that you may use to check the code:
#
# x     pcf(x)
# 10    4
# 10^2  25
# 10^3  168
# 10^4  1,229
# 10^5  9,592
# 10^6  78,498
# 10^7  664,579
# 10^8  5,761,455
# 10^9  50,847,534
# 10^10 455,052,511
# 10^11 4,118,054,813
# 10^12 37,607,912,018
# 10^13 346,065,536,839
# 10^14 3,204,941,750,802
# 10^15 29,844,570,422,669
# 10^16 279,238,341,033,925
# 10^17 2,623,557,157,654,233
# 10^18 24,739,954,287,740,860
# 10^19 234,057,667,276,344,607
# 10^20 2,220,819,602,560,918,840
# 10^21 21,127,269,486,018,731,928
# 10^22 201,467,286,689,315,906,290
# 10^23 1,925,320,391,606,803,968,923
# 10^24 18,435,599,767,349,200,867,866

.SUFFIXES:
.PHONY: all check run clean

CXX=mpicxx
OPTS=-xhost -O2
CMD=sbatch job.sh

CCFILES=$(shell ls -1 *.cc)
TARGETS=$(basename $(CCFILES))

all: $(TARGETS)

check: all
	@test $$(./pcf1 1000000) -eq 78498
	@test $$(./pcf2 1000000) -eq 78498
	@test $$(./pcf3 1000000) -eq 78498
	@echo "all checks passed"

%:: %.cc isprime.h Makefile
	$(CXX) $(OPTS) -o "$@" "$<"

run: $(TARGETS)
	./pcf1 1000000
	./pcf2 1000000
	$(CMD)

clean:
	rm -f $(TARGETS)
	rm -f out.*
	rm -f err.*
