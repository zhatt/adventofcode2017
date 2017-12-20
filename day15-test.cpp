

#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "day15.h"
#include "main.h"

using namespace std;

class Day15Test : public ::testing::Test{};

TEST_F( Day15Test, PuzzleInputPart1 ) {
    ifstream is( "day15.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "577\n", os.str() );
}

TEST_F( Day15Test, Description1_1 ) {
    unsigned numMatches = runTrial( 5, 16807, 65, 1, 48271, 8921, 1 );

    EXPECT_EQ( 1, numMatches );
}

TEST_F( Day15Test, PuzzleInputPart2 ) {
    ifstream is( "day15.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "316\n", os.str() );
}

TEST_F( Day15Test, Description2_1 ) {
    unsigned numMatches = runTrial( 1055, 16807, 65, 4, 48271, 8921, 8 );

    EXPECT_EQ( 0, numMatches );
}

TEST_F( Day15Test, Description2_2 ) {
    unsigned numMatches = runTrial( 1056, 16807, 65, 4, 48271, 8921, 8 );

    EXPECT_EQ( 1, numMatches );
}

TEST_F( Day15Test, Description2_3 ) {
    unsigned numMatches = runTrial( 5000000, 16807, 65, 4, 48271, 8921, 8 );

    EXPECT_EQ( 309, numMatches );
}
