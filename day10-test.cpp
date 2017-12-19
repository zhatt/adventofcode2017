
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day10Test : public ::testing::Test{};

TEST_F( Day10Test, PuzzleInputPart1 ) {
    ifstream is( "day10.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "52070\n", os.str() );
}
/*
TEST_F( Day10Test, Description1_1 ) {
    int score = 0;
    stringstream is;
    
    is << "{}\n"; score += 1;
    is << "{{{}}}\n"; score += 6;
    is << "{{},{}}\n"; score+=5;
    is << "{{{},{},{{}}}}\n"; score += 16;
    is << "{<a>,<a>,<a>,<a>}\n"; score += 1;
    is << "{{<ab>},{<ab>},{<ab>},{<ab>}}\n"; score += 9;
    is << "{{<!!>},{<!!>},{<!!>},{<!!>}}\n"; score += 9;
    is << "{{<a!>},{<a!>},{<a!>},{<ab>}}\n"; score += 3;

    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    ostringstream expectedResult;
    expectedResult << score << "\n";

    EXPECT_EQ( expectedResult.str(), os.str() );
}
*/
TEST_F( Day10Test, PuzzleInputPart2 ) {
    ifstream is( "day10.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "7f94112db4e32e19cf6502073c66f9bb\n", os.str() );
}

TEST_F( Day10Test, Description2_1 ) {
    istringstream is ( "\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "a2582a3a0e66e6e86e3812dcb672a272\n",  os.str() );
}

TEST_F( Day10Test, Description2_2 ) {
    istringstream is ( "AoC 2017\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "33efeb34ea91902bb2f59c9920caa6cd\n",  os.str() );
}

TEST_F( Day10Test, Description2_3 ) {
    istringstream is ( "1,2,3\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "3efbe78a8d82f29979031a4aa0b16a9d\n",  os.str() );
}

TEST_F( Day10Test, Description2_4 ) {
    istringstream is ( "1,2,4\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "63960835bcdc130f0b66d7ff4f6a5a8e\n",  os.str() );
}

