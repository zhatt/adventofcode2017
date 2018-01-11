
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day22Test : public ::testing::Test{};

TEST( Day22Test, PuzzleInputPart1 ) {
    ifstream is( "day22.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "5196\n", os.str() );
}

TEST( Day22Test, Description1_1 ) {
    stringstream is;
    ostringstream os;

    is << "..#\n";
    is << "#..\n";
    is << "...\n";

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "5587\n", os.str() );
}

TEST( Day22Test, PuzzleInputPart2 ) {
    ifstream is( "day22.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "2511633\n", os.str() );
}

TEST( Day22Test, Description2_1 ) {
    stringstream is;
    ostringstream os;

    is << "..#\n";
    is << "#..\n";
    is << "...\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "2511944\n", os.str() );
}

