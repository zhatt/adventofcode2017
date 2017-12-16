
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day3Test : public ::testing::Test{};

TEST_F(Day3Test, PuzzleInputPart1 ) {
    ifstream is( "day3.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "480\n", os.str() );
}

TEST_F(Day3Test, PuzzleInputPart2 ) {
    ifstream is( "day3.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "349975\n", os.str() );
}

