
LDFLAGS = -lstdc++

CXXFLAGS=-Wall -Werror -Og -g

PROGS += day1
PROGS += day2
PROGS += day3.1 day3.2
PROGS += day4.1 day4.2
PROGS += day5.1 day5.2
PROGS += day6.1 day6.2
PROGS += day7.1 day7.2
PROGS += day8.1 day8.2
PROGS += day9.1 day9.2
PROGS += day10.1 day10.2
PROGS += day11.1 day11.2
PROGS += day12.1 day12.2
PROGS += day13.1 day13.2

TESTPROGS += day1-test

SRCS += day1.cpp
SRCS +=	main.cpp
SRCS += test-day1.cpp
SRCS +=	testmain.cpp

all: ${PROGS} ${TESTPROGS}

test: day1-test.out

clean:
	rm -f ${PROGS} ${TESTPROGS} *.o ${DEPDIR}/*

day1: day1.o main.o
day2: day2.o
day3.1: day3.1.cpp
day3.2: day3.2.cpp
day4.1: day4.1.cpp
day4.2: day4.2.cpp
day5.1: day5.1.cpp
day5.2: day5.2.cpp
day6.1: day6.1.cpp
day6.2: day6.2.cpp
day7.1: day7.1.cpp
day7.2: day7.2.cpp
day8.1: day8.1.cpp
day8.2: day8.2.cpp
day9.1: day9.1.cpp
day10.1: day10.1.cpp
day10.2: day10.2.cpp
day11.1: day11.1.cpp
day11.2: day11.2.cpp
day12.1: day12.1.cpp
day12.2: day12.2.cpp
day13.1: day13.1.cpp
day13.2: day13.2.cpp

day12.1.cpp: graph.h
day12.2.cpp: graph.h

day1-test: day1-test.o day1.o testmain.o -lgtest

day1-test.out: day1-test
	./day1-test | tee day1-test.out


include Makefile.inc
