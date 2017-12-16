/*
 --- Day 3: Spiral Memory ---

You come across an experimental new kind of memory stored on an infinite
two-dimensional grid.

Each square on the grid is allocated in a spiral pattern starting at a
location marked 1 and then counting up while spiraling outward. For
example, the first few squares are allocated like this:

17  16  15  14  13
18   5   4   3  12
19   6   1   2  11
20   7   8   9  10
21  22  23---> ...

While this is very space-efficient (no squares are skipped), requested data
must be carried back to square 1 (the location of the only access port for
this memory system) by programs that can only move up, down, left, or
right. They always take the shortest path: the Manhattan Distance between
the location of the data and square 1.

For example:

  - Data from square 1 is carried 0 steps, since it's at the access port.
  - Data from square 12 is carried 3 steps, such as: down, left, left.
  - Data from square 23 is carried only 2 steps: up twice.
  - Data from square 1024 must be carried 31 steps.

How many steps are required to carry the data from the square identified in
your puzzle input all the way to the access port?

--- Part Two ---
As a stress test on the system, the programs here clear the grid and then
store the value 1 in square 1. Then, in the same allocation order as shown
above, they store the sum of the values in all adjacent squares, including
diagonals.

So, the first few squares' values are chosen as follows:

  - Square 1 starts with the value 1.
  - Square 2 has only one adjacent filled square (with value 1), so it
    also stores 1.
  - Square 3 has both of the above squares as neighbors and stores the sum
    of their values, 2.
  - Square 4 has all three of the aforementioned squares as neighbors and
    stores the sum of their values, 4.
  - Square 5 only has the first and fourth squares as neighbors, so it
    gets the value 5.

Once a square is written, its value does not change. Therefore, the first
few squares would receive the following values:

147  142  133  122   59
304    5    4    2   57
330   10    1    1   54
351   11   23   25   26
362  747  806--->   ...

What is the first value written that is larger than your puzzle input?
*/

#include <cassert>
#include <iostream>
#include <map>
#include <utility>

#include "main.h"

using namespace std;

int mainfunc( istream& is, ostream& os, Part part ) {
    int input;
    is >> input;

    assert( is );

    int xinc = 1, yinc = 0;
    int right = 0, left = 0, top = 0, bottom = 0;

    int x = 0, y = 0;

    map<pair<int,int>,int> array;

    // Initialize the center square.
    array[ {0,0} ] = 1;

    int firstval = input;

    for ( int i = 1; i < input; i++ ) {
        int val = 0;

        // Add up neighbor values.
        for ( int a = -1; a <= 1; a++ ) {
            for ( int b = -1; b <= 1; b++ ) {
  
                // Skip current square.
                if ( a == 0 && b == 0 ) continue;

                // Does the neighbor exist yet?
                auto iter = array.find( make_pair( x+a, y+b ) );

                // Found a neighbor, add it.
                if ( iter != array.end() ) {
                    val += iter->second;
                }
            }
        }

        array.insert( make_pair( make_pair(x,y), val ) );

        if ( val > input && firstval == input ) {
            firstval = val;
        }

        x += xinc;
        y += yinc;

        if ( x > right ) {
            right ++;
            xinc = 0;
            yinc = 1;
        } else if ( y > top ) {
            top ++;
            xinc = -1;
            yinc = 0;
        } else if ( x < left ) {
            left --;
            xinc = 0;
            yinc = -1;
        } else if ( y < bottom ) {
            bottom --;
            xinc = 1;
            yinc = 0;
        }
    }

    if ( part == Part::PART1 ) {
        os << abs( x ) + abs( y ) << endl;
    } else {
        os << firstval << endl;
    }

    return 0;
}
