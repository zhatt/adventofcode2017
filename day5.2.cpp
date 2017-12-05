/*
--- Part Two ---

Now, the jumps are even stranger: after each jump, if the offset was three or more, instead decrease it by 1. Otherwise, increase it by 1 as before.

Using this rule with the above example, the process now takes 10 steps, and the offset values after finding the exit are left as 2 3 2 3 -1.

How many steps does it now take to reach the exit?

*/

#include <iostream>
#include <vector>

int main() {
    std::vector<int> data;

    while ( std::cin ) {
        int x;
        std::cin >> x;
        if ( std::cin ) data.push_back( x );
    }

    int current = 0;
    int jumps = 0;

    while ( current < (int) data.size() ) {
        int oldcurrent = current;
        current += data[current];

        if ( data[oldcurrent] >= 3 ) {
            data[oldcurrent]--;
        } else {
            data[oldcurrent]++;
        }

        jumps++;
    }

    std::cout << jumps << std::endl;
}
