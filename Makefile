
LDFLAGS = -lstdc++

CXXFLAGS=-Wall -Werror -Og -g

PROGS += day1
PROGS += day2
PROGS += day3
PROGS += day4
PROGS += day5
PROGS += day6
PROGS += day7
PROGS += day8
PROGS += day9
PROGS += day10.1 day10.2
PROGS += day11
PROGS += day12.1 day12.2
#PROGS += day13.1 day13.2

TESTPROGS += day1-test day2-test day3-test day4-test day5-test
TESTPROGS += day6-test day7-test day8-test day9-test
TESTPROGS += day11-test

all: ${PROGS} ${TESTPROGS}

test: $(TESTPROGS:-test=-test.out)

clean:
	rm -f ${PROGS} ${TESTPROGS} *.o ${DEPDIR}/* *-test.out

day1: day1.o main.o
day2: day2.o main.o
day3: day3.o main.o
day4: day4.o main.o
day5: day5.o main.o
day6: day6.o main.o
day7: day7.o main.o
day8: day8.o main.o
day9: day9.o main.o
day10.1: day10.1.cpp
day10.2: day10.2.cpp
day11: day11.o main.o
day12.1: day12.1.cpp
day12.2: day12.2.cpp
day13.1: day13.1.cpp
day13.2: day13.2.cpp

day12.1.cpp: graph.h
day12.2.cpp: graph.h

day1-test: day1-test.o day1.o testmain.o -lgtest
day2-test: day2-test.o day2.o testmain.o -lgtest
day3-test: day3-test.o day3.o testmain.o -lgtest
day4-test: day4-test.o day4.o testmain.o -lgtest
day5-test: day5-test.o day5.o testmain.o -lgtest
day6-test: day6-test.o day6.o testmain.o -lgtest
day7-test: day7-test.o day7.o testmain.o -lgtest
day8-test: day8-test.o day8.o testmain.o -lgtest
day9-test: day9-test.o day9.o testmain.o -lgtest

day11-test: day11-test.o day11.o testmain.o -lgtest

%-test.out: %-test
	set -o pipefail; \
	"./$<" | tee "$@.tmp"; \
	[[ $$? -eq 0 ]] && mv "$@.tmp" "$@" || exit 1

include Makefile.inc
