
/*
--- Part Two ---
Now, you're ready to remove the garbage.

To prove you've removed it, you need to count all of the characters within the garbage. The leading and trailing < and > don't count, nor do any canceled characters or the ! doing the canceling.

<>, 0 characters.
<random characters>, 17 characters.
<<<<>, 3 characters.
<{!>}>, 2 characters.
<!!>, 0 characters.
<!!!>>, 0 characters.
<{o"i!a,<{i<a>, 10 characters.
How many non-canceled characters are within the garbage in your puzzle input?
*/

#include <cassert>
#include <iostream>

using namespace std;

int main() {

    int depth = 0;
    int score = 0;
    int garbageCount = 0;

    bool inGarbage = false;

    char input;
    while( cin.get( input ) ) {
        if ( input == '<' ) {
            if ( inGarbage ) {
                garbageCount++;
            }
            inGarbage = true;
            continue;
        }

        if ( input == '!' ) {
            char ignore;
            cin >> ignore;
            continue;
        }

        if ( input == '>' ) {
            inGarbage = false;
            continue;
        }

        if ( ! inGarbage ) {
            if ( input == '{' ) {
                depth ++;
                score += depth;
            }
            if ( input == '}' ) depth --;
        } else {
            garbageCount++;
        }
    }

    assert( depth == 0 );

    cout << garbageCount << endl;
}
