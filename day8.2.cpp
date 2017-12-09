/*
--- Part Two ---
To be safe, the CPU also needs to know the highest value held in any register during this process so that it can decide how much memory to allocate to these operations. For example, in the above instructions, the highest value ever held was 10 (in register c after the third instruction was evaluated).
*/


#include <cassert>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

int main() {

    map<string,int> registers;

    int highest = 0;

    string line;
    while( getline( cin, line ) ) {
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
        assert( cin );

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

    cout << highest << endl;
}
