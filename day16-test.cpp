

#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day16Test : public ::testing::Test{};

TEST_F( Day16Test, PuzzleInputPart1 ) {
    ifstream is( "day16.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "lbdiomkhgcjanefp\n", os.str() );
}

TEST_F( Day16Test, PuzzleInputPart2 ) {
    ifstream is( "day16.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "ejkflpgnamhdcboi\n", os.str() );
}
