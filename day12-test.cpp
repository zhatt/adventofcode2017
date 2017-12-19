
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day12Test : public ::testing::Test{};

TEST_F( Day12Test, PuzzleInputPart1 ) {
    ifstream is( "day12.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "175\n", os.str() );
}

TEST_F( Day12Test, Description1_1 ) {
    stringstream is;
    ostringstream os;

    is << "0 <-> 2\n";
    is << "1 <-> 1\n";
    is << "2 <-> 0, 3, 4\n";
    is << "3 <-> 2, 4\n";
    is << "4 <-> 2, 3, 6\n";
    is << "5 <-> 6\n";
    is << "6 <-> 4, 5\n";

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "6\n", os.str() );
}

TEST_F( Day12Test, PuzzleInputPart2 ) {
    ifstream is( "day12.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "213\n", os.str() );
}

TEST_F( Day12Test, Description2_1 ) {
    stringstream is;
    ostringstream os;

    is << "0 <-> 2\n";
    is << "1 <-> 1\n";
    is << "2 <-> 0, 3, 4\n";
    is << "3 <-> 2, 4\n";
    is << "4 <-> 2, 3, 6\n";
    is << "5 <-> 6\n";
    is << "6 <-> 4, 5\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "2\n", os.str() );
}

