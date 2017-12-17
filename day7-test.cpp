
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day7Test : public ::testing::Test{};

TEST_F( Day7Test, PuzzleInputPart1 ) {
    ifstream is( "day7.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "eqgvf\n", os.str() );
}

TEST_F( Day7Test, Description1_1 ) {
    stringstream is;
    is << "pbga (66)\n";
    is << "xhth (57)\n";
    is << "ebii (61)\n";
    is << "havc (66)\n";
    is << "ktlj (57)\n";
    is << "fwft (72) -> ktlj, cntj, xhth\n";
    is << "qoyq (66)\n";
    is << "padx (45) -> pbga, havc, qoyq\n";
    is << "tknk (41) -> ugml, padx, fwft\n";
    is << "jptl (61)\n";
    is << "ugml (68) -> gyxo, ebii, jptl\n";
    is << "gyxo (61)\n";
    is << "cntj (57)\n";
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "tknk\n", os.str() );
}

TEST_F( Day7Test, PuzzleInputPart2 ) {
    ifstream is( "day7.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "757\n", os.str() );
}

TEST_F( Day7Test, Description2_1 ) {
    stringstream is;
    is << "pbga (66)\n";
    is << "xhth (57)\n";
    is << "ebii (61)\n";
    is << "havc (66)\n";
    is << "ktlj (57)\n";
    is << "fwft (72) -> ktlj, cntj, xhth\n";
    is << "qoyq (66)\n";
    is << "padx (45) -> pbga, havc, qoyq\n";
    is << "tknk (41) -> ugml, padx, fwft\n";
    is << "jptl (61)\n";
    is << "ugml (68) -> gyxo, ebii, jptl\n";
    is << "gyxo (61)\n";
    is << "cntj (57)\n";
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "60\n", os.str() );
}
