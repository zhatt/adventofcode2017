/*
--- Day 19: A Series of Tubes ---

Somehow, a network packet got lost and ended up here. It's trying to follow
a routing diagram (your puzzle input), but it's confused about where to go.

Its starting point is just off the top of the diagram. Lines (drawn with |,
-, and +) show the path it needs to take, starting by going down onto the
only line connected to the top of the diagram. It needs to follow this path
until it reaches the end (located somewhere within the diagram) and stop
there.

Sometimes, the lines cross over each other; in these cases, it needs to
continue going the same direction, and only turn left or right when there's
no other option. In addition, someone has left letters on the line; these
also don't change its direction, but it can use them to keep track of where
it's been. For example:

     |          
     |  +--+    
     A  |  C    
 F---|----E|--+ 
     |  |  |  D 
     +B-+  +--+ 

Given this diagram, the packet needs to take the following path:

  - Starting at the only line touching the top of the diagram, it must go
    down, pass through A, and continue onward to the first +.
  - Travel right, up, and right, passing through B in the process.
  - Continue down (collecting C), right, and up (collecting D).
  - Finally, go all the way left through E and stopping at F.

Following the path to the end, the letters it sees on its path are ABCDEF.

The little packet looks up at you, hoping you can help it find the way.
What letters will it see (in the order it would see them) if it follows the
path? (The routing diagram is very wide; make sure you view it without line
wrapping.)

--- Part Two ---

The packet is curious how many steps it needs to go.

For example, using the same routing diagram from the example above...

     |          
     |  +--+    
     A  |  C    
 F---|--|-E---+ 
     |  |  |  D 
     +B-+  +--+ 

...the packet would go:

  - 6 steps down (including the first line at the top of the diagram).
  - 3 steps right.
  - 4 steps up.
  - 3 steps right.
  - 4 steps down.
  - 3 steps right.
  - 2 steps up.
  - 13 steps left (including the F it stops on).

This would result in a total of 38 steps.

How many steps does the packet need to go?
*/

#include <cassert>
#include <cctype>
#include <complex>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "main.h"

using namespace std;

template<> struct std::hash<complex<int> > {
    typedef complex<int> argument_type;
    typedef size_t result_type;
    result_type operator()(argument_type const& s) const noexcept {
        result_type const h1 ( hash<int>()(s.real()) );
        result_type const h2 ( hash<int>{}(s.imag()) );
        return h1 ^ (h2 << 1);
    }
};

const unordered_set<complex<int>> nextIncrement {
    {  1,  0 }, 
    {  0,  1 },
    { -1,  0 },
    {  0, -1 }
};

int mainfunc( istream& is, ostream& os, Part part ) {

    // Store sparse diagram as map of complex.  real is x.  imag will be neg y
    // so that y increases as you go down.
    unordered_map<complex<int>,char> diagram;

    // Read all input into the map.
    string input;
    int y = 0;
    while ( getline( is, input ) ) {
        int currenty = y++;
        int x = 0;
        for ( char c : input ) {
            int currentx = x++;
            if ( ! isspace( c ) ) {
                diagram[ { currentx, currenty } ] = c;
            }
        }
    }

    complex<int> location { 0, 0 };
    complex<int> increment { 1, 0 };

    // Find beginning.  It will be first coordinate that exists in the first
    // row.  If the input is not well formed, this may loop forever.
    while ( diagram.find( location ) == diagram.end() ) {
        location += increment;
    }

    assert( diagram[ location ] == '|' );

    string valuesSeen;
    unsigned steps = 1;

    increment = { 0, 1 };

    // Go until we find a blank location.
    while ( diagram[ location ] != 0 ) {
        location += increment;
        steps++;

        if ( isalpha( diagram[ location ] ) ) {
            valuesSeen.push_back( diagram[ location ] );

        } else if ( diagram[ location ] == '+' ) {

            for ( const auto& nextInc : nextIncrement ) {
                // -increment is the path we arrived on and so we don't want to
                // go back.
                if ( nextInc == -increment ) continue;

                if ( diagram.find( location + nextInc ) != diagram.end() ) {
                    increment = nextInc;
                    break;
                }
            }
        }
    }
    steps--;

    if ( part == Part::PART1 ) {
        os << valuesSeen << endl;
    } else {
        os << steps << endl;
    }

    return 0;
}

