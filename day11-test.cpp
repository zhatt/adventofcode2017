
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day11Test : public ::testing::Test{};

TEST_F( Day11Test, PuzzleInputPart1 ) {
    ifstream is( "day11.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "743\n", os.str() );
}

TEST_F( Day11Test, Description1_1 ) {
    istringstream is( "ne,ne,ne\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "3\n", os.str() );
}

TEST_F( Day11Test, Description1_2 ) {
    istringstream is( "ne,ne,sw,sw\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "0\n", os.str() );
}

TEST_F( Day11Test, Description1_3 ) {
    istringstream is( "ne,ne,s,s\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "2\n", os.str() );
}

TEST_F( Day11Test, Description1_4 ) {
    istringstream is( "se,sw,se,sw,sw\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "3\n", os.str() );
}


TEST_F( Day11Test, PuzzleInputPart2 ) {
    ifstream is( "day11.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1493\n", os.str() );
}

