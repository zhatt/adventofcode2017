/*
--- Day 8: I Heard You Like Registers ---

You receive a signal directly from the CPU. Because of your recent
assistance with jump instructions, it would like you to compute the result
of a series of unusual register instructions.

Each instruction consists of several parts: the register to modify, whether
to increase or decrease that register's value, the amount by which to
increase or decrease it, and a condition. If the condition fails, skip the
instruction without modifying the register. The registers all start at 0.
The instructions look like this:

b inc 5 if a > 1
a inc 1 if b < 5
c dec -10 if a >= 1
c inc -20 if c == 10

These instructions would be processed as follows:

  - Because a starts at 0, it is not greater than 1, and so b is not
    modified.
  - a is increased by 1 (to 1) because b is less than 5 (it is 0).
  - c is decreased by -10 (to 10) because a is now greater than or equal
    to 1 (it is 1).
  - c is increased by -20 (to -10) because c is equal to 10.

After this process, the largest value in any register is 1.

You might also encounter <= (less than or equal to) or != (not equal to).
However, the CPU doesn't have the bandwidth to tell you what all the
registers are named, and leaves that to you to determine.

What is the largest value in any register after completing the instructions
in your puzzle input?

--- Part Two ---

To be safe, the CPU also needs to know the highest value held in any
register during this process so that it can decide how much memory to
allocate to these operations. For example, in the above instructions, the
highest value ever held was 10 (in register c after the third instruction
was evaluated).
*/


#include <cassert>
#include <iostream>
#include <map>
#include <sstream>

#include "main.h"

using namespace std;

int mainfunc( istream& is, ostream& os, Part part ) {

    map<string,int> registers;

    int highest = 0;

    string line;
    while( getline( is, line ) ) {
        istringstream parser( line );

        string destReg;
        string op;
        int amount;
        string ifDummy;
        string testReg;
        string condition;
        int testValue;

        parser >> destReg;
        parser >> op;
        parser >> amount;
        parser >> ifDummy;
        parser >> testReg;
        parser >> condition;
        parser >> testValue;

        assert( ifDummy == "if" );
        assert( is );

        bool result;
        if ( condition == "==" ) {
            result = registers[ testReg ] == testValue;
        } else if ( condition == "!=" ) {
            result = registers[ testReg ] != testValue;
        } else if ( condition == ">" ) {
            result = registers[ testReg ] > testValue;
        } else if ( condition == ">=" ) {
            result = registers[ testReg ] >= testValue;
        } else if ( condition == "<" ) {
            result = registers[ testReg ] < testValue;
        } else if ( condition == "<=" ) {
            result = registers[ testReg ] <= testValue;
        } else {
            assert( ! "unknown operator" );
        }

        if ( ! result ) continue;

        if ( op == "inc" ) {
            registers[ destReg ] += amount;
        } else if ( op == "dec" ) {
            registers[ destReg ] -= amount;
        } else {
            assert( ! "unknown op" );
        }

        if ( registers[ destReg ] > highest ) {
            highest = registers[ destReg ];
        }
    }

    assert( registers.size() );
    int largest = ( registers.begin() )->second;
    for ( auto reg : registers ) {
        if ( reg.second > largest ) largest = reg.second;
    }

    if ( part == Part::PART1 ) {
        os << largest << endl;
    } else {
        os << highest << endl;
    }

    return 0;
}
