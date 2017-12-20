

#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day14Test : public ::testing::Test{};

TEST_F( Day14Test, PuzzleInputPart1 ) {
    ifstream is( "day14.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "8074\n", os.str() );
}

TEST_F( Day14Test, Description1_1 ) {
    istringstream is( "flqrgnkx" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "8108\n", os.str() );
}

TEST_F( Day14Test, PuzzleInputPart2 ) {
    ifstream is( "day14.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1212\n", os.str() );
}

TEST_F( Day14Test, Description2_1 ) {
    istringstream is( "flqrgnkx" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1242\n", os.str() );
}
