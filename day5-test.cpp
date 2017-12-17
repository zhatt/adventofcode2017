
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day5Test : public ::testing::Test{};

TEST_F( Day5Test, PuzzleInputPart1 ) {
    ifstream is( "day5.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "315613\n", os.str() );
}

TEST_F( Day5Test, Description1_1 ) {
    istringstream is( "0\n3\n0\n1\n-3\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "5\n", os.str() );
}

TEST_F( Day5Test, PuzzleInputPart2 ) {
    ifstream is( "day5.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "22570529\n", os.str() );
}

TEST_F( Day5Test, Description2_1 ) {
    istringstream is( "0\n3\n0\n1\n-3\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "10\n", os.str() );
}
