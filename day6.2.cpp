/*
  --- Part Two ---

Out of curiosity, the debugger would also like to know the size of the loop: starting from a state that has already been seen, how many block redistribution cycles must be performed before that same state is seen again?

In the example above, 2 4 1 2 is seen again after four cycles, and so the answer in that example would be 4.

How many cycles are in the infinite loop that arises from the configuration in your puzzle input?
*/


#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

static void redistribute( vector<int>::iterator largest, vector<int>& data ) {
    int amount = *largest;
    *largest = 0;

    while( amount > 0 ) {
        if ( ++largest == data.end() ) largest = data.begin(); 
        (*largest)++;
        amount--;
    }
}

int main() {
 
    // Load token stream from cin.
    vector<int> data( (std::istream_iterator<int>(cin)),
                      std::istream_iterator<int>());

    set<string> seen;

    int count = 0;
    while ( true ) {
        ostringstream s;

        auto largest = data.begin(); 
        
        for ( auto iter = data.begin(); iter != data.end(); ++iter ) {
            s << *iter << " ";
            if ( *iter > *largest ) largest = iter;
        }

        if ( seen.find( s.str() ) != seen.end() ) {
            break;
        } else {
            seen.insert( s.str() );
        }

        count++;

        redistribute( largest, data );
    }

    count = 0;
    string original;

    while ( true ) {
        ostringstream s;

        auto largest = data.begin(); 
        
        for ( auto iter = data.begin(); iter != data.end(); ++iter ) {
            s << *iter << " ";
            if ( *iter > *largest ) largest = iter;
        }

        if ( original.size() == 0 ) {
            original = s.str();
        } else if ( s.str() == original ) {
            break;
        }

        count++;

        redistribute( largest, data );
    }

    cout << count << endl;
}
