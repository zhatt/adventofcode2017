
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day6Test : public ::testing::Test{};

TEST_F( Day6Test, PuzzleInputPart1 ) {
    ifstream is( "day6.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "11137\n", os.str() );
}

TEST_F( Day6Test, Description1_1 ) {
    istringstream is( "0 2 7 0\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "5\n", os.str() );
}

TEST_F( Day6Test, PuzzleInputPart2 ) {
    ifstream is( "day6.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1037\n", os.str() );
}

TEST_F( Day6Test, Description2_1 ) {
    istringstream is( "0 2 7 0\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "4\n", os.str() );
}
