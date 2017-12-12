
CXXFLAGS=-Wall -Werror -g

all: \
	day1.1 day1.2 \
	day2.1 day2.2 \
	day3.1 day3.2 \
	day4.1 day4.2 \
	day5.1 day5.2 \
	day6.1 day6.2 \
	day7.1 day7.2 \
	day8.1 day8.2 \
	day9.1 day9.2 \
	day10.1 day10.2 \
	day11.1 day11.2 \
	day12.1 day12.2

day1.1: day1.1.cpp
day1.2: day1.2.cpp
day2.1: day2.1.cpp
day2.2: day2.2.cpp
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
day12.1: day12.1.cpp graph.cpp
day12.2: day12.2.cpp graph.cpp

graph.h : graph.cpp
