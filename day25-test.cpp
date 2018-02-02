
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"

using namespace std;

class Day25Test : public ::testing::Test{};

TEST( Day25Test, PuzzleInputPart1 ) {
    ifstream is( "day25.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "5593\n", os.str() );
}

TEST( Day25Test, Description1_1 ) {
    const char* input =
R"(Begin in state A.
Perform a diagnostic checksum after 6 steps.

In state A:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state B.
  If the current value is 1:
    - Write the value 0.
    - Move one slot to the left.
    - Continue with state B.

In state B:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the left.
    - Continue with state A.
  If the current value is 1:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state A.
)";

    istringstream is( input );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "3\n", os.str() );
}
