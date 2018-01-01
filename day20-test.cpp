
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day20Test : public ::testing::Test{};

TEST_F( Day20Test, PuzzleInputPart1 ) {
    ifstream is( "day20.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "157\n", os.str() );
}

TEST_F( Day20Test, Description1_1 ) {
    stringstream is;
    ostringstream os;

    is << "p=< 3,0,0>, v=< 2,0,0>, a=<-1,0,0>\n";
    is << "p=< 4,0,0>, v=< 0,0,0>, a=<-2,0,0>\n";

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "0\n", os.str() );
}

TEST_F( Day20Test, PuzzleInputPart2 ) {
    ifstream is( "day20.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "499\n", os.str() );
}

TEST_F( Day20Test, Description2_1 ) {
    stringstream is;
    ostringstream os;

    is << "p=<-6,0,0>, v=< 3,0,0>, a=< 0,0,0>\n";
    is << "p=<-4,0,0>, v=< 2,0,0>, a=< 0,0,0>\n";
    is << "p=<-2,0,0>, v=< 1,0,0>, a=< 0,0,0>\n";
    is << "p=< 3,0,0>, v=<-1,0,0>, a=< 0,0,0>\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1\n", os.str() );
}
