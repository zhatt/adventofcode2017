
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day8Test : public ::testing::Test{};

TEST_F( Day8Test, PuzzleInputPart1 ) {
    ifstream is( "day8.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "7296\n", os.str() );
}

TEST_F( Day8Test, Description1_1 ) {
    stringstream is;
    is << "b inc 5 if a > 1\n";
    is << "a inc 1 if b < 5\n";
    is << "c dec -10 if a >= 1\n";
    is << "c inc -20 if c == 10\n";
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "1\n", os.str() );
}

TEST_F( Day8Test, PuzzleInputPart2 ) {
    ifstream is( "day8.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "8186\n", os.str() );
}

TEST_F( Day8Test, Description2_1 ) {
    stringstream is;
    is << "b inc 5 if a > 1\n";
    is << "a inc 1 if b < 5\n";
    is << "c dec -10 if a >= 1\n";
    is << "c inc -20 if c == 10\n";
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "10\n", os.str() );
}

