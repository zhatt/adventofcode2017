/*
--- Day 7: Recursive Circus ---

Wandering further through the circuits of the computer, you come upon a
tower of programs that have gotten themselves into a bit of trouble. A
recursive algorithm has gotten out of hand, and now they're balanced
precariously in a large tower.

One program at the bottom supports the entire tower. It's holding a large
disc, and on the disc are balanced several more sub-towers. At the bottom of
these sub-towers, standing on the bottom disc, are other programs, each
holding their own disc, and so on. At the very tops of these sub-sub-
sub-...-towers, many programs stand simply keeping the disc below them
balanced but with no disc of their own.

You offer to help, but first you need to understand the structure of these
towers. You ask each program to yell out their name, their weight, and (if
they're holding a disc) the names of the programs immediately above them
balancing on that disc. You write this information down (your puzzle
input). Unfortunately, in their panic, they don't do this in an orderly
fashion; by the time you're done, you're not sure which program gave which
information.

For example, if your list is the following:

pbga (66)
xhth (57)
ebii (61)
havc (66)
ktlj (57)
fwft (72) -> ktlj, cntj, xhth
qoyq (66)
padx (45) -> pbga, havc, qoyq
tknk (41) -> ugml, padx, fwft
jptl (61)
ugml (68) -> gyxo, ebii, jptl
gyxo (61)
cntj (57)

...then you would be able to recreate the structure of the towers that
looks like this:

                gyxo
              /     
         ugml - ebii
       /      \
      |         jptl
      |        
      |         pbga
     /        /
tknk --- padx - havc
     \        \
      |         goyq
      |             
      |         ktlj
       \      /     
         fwft - cntj
              \
                xhth

In this example, tknk is at the bottom of the tower (the bottom program),
and is holding up ugml, padx, and fwft. Those programs are, in turn,
holding up other programs; in this example, none of those programs are
holding up any other programs, and are all the tops of their own towers.
(The actual tower balancing in front of you is much larger.)

Before you're ready to help them, you need to make sure your information is
correct. What is the name of the bottom program?

--- Part Two ---

The programs explain the situation: they can't get down. Rather, they could
get down, if they weren't expending all of their energy trying to keep the
tower balanced. Apparently, one program has the wrong weight, and until
it's fixed, they're stuck here.

For any program holding a disc, each program standing on that disc forms a
sub-tower. Each of those sub-towers are supposed to be the same weight, or
the disc itself isn't balanced. The weight of a tower is the sum of the
weights of the programs in that tower.

In the example above, this means that for ugml's disc to be balanced, gyxo,
ebii, and jptl must all have the same weight, and they do: 61.

However, for tknk to be balanced, each of the programs standing on its disc
and all programs above it must each match. This means that the following
sums must all be the same:

  ugml + (gyxo + ebii + jptl) = 68 + (61 + 61 + 61) = 251
  padx + (pbga + havc + qoyq) = 45 + (66 + 66 + 66) = 243
  fwft + (ktlj + cntj + xhth) = 72 + (57 + 57 + 57) = 243

As you can see, tknk's disc is unbalanced: ugml's stack is heavier than the
other two. Even though the nodes above ugml are balanced, ugml itself is
too heavy: it needs to be 8 units lighter for its stack to weigh 243 and
keep the towers balanced. If this change were made, its weight would be 60.

Given that exactly one program is the wrong weight, what would its weight
need to be to balance the entire tower?
*/

#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "main.h"

using namespace std;


class Programs {

    struct ProgramInfo {
        int weight;
        set<string> subprograms;
    };

    map<string,ProgramInfo> programInfo_;

    set<string> roots;

    int calcWeight( const string& program ) {
        auto info = programInfo_[ program ];

        int weight = info.weight;

        for ( auto& program : info.subprograms ) {
            weight += calcWeight( program );
        }

        return weight;
    }

    public:    
    void insert( string program, int weight, set<string> subprograms ) {
        for ( auto s : subprograms ) {
            if ( programInfo_.find( s ) != programInfo_.end() ) {
                roots.erase( s );
            } else {
                programInfo_[ s ] = { 0, {} };
            }
        }

        if ( programInfo_.find( program ) == programInfo_.end() ) {
            roots.insert( program );
        }

        programInfo_[ program ] = { weight, subprograms };
    }

    private:
    void printTree_r( ostream& os, int depth, string prefix, string program ) {
        ProgramInfo info = programInfo_[ program ];

        prefix += ":" + program;

        for ( auto s : info.subprograms ) {
            printTree_r( os, depth, prefix, s );
        }

        os << prefix << endl;
    }

    public:
    string firstRoot() {
        if ( roots.size() ) {
            return *roots.begin();
        } else {
            return "";
        }
    }

    void print( ostream& os, int depth=0 ) {
        assert( roots.size() == 1 );

        printTree_r( os, depth, "", *roots.begin() );
    }

    private:
    void findFirstUnbalanced_r( const string& program, string& unbalanced ) {
        ProgramInfo info = programInfo_[ program ];

        for ( auto s : info.subprograms ) {
            findFirstUnbalanced_r( s, unbalanced );
            if ( unbalanced.size() ) return;
        }

        map<int,int> weights;

        for ( auto& program : info.subprograms ) {
            int weight = calcWeight( program );
            weights[ weight ] ++;
        }

        if ( weights.size() > 1 ) {
            unbalanced = program;
        }
    }

    public:
    string findFirstUnbalanced() {
        assert( roots.size() == 1 );
        string unbalanced;
        findFirstUnbalanced_r( *roots.begin(), unbalanced );
        return unbalanced;
    }

    int calculateBalanceWeight( const string& program ) {
        ProgramInfo info = programInfo_[ program ];

        map<int,int> weights;
        for ( auto& subprog : info.subprograms ) {
            int weight = calcWeight( subprog );
            weights[ weight ] ++;
        }

        assert( weights.size() > 1 );

        int wrongWeight = 0;
        int rightWeight = 0;

        for ( auto w : weights ) {
            if ( w.second == 1 ) {
                wrongWeight = w.first;
            } else {
                rightWeight = w.first;
            }
        }

        for ( auto& subprog : info.subprograms ) {
            int weight = calcWeight( subprog );

            if ( weight == wrongWeight ) {
                int adjustment = wrongWeight - rightWeight;
                return programInfo_[ subprog ].weight - adjustment;
            }
        }

        assert( 0 );
        return 0;
    }
};

int mainfunc( istream& is, ostream& os, Part part ) {

    Programs programs;

    string line;
    while( getline( is, line ) ) {
        set<string> subprograms;

        istringstream parser( line );

        string program;
        parser >> program;
        char discard;
        parser >> discard;
        int weight;
        parser >> weight;
        parser >> discard;
        string arrow;
        parser >> arrow;

        while( parser && ! parser.eof() ) {
            string heldUpProgram;
            parser >> heldUpProgram;
            if ( *(heldUpProgram.end() - 1) == ',' ) {
                heldUpProgram.pop_back();
            }

            subprograms.insert( heldUpProgram );
        }

        programs.insert( program, weight, subprograms );
    }

    string root = programs.firstRoot();
    if ( part == Part::PART1 ) {
        os << root << endl;
    } else {
        //programs.print( cerr );
        string unbalanced = programs.findFirstUnbalanced();
        os << programs.calculateBalanceWeight( unbalanced ) << endl;
    }

    return 0;
}
