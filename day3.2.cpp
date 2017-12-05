
/*
--- Part Two ---

As a stress test on the system, the programs here clear the grid and then store the value 1 in square 1. Then, in the same allocation order as shown above, they store the sum of the values in all adjacent squares, including diagonals.

So, the first few squares' values are chosen as follows:

Square 1 starts with the value 1.
Square 2 has only one adjacent filled square (with value 1), so it also stores 1.
Square 3 has both of the above squares as neighbors and stores the sum of their values, 2.
Square 4 has all three of the aforementioned squares as neighbors and stores the sum of their values, 4.
Square 5 only has the first and fourth squares as neighbors, so it gets the value 5.
Once a square is written, its value does not change. Therefore, the first few squares would receive the following values:

147  142  133  122   59
304    5    4    2   57
330   10    1    1   54
351   11   23   25   26
362  747  806--->   ...
What is the first value written that is larger than your puzzle input?

Your puzzle input is still 347991.
*/

#include <cassert>
#include <iostream>
#include <map>
#include <utility>

int main() {
    int input;
    std::cin >> input;

    assert( std::cin );

    int xinc = 1, yinc = 0;
    int right = 0, left = 0, top = 0, bottom = 0;

    int x = 0, y = 0;

    std::map<std::pair<int,int>,int> array;

    int i;
    int val = 0;
    for ( i = 1; val < input; i++ ) {
        val = 0;
        // Store value.
        for ( int a = -1; a <= 1; a++ ) {
            for ( int b = -1; b <= 1; b++ ) {
                if ( a == 0 && b == 0 ) continue;

                std::map<std::pair<int,int>,int>::const_iterator iter =
                    array.find( std::make_pair( x+a, y+b ) );

                if ( iter != array.end() ) {
                    val += iter->second;
                }
            }
        }

        if ( val == 0 ) val = 1;

        array.insert( std::make_pair(std::make_pair(x,y), val ) );

        std::cerr << "i:" << i
                  << "(" << x << "," << y << ")"
                  << " " << abs( x ) + abs( y )
                  << " " << val
                  << std::endl;

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

    std::cout << val << std::endl;

}
