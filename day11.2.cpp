/*
--- Part Two ---
How many steps away is the furthest he ever got from his starting position?
*/

#include <algorithm>
#include <cassert>
#include <complex>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

static const map<string,complex<int> > offsets {
    {"n",  {  0,  2 } },
    {"ne", {  1,  1 } },
    {"se", {  1, -1 } },
    {"s",  {  0, -2 } },
    {"sw", { -1, -1 } },
    {"nw", { -1,  1 } },
};

int main() {
    string input;

    cin >> input;
    replace( input.begin(), input.end(), ',', ' ');

    istringstream parser( input );

    complex<int> location { 0, 0 };
    int furthest = 0;

    while ( parser) {
        string command;

        parser >> command;
        if ( !parser ) break;

        const auto offset = offsets.find( command );
        assert( offset != offsets.end() );

        location += offset->second;

        int currentDistance = abs( location.real() + location.imag() ) / 2;
        furthest = max( furthest, currentDistance );
    }

    cout << furthest << endl;
}
