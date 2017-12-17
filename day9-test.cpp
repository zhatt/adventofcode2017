
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day9Test : public ::testing::Test{};

TEST_F( Day9Test, PuzzleInputPart1 ) {
    ifstream is( "day9.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "10800\n", os.str() );
}

TEST_F( Day9Test, Description1_1 ) {
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

TEST_F( Day9Test, PuzzleInputPart2 ) {
    ifstream is( "day9.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "4522\n", os.str() );
}

TEST_F( Day9Test, Description2_1 ) {
    stringstream is;
    int characters = 0;

    is << "<>"; characters += 0;
    is << "<random characters>"; characters += 17;
    is << "<<<<>"; characters += 3;
    is << "<{!>}>"; characters += 2;
    is << "<!!>"; characters += 0;
    is << "<!!!>>", characters += 0;
    is << "<{o\"i!a,<{i<a>"; characters += 10;

    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    ostringstream expectedResult;
    expectedResult << characters << "\n";

    EXPECT_EQ( expectedResult.str(), os.str() );
}

