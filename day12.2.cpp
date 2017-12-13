/*
--- Part Two ---
There are more programs than just the ones in the group containing program ID 0. The rest of them have no way of reaching that group, and still might have no way of reaching each other.

A group is a collection of programs that can all communicate via pipes either directly or indirectly. The programs you identified just a moment ago are all part of the same group. Now, they would like you to determine the total number of groups.

In the example above, there were 2 groups: one consisting of programs 0,2,3,4,5,6, and the other consisting solely of program 1.

How many groups are there in total?
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>

#include "graph.h"

using namespace std;

int main()
{
    Graph<int> g;

    set<int> programs;

    string line;
    while( getline( cin, line ) ) {
        replace( line.begin(), line.end(), ',', ' ');
        istringstream parser( line );

        int from;
        parser >> from;

        string arrow;
        parser >> arrow;

        while( parser ) {
            int to;
            parser >> to;

            g.addEdge( from, to );
            g.addEdge( to, from );

            programs.insert( from );
            programs.insert( to );
        }
    }

    set<int> notfound = programs;

    int groups=0;
    while( notfound.size() ) {
        groups++;

        int x = *notfound.begin();
        notfound.erase( notfound.begin() );

        int groupsize = 1;

        for( auto iter = notfound.begin(); iter != notfound.end();
             /* intr increment below */ ) {
            if ( g.isReachable( x, *iter ) ) {
                notfound.erase( iter++ );
                groupsize++;
            } else {
                iter++;
            }
        }
    }

    cout << groups << endl;
}
