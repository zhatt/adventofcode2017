#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day17Test : public ::testing::Test{};

TEST_F( Day17Test, PuzzleInputPart1 ) {
    ifstream is( "day17.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "2000\n", os.str() );
}

TEST_F( Day17Test, Description1_1 ) {
    istringstream is( "3\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "638\n", os.str() );
}

TEST_F( Day17Test, PuzzleInputPart2 ) {
    ifstream is( "day17.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "10242889\n", os.str() );
}
