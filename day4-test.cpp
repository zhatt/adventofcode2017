
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day4Test : public ::testing::Test{};

TEST_F(Day4Test, PuzzleInputPart1 ) {
    ifstream is( "day4.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "455\n", os.str() );
}

TEST_F(Day4Test, Description1_1 ) {
    istringstream is( "aa bb cc dd ee\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "1\n", os.str() );
}

TEST_F(Day4Test, Description1_2 ) {
    istringstream is( "aa bb cc dd aa\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "0\n", os.str() );
}

TEST_F(Day4Test, Description1_3 ) {
    istringstream is( "aa bb cc dd aaa\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "1\n", os.str() );
}

TEST_F(Day4Test, Description1_4 ) {
    stringstream is;
    is << "aa bb cc dd ee\n";
    is << "aa bb cc dd aa\n";
    is << "aa bb cc dd aaa\n";

    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "2\n", os.str() );
}

TEST_F(Day4Test, PuzzleInputPart2 ) {
    ifstream is( "day4.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "186\n", os.str() );
}

TEST_F(Day4Test, Description2_1 ) {
    istringstream is( "abcde fghij\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1\n", os.str() );
}

TEST_F(Day4Test, Description2_2 ) {
    istringstream is( "abcde xyz ecdab\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "0\n", os.str() );
}

TEST_F(Day4Test, Description2_3 ) {
    istringstream is( "a ab abc abd abf abj\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1\n", os.str() );
}

TEST_F(Day4Test, Description2_4 ) {
    istringstream is( "iiii oiii ooii oooi oooo\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1\n", os.str() );
}

TEST_F(Day4Test, Description2_5 ) {
    istringstream is( "oiii ioii iioi iiio\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "0\n", os.str() );
}

TEST_F(Day4Test, Description2_6 ) {
    stringstream is;
    is << "abcde fghij\n";
    is << "abcde xyz ecdab\n";
    is << "a ab abc abd abf abj\n";
    is << "iiii oiii ooii oooi oooo\n";
    is << "oiii ioii iioi iiio\n";
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "3\n", os.str() );
}
