/*
--- Part Two ---
How many steps away is the furthest he ever got from his starting position?
*/

#include <algorithm>
#include <cassert>
#include <complex>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    string input;

    cin >> input;
    replace( input.begin(), input.end(), ',', ' ');

    istringstream parser( input );

    int x = 0;
    int y = 0;

    int furthest = 0;

    while ( parser) {
        string command;

        parser >> command;
        if ( !parser ) break;

        if ( command == "n" ) {
            x += 2;
        } else if ( command == "ne" ) {
            x += 1;
            y += 1;
        } else if ( command == "se" ) {
            x += 1;
            y -= 1;
        } else if ( command == "s" ) {
            y -= 2;
        } else if ( command == "sw" ) {
            x -= 1;
            y -= 1;
        } else if ( command == "nw" ) {
            x += 1;
            y -= 1;
        } else {
            assert( !"Unknown direction" );
        }

        int currentDistance = abs( x + y ) / 2;
        furthest = max( furthest, currentDistance );
    }

    cout << furthest << endl;
}
