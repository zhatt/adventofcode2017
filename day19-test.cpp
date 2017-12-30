
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day19Test : public ::testing::Test{};

TEST_F( Day19Test, PuzzleInputPart1 ) {
    ifstream is( "day19.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "VEBTPXCHLI\n", os.str() );
}

TEST_F( Day19Test, Description1_1 ) {
    stringstream is;
    ostringstream os;

    is << "     |         \n";
    is << "     |  +--+   \n";
    is << "     A  |  C   \n";
    is << " F---|----E|--+\n";
    is << "     |  |  |  D\n";
    is << "     +B-+  +--+\n";

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "ABCDEF\n", os.str() );
}

TEST_F( Day19Test, PuzzleInputPart2 ) {
    ifstream is( "day19.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "18702\n", os.str() );
}

TEST_F( Day19Test, Description2_1 ) {
    stringstream is;
    ostringstream os;

    is << "     |         \n";
    is << "     |  +--+   \n";
    is << "     A  |  C   \n";
    is << " F---|----E|--+\n";
    is << "     |  |  |  D\n";
    is << "     +B-+  +--+\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "38\n", os.str() );
}

