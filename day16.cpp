/*
--- Day 16: Permutation Promenade ---

You come upon a very unusual sight; a group of programs here appear to be
dancing.

There are sixteen programs in total, named a through p. They start by
standing in a line: a stands in position 0, b stands in position 1, and so
on until p, which stands in position 15.

The programs' dance consists of a sequence of dance moves:

  - Spin, written sX, makes X programs move from the end to the front, but
    maintain their order otherwise. (For example, s3 on abcde produces
    cdeab).
  - Exchange, written xA/B, makes the programs at positions A and B swap
    places.
  - Partner, written pA/B, makes the programs named A and B swap places.

For example, with only five programs standing in a line (abcde), they could
do the following dance:

  - s1, a spin of size 1: eabcd.
  - x3/4, swapping the last two programs: eabdc.
 - pe/b, swapping programs e and b: baedc.

After finishing their dance, the programs end up in order baedc.

You watch the dance for a while and record their dance moves (your puzzle
input). In what order are the programs standing after their dance?

--- Part Two ---

Now that you're starting to get a feel for the dance moves, you turn your
attention to the dance as a whole.

Keeping the positions they ended up in from their previous dance, the
programs perform it again and again: including the first dance, a total of
one billion (1000000000) times.

In the example above, their second dance would begin with the order baedc,
and use the same dance moves:

  - s1, a spin of size 1: cbaed.
  - x3/4, swapping the last two programs: cbade.
  - pe/b, swapping programs e and b: ceadb.

In what order are the programs standing after their billion dances?
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <list>
#include <iostream>
#include <sstream>
#include <utility>

#include "main.h"

using namespace std;

int mainfunc( istream &is, ostream &os, Part part ) {

    string input;
    getline( is, input );
    assert( is );

    replace( input.begin(), input.end(), ',', ' ' );

    string move;
    deque<char> programs;
    for ( char c = 'a'; c <= 'p'; c++ ) {
        programs.push_back( c );
    }
    const deque<char> programsOrig( programs );

    unsigned numIterations = 1;
    if ( part == Part::PART2 ) numIterations = 1000000000;

    for ( unsigned iteration = 0; iteration < numIterations; iteration++ ) {
        istringstream parser( input );
        while ( parser >> move ) {
            if ( move[0] == 's' ) {
                // Spin
                istringstream s( move.substr(1) );

                unsigned count;
                s >> count;
                assert( s );

                for ( unsigned i = 0; i < count; i++ ) {
                    programs.push_front( programs.back() );
                    programs.pop_back();
                }

            } else if ( move[0] == 'x' ) {
                // Exchange
                istringstream s( move.substr(1) );
                unsigned pos1, pos2;

                s >> pos1;
                assert( pos1 < programs.size() );
                assert( s.peek() == '/' );
                s.ignore( 1 );
                s >> pos2;
                assert( pos2 < programs.size() );
                assert( s );

                swap( programs[pos1], programs[pos2] );

            } else if ( move[0] == 'p' ) {
                // Partner
                assert( move.size() == 4 );
                assert( move[2] == '/' );

                auto pos1 = find( programs.begin(), programs.end(), move[1] );
                assert( pos1 != programs.end() );
                auto pos2 = find( programs.begin(), programs.end(), move[3] );
                assert( pos2 != programs.end() );

                swap( *pos1, *pos2 );
            } else {
                assert( !"Unknown comand" );
            }
        }

        if ( programs == programsOrig ) {
            unsigned numIterationsInCycle = iteration + 1;
            while( iteration < numIterations ) iteration += numIterationsInCycle;
            iteration -= numIterationsInCycle;
        }
    }

    for( auto c: programs ) {
        os << c;
    }
    os << endl;

    return 0;
}
