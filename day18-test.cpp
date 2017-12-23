
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day18Test : public ::testing::Test{};

TEST_F( Day18Test, PuzzleInputPart1 ) {
    ifstream is( "day18.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "3188\n", os.str() );
}

TEST_F( Day18Test, Description1_1 ) {
     stringstream is;
     is << "set a 1\n";
     is << "add a 2\n";
     is << "mul a a\n";
     is << "mod a 5\n";
     is << "snd a\n";
     is << "set a 0\n";
     is << "rcv a\n";
     is << "jgz a -1\n";
     is << "set a 1\n";
     is << "jgz a -2\n";

    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "4\n", os.str() );
}
/*
TEST_F( Day18Test, PuzzleInputPart2 ) {
    ifstream is( "day18.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "10242889\n", os.str() );
}
*/
