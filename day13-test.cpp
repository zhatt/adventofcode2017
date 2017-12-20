
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day13Test : public ::testing::Test{};

TEST_F( Day13Test, PuzzleInputPart1 ) {
    ifstream is( "day13.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "1844\n", os.str() );
}

TEST_F( Day13Test, Description1_1 ) {
    stringstream is;
    ostringstream os;
    is << "0: 3\n";
    is << "1: 2\n";
    is << "4: 4\n";
    is << "6: 4\n";

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "24\n", os.str() );
}

TEST_F( Day13Test, PuzzleInputPart2 ) {
    ifstream is( "day13.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "3897604\n", os.str() );
}
