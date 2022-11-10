/*
--- Day 23: Coprocessor Conflagration ---

You decide to head directly to the CPU and fix the printer from there. As
you get close, you find an experimental coprocessor doing so much work that
the local programs are afraid it will halt and catch fire. This would cause
serious issues for the rest of the computer, so you head in and see what
you can do.

The code it's running seems to be a variant of the kind you saw recently on
that tablet. The general functionality seems very similar, but some of the
instructions are different:

  - set X Y sets register X to the value of Y.
  - sub X Y decreases register X by the value of Y.
  - mul X Y sets register X to the result of multiplying the value
    contained in register X by the value of Y.
  - jnz X Y jumps with an offset of the value of Y, but only if the value
    of X is not zero. (An offset of 2 skips the next instruction, an
    offset of -1 jumps to the previous instruction, and so on.)

Only the instructions listed above are used. The eight registers here,
named a through h, all start at 0.

The coprocessor is currently set to some kind of debug mode, which allows
for testing, but prevents it from doing any meaningful work.

If you run the program (your puzzle input), how many times is the mul
instruction invoked?

--- Part Two ---
Now, it's time to fix the problem.

The debug mode switch is wired directly to register a. You flip the switch,
which makes register a now start at 1 when the program is executed.

Immediately, the coprocessor begins to overheat. Whoever wrote this program
obviously didn't choose a very efficient implementation. You'll need to
optimize the program if it has any hope of completing before Santa needs
that printer working.

The coprocessor's ultimate goal is to determine the final value left in
register h once the program completes. Technically, if it had that... it
wouldn't even need to run the program.

After setting register a to 1, if the program were to run to completion,
what value would be left in register h?
*/

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "machine.h"
#include "main.h"

using namespace std;

bool isPrime( int number ) {
    int i = 2;

    while ( i * i <= number ) {
        if ( number % i == 0 ) {
            return false;
        }
        i += 1;
    }

    return true;
}

int mainfunc( istream& is, ostream& os, Part part ) {

    if ( part == Part::PART1 ) {
        const Program program( is, os );

        list<int64_t> q;
        Machine machine(
            part == Part::PART1 ? registersDebugOn : registersDebugOff,
            q, q, program );

        while( ! machine.pastEnd() ) {
            machine.execute();
#if DEBUGGING
            cerr << "---------------------------------------------------\n";
            cerr << machine.pc() << " " << Mul::getCount() << " " << machine.getReg( "h" ) << endl;
            machine.dump( cerr );
#endif
        }

        os << Mul::getCount() << endl;

    } else {
        // Re-implement algorithm in C.
        // Input is first assignment in assembly code.
        int input = 67;

        int b = input * 100 - -100000;
        int c = b - -17000;

        int regH = 0;

        for ( ; b <= c; b += 17 ) {
            if ( ! isPrime(b) ) {
                regH += 1;
            }
        }

        os << regH << endl;
    }

    return 0;
}
