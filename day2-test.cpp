
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day2Test : public ::testing::Test{};

TEST_F( Day2Test, Part1_1 ) {
    stringstream is;
    is << "5 1 9 5\n";
    is << "7 5 3\n";
    is << "2 4 6 8\n";

    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "18\n", os.str() );
}

TEST_F(Day2Test, PuzzleInputPart1 ) {
    ifstream is( "day2.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "45972\n", os.str() );
}

TEST_F( Day2Test, Part2_1 ) {
    stringstream is;
    is << "5 9 2 8\n";
    is << "9 4 7 3\n";
    is << "3 8 6 5\n";

    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "9\n", os.str() );
}

TEST_F(Day2Test, PuzzleInputPart2 ) {
    ifstream is( "day2.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "326\n", os.str() );
}

