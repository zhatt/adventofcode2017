/*
--- Day 21: Fractal Art ---
You find a program trying to generate some art. It uses a strange process
that involves repeatedly enhancing the detail of an image through a set of
rules.

The image consists of a two-dimensional square grid of pixels that are
either on (#) or off (.). The program always begins with this pattern:

.#.
..#
###

Because the pattern is both 3 pixels wide and 3 pixels tall, it is said to
have a size of 3.

Then, the program repeats the following process:

  - If the size is evenly divisible by 2, break the pixels up into 2x2
    squares, and convert each 2x2 square into a 3x3 square by following
    the corresponding enhancement rule.
  - Otherwise, the size is evenly divisible by 3; break the pixels up into
    3x3 squares, and convert each 3x3 square into a 4x4 square by
    following the corresponding enhancement rule.

Because each square of pixels is replaced by a larger one, the image gains
pixels and so its size increases.

The artist's book of enhancement rules is nearby (your puzzle input);
however, it seems to be missing rules. The artist explains that sometimes,
one must rotate or flip the input pattern to find a match. (Never rotate or
flip the output pattern, though.) Each pattern is written concisely: rows
are listed as single units, ordered top-down, and separated by slashes. For
example, the following rules correspond to the adjacent patterns:

../.#  =  ..
          .#

                .#.
.#./..#/###  =  ..#
                ###

                        #..#
#..#/..../#..#/.##.  =  ....
                        #..#
                        .##.

When searching for a rule to use, rotate and flip the pattern as necessary.
For example, all of the following patterns match the same rule:

.#.   .#.   #..   ###
..#   #..   #.#   ..#
###   ###   ##.   .#.

Suppose the book contained the following two rules:

../.# => ##./#../...
.#./..#/### => #..#/..../..../#..#

As before, the program begins with this pattern:

.#.
..#
###

The size of the grid (3) is not divisible by 2, but it is divisible by 3.
It divides evenly into a single square; the square matches the second rule
which produces:

#..#
....
....
#..#

The size of this enhanced grid (4) is evenly divisible by 2, so that rule
is used. It divides evenly into four squares:

#.|.#
..|..
--+--
..|..
#.|.#

Each of these squares matches the same rule (../.# => ##./#../...), three
of which require some flipping and rotation to line up with the rule. The
output for the rule is the same in all four cases:

##.|##.
#..|#..
...|...
---+---
##.|##.
#..|#..
...|...

Finally, the squares are joined into a new grid:

##.##.
#..#..
......
##.##.
#..#..
......

Thus, after 2 iterations, the grid contains 12 pixels that are on.

How many pixels stay on after 5 iterations?

--- Part Two ---
How many pixels stay on after 18 iterations?
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <unordered_map>
#include <sstream>
#include <utility>

#include "day21.h"
#include "main.h"

using namespace std;

std::ostream& operator<<( std::ostream& os, const Picture& grid ) {
    grid.print( os );
    return os;
}

class Rules : public unordered_map<Pixels,Pixels> {

    public:
    void insertRule( Pixels oldPixels, Pixels newPixels ) {

        auto iter = find( oldPixels );
        if ( iter == end() ) {
            insert( { oldPixels, newPixels } );
        } else {
            // If the old pixel pattern exists then the new pixels must be the
            // same if the input rules are valid.
            assert( newPixels == iter->second );
        }
    }
};

ostream& operator<<( ostream& os, const Rules& rules ) {
    for ( const auto& rule : rules ) {
        os << rule.first.getString() << " => " << rule.second.getString() 
           << "\n";
    }

    return os;
}

static void addRule( Rules& rules,
                     const Pixels& oldPixels,
                     const Pixels& newPixels ) {
    {
    Pixels tmpPixels { oldPixels };
    rules.insertRule( tmpPixels, newPixels );
    tmpPixels.mirrorHoriz();
    rules.insertRule( tmpPixels, newPixels );
    tmpPixels.mirrorHoriz();

    tmpPixels.rotateCCW();
    rules.insertRule( tmpPixels, newPixels );
    tmpPixels.mirrorHoriz();
    rules.insertRule( tmpPixels, newPixels );
    tmpPixels.mirrorHoriz();

    tmpPixels.rotateCCW();
    rules.insertRule( tmpPixels, newPixels );
    tmpPixels.mirrorHoriz();
    rules.insertRule( tmpPixels, newPixels );
    tmpPixels.mirrorHoriz();

    tmpPixels.rotateCCW();
    rules.insertRule( tmpPixels, newPixels );
    tmpPixels.mirrorHoriz();
    rules.insertRule( tmpPixels, newPixels );
    tmpPixels.mirrorHoriz();
    }
}


static const Pixels initialPixels { ".#./..#/###" };

int simulate( istream& is, ostream& os, Part part, const unsigned iterations ) {

    string line;

    Rules rules;

    while ( getline( is, line ) ) {
        istringstream parser( line );
        string oldPixels, newPixels;
        parser >> oldPixels;
        parser.ignore( 100, '>' );
        parser >> newPixels;
        assert( parser );

        addRule( rules, oldPixels, newPixels );
    }

    Picture grid { { { initialPixels } } };

    for ( unsigned iteration = 0; iteration < iterations; iteration++ ) {
        grid.flatten();
        grid.reduce();

        // Walk grid
        for ( auto& row : grid ) {
           for ( auto& subgrid : row ) {

                auto iterRule = rules.find( subgrid );
                assert( iterRule != rules.end() );

                subgrid = iterRule->second;
            }
        }
    }

    // Walk grid and count pixels.
    size_t count=0;
    size_t numOn = 0;
    for ( auto& row : grid ) {
        for ( auto& subgrid : row ) {
            numOn += subgrid.numMatching( '#' );
            count++;
        }
    }
    os << numOn << endl;

    return 0;
}

int mainfunc( istream& is, ostream& os, Part part ) {
    if ( part == Part::PART1 ) {
        return simulate( is, os, part, 5 );
    } else {
        return simulate( is, os, part, 18 );
    }
}
