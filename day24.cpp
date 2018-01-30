/*
--- Day 24: Electromagnetic Moat ---

The CPU itself is a large, black building surrounded by a bottomless pit.
Enormous metal tubes extend outward from the side of the building at
regular intervals and descend down into the void. There's no way to cross,
but you need to get inside.

No way, of course, other than building a bridge out of the magnetic
components strewn about nearby.

Each component has two ports, one on each end. The ports come in all
different types, and only matching types can be connected. You take an
inventory of the components by their port types (your puzzle input). Each
port is identified by the number of pins it uses; more pins mean a stronger
connection for your bridge. A 3/7 component, for example, has a type-3 port
on one side, and a type-7 port on the other.

Your side of the pit is metallic; a perfect surface to connect a magnetic,
zero-pin port. Because of this, the first port you use must be of type 0.
It doesn't matter what type of port you end with; your goal is just to make
the bridge as strong as possible.

The strength of a bridge is the sum of the port types in each component.
For example, if your bridge is made of components 0/3, 3/7, and 7/4, your
bridge has a strength of 0+3 + 3+7 + 7+4 = 24.

For example, suppose you had the following components:

0/2
2/2
2/3
3/4
3/5
0/1
10/1
9/10

With them, you could make the following valid bridges:

  - 0/1
  - 0/1--10/1
  - 0/1--10/1--9/10
  - 0/2
  - 0/2--2/3
  - 0/2--2/3--3/4
  - 0/2--2/3--3/5
  - 0/2--2/2
  - 0/2--2/2--2/3
  - 0/2--2/2--2/3--3/4
  - 0/2--2/2--2/3--3/5

(Note how, as shown by 10/1, order of ports within a component doesn't
matter. However, you may only use each port on a component once.)

Of these bridges, the strongest one is 0/1--10/1--9/10; it has a strength
of 0+1 + 1+10 + 10+9 = 31.

What is the strength of the strongest bridge you can make with the
components you have available?

--- Part Two ---

The bridge you've built isn't long enough; you can't jump the rest of the
way.

In the example above, there are two longest bridges:

0/2--2/2--2/3--3/4
0/2--2/2--2/3--3/5

Of them, the one which uses the 3/5 component is stronger; its strength is
0+2 + 2+2 + 2+3 + 3+5 = 19.

What is the strength of the longest bridge you can make? If you can make
multiple bridges of the longest length, pick the strongest one.
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <utility>

#include "day24.h"
#include "main.h"

using namespace std;

void connectNext( const ComponentSet& allComponents,
                  ComponentSet& current,
                  unsigned currentStrength,
                  unsigned& maxTotalStrength,
                  unsigned& longestLength,
                  unsigned& longestMaxStrength) {

    ComponentSet allCompatible;
    ComponentSet compatible;

    allComponents.getCompatible( currentStrength, allCompatible );

    // Get the compatible components that aren't in current because we can't
    // reuse a component.
    set_difference( allCompatible.begin(), allCompatible.end(),
                    current.begin(), current.end(),
                    inserter( compatible, compatible.end() ) );

    if ( compatible.size() != 0 ) {
        for ( auto c : compatible ) {
            auto iter = current.insert( c );

            connectNext( allComponents, current,
                         c.first == currentStrength ? c.second : c.first,
                         maxTotalStrength, longestLength, longestMaxStrength );

            current.erase( iter.first );
        }
    } else {
        unsigned strength = 0;

        for ( auto c : current ) {
            strength += c.first + c.second;
        }

        maxTotalStrength = max( strength, maxTotalStrength );

        if ( longestLength < current.size() ) {
            longestLength = current.size();
            longestMaxStrength = strength;

        } else if ( longestLength == current.size() ) {
            longestMaxStrength = max( strength, longestMaxStrength );
        }
    }
}

int mainfunc( istream& is, ostream& os, Part part ) {

    ComponentSet allComponents;

    string line;

    while( getline( is, line ) ) {
        istringstream parser( line );

        unsigned a, b;
        parser >> a;
        parser.ignore( 1 );
        parser >> b;
        assert( parser );

        Component c( a, b );
        auto r = allComponents.insert( Component( a, b ) );

        // There are no duplicates in the sample input so everything must
        // insert witout error.
        assert( r.second == true );
    }

    unsigned maxTotalStrength = 0;
    unsigned longestLength = 0;
    unsigned longestMaxStrength = 0;

    ComponentSet s;
    s.insert( { 0, 0 } );
    connectNext( allComponents, s, 0, maxTotalStrength,
                 longestLength, longestMaxStrength );

    if ( part == Part::PART1 ) {
        os << maxTotalStrength << endl;
    } else {
        os << longestMaxStrength << endl;
    }

    return 0;
}

