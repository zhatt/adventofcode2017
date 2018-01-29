
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day23Test : public ::testing::Test{};

TEST_F( Day23Test, PuzzleInputPart1 ) {
    ifstream is( "day23.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "4225\n", os.str() );
}

TEST_F( Day23Test, PuzzleInputPart2 ) {
    ifstream is( "day23.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "905\n", os.str() );
}
