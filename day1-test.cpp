
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day1Test : public ::testing::Test{};

TEST_F( Day1Test, Part1_1 ) {
    istringstream is( "1122" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "3\n", os.str() );
}

TEST_F( Day1Test, Part1_2 ) {
    istringstream is( "1111" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "4\n", os.str() );
}

TEST_F( Day1Test, Part1_3 ) {
    istringstream is( "1234" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "0\n", os.str() );
}

TEST_F( Day1Test, Part1_4 ) {
    istringstream is( "91212129" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "9\n", os.str() );
}

TEST_F(Day1Test, PuzzleInputPart1 ) {
    ifstream is( "day1.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "1031\n", os.str() );
}

TEST_F( Day1Test, Part2_1 ) {
    istringstream is( "1212" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "6\n", os.str() );
}

TEST_F( Day1Test, Part2_2 ) {
    istringstream is( "1221" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "0\n", os.str() );
}

TEST_F( Day1Test, Part2_3 ) {
    istringstream is( "123425" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "4\n", os.str() );
}

TEST_F( Day1Test, Part2_4 ) {
    istringstream is( "123123" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "12\n", os.str() );
}

TEST_F( Day1Test, Part2_5 ) {
    istringstream is( "12131415" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "4\n", os.str() );
}

TEST_F(Day1Test, PuzzleInputPart2 ) {
    ifstream is( "day1.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1080\n", os.str() );
}

