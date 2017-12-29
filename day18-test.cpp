
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day18Test : public ::testing::Test{};

TEST_F( Day18Test, Dmp ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=0\n";
    r << "0:p=0\n";
    r << "1:pc=0\n";
    r << "1:p=1\n";
    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, SetIm ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 1\n";
    is << "set b 2\n";
    is << "set p 3\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=3\n";
    r << "0:a=1\n";
    r << "0:b=2\n";
    r << "0:p=3\n";
    r << "1:pc=3\n";
    r << "1:a=1\n";
    r << "1:b=2\n";
    r << "1:p=3\n";
    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, Set ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 1\n";
    is << "set b a\n";
    is << "set c 2\n";
    is << "set d c\n";
    is << "set c c\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=5\n";
    r << "0:a=1\n";
    r << "0:b=1\n";
    r << "0:c=2\n";
    r << "0:d=2\n";
    r << "0:p=0\n";
    r << "1:pc=5\n";
    r << "1:a=1\n";
    r << "1:b=1\n";
    r << "1:c=2\n";
    r << "1:d=2\n";
    r << "1:p=1\n";
    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, SetNeg ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a -1\n";
    is << "set b -2\n";
    is << "set c a\n";
    is << "set d b\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=4\n";
    r << "0:a=-1\n";
    r << "0:b=-2\n";
    r << "0:c=-1\n";
    r << "0:d=-2\n";
    r << "0:p=0\n";
    r << "1:pc=4\n";
    r << "1:a=-1\n";
    r << "1:b=-2\n";
    r << "1:c=-1\n";
    r << "1:d=-2\n";
    r << "1:p=1\n";
    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, Add ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "add a 1\n";
    is << "add b a\n";
    is << "add c 2\n";
    is << "add d c\n";
    is << "add d a\n";
    is << "add d 8\n";
    is << "add c c\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=7\n";
    r << "0:a=1\n";
    r << "0:b=1\n";
    r << "0:c=4\n";
    r << "0:d=11\n";
    r << "0:p=0\n";
    r << "1:pc=7\n";
    r << "1:a=1\n";
    r << "1:b=1\n";
    r << "1:c=4\n";
    r << "1:d=11\n";
    r << "1:p=1\n";
    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, AddNeg ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "add a 1\n";
    is << "add b -4\n";
    is << "add a b\n";
    is << "add b 4\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=4\n";
    r << "0:a=-3\n";
    r << "0:b=0\n";
    r << "0:p=0\n";
    r << "1:pc=4\n";
    r << "1:a=-3\n";
    r << "1:b=0\n";
    r << "1:p=1\n";
    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, Mul ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 2\n";
    is << "set b 3\n";
    is << "set c 3\n";
    is << "set d 1\n";
    is << "mul a 5\n";
    is << "mul b a\n";
    is << "mul d a\n";
    is << "mul d a\n";
    is << "mul d 8\n";
    is << "mul c 3\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=10\n";
    r << "0:a=10\n";
    r << "0:b=30\n";
    r << "0:c=9\n";
    r << "0:d=800\n";
    r << "0:p=0\n";

    r << "1:pc=10\n";
    r << "1:a=10\n";
    r << "1:b=30\n";
    r << "1:c=9\n";
    r << "1:d=800\n";
    r << "1:p=1\n";

    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, MulNeg ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a -2\n";
    is << "set b 3\n";
    is << "set c -3\n";
    is << "mul a 5\n";
    is << "mul b -2\n";
    is << "mul c c\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=6\n";
    r << "0:a=-10\n";
    r << "0:b=-6\n";
    r << "0:c=9\n";
    r << "0:p=0\n";

    r << "1:pc=6\n";
    r << "1:a=-10\n";
    r << "1:b=-6\n";
    r << "1:c=9\n";
    r << "1:p=1\n";

    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, Mod ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 20\n";
    is << "set b 30\n";
    is << "mod a 5\n";
    is << "mod b 8\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=4\n";
    r << "0:a=0\n";
    r << "0:b=6\n";
    r << "0:p=0\n";

    r << "1:pc=4\n";
    r << "1:a=0\n";
    r << "1:b=6\n";
    r << "1:p=1\n";

    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, ModNeg ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a -20\n";
    is << "set b -30\n";
    is << "set c -30\n";
    is << "mod a 5\n";
    is << "mod b 8\n";
    is << "mod c -8\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=6\n";
    r << "0:a=0\n";
    r << "0:b=-6\n";
    r << "0:c=-6\n";
    r << "0:p=0\n";

    r << "1:pc=6\n";
    r << "1:a=0\n";
    r << "1:b=-6\n";
    r << "1:c=-6\n";
    r << "1:p=1\n";

    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, Snd1 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "snd 20\n";
    is << "snd 30\n";
    is << "snd 40\n";
    is << "rcv x\n";
    is << "rcv x\n";
    is << "rcv x\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=6\n";
    r << "0:p=0\n";
    r << "0:x=40\n";

    r << "1:pc=6\n";
    r << "1:p=1\n";
    r << "1:x=40\n";

    r << "3\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, SndRcv1 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "snd p\n";
    is << "rcv x\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=2\n";
    r << "0:p=0\n";
    r << "0:x=1\n";

    r << "1:pc=2\n";
    r << "1:p=1\n";
    r << "1:x=0\n";

    r << "1\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, Jgz1 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "jgz 1 1\n";
    is << "add a 1\n";
    is << "jgz 1 1\n";
    is << "add a 1\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=4\n";
    r << "0:a=2\n";
    r << "0:p=0\n";

    r << "1:pc=4\n";
    r << "1:a=2\n";
    r << "1:p=1\n";

    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, Jgz2 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "jgz 1 2\n";
    is << "add a 1\n";
    is << "jgz 1 1\n";
    is << "add a 1\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=4\n";
    r << "0:a=1\n";
    r << "0:p=0\n";

    r << "1:pc=4\n";
    r << "1:a=1\n";
    r << "1:p=1\n";

    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( Day18Test, Jgz3_negoffset ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "jgz 1 4\n";
    is << "dmp\n";
    is << "rcv x\n";
    is << "jgz 1 1\n";
    is << "add a 5\n";
    is << "jgz 1 -4\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=1\n";
    r << "0:a=5\n";
    r << "0:p=0\n";

    r << "1:pc=1\n";
    r << "1:a=5\n";
    r << "1:p=1\n";

    r << "0\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( r.str(), os.str() );
}

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

TEST_F( Day18Test, PuzzleInputPart2 ) {
    ifstream is( "day18.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "7112\n", os.str() );
}

TEST_F( Day18Test, Description2_1 ) {
    stringstream is;

    is << "snd 1\n";
    is << "snd 2\n";
    is << "snd p\n";
    is << "rcv a\n";
    is << "rcv b\n";
    is << "rcv c\n";
    is << "rcv d\n";

    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "3\n", os.str() );
}

