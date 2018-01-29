/*
--- Day 22: Sporifica Virus ---

Diagnostics indicate that the local grid computing cluster has been
contaminated with the Sporifica Virus. The grid computing cluster is a
seemingly-infinite two-dimensional grid of compute nodes. Each node is
either clean or infected by the virus.

To prevent overloading the nodes (which would render them useless to the
virus) or detection by system administrators, exactly one virus carrier
moves through the network, infecting or cleaning nodes as it moves. The
virus carrier is always located on a single node in the network (the
current node) and keeps track of the direction it is facing.

To avoid detection, the virus carrier works in bursts; in each burst, it
wakes up, does some work, and goes back to sleep. The following steps are
all executed in order one time each burst:

  - If the current node is infected, it turns to its right. Otherwise, it
    turns to its left. (Turning is done in-place; the current node does
    not change.)
  - If the current node is clean, it becomes infected. Otherwise, it
    becomes cleaned. (This is done after the node is considered for the
    purposes of changing direction.)
  - The virus carrier moves forward one node in the direction it is
    facing.

Diagnostics have also provided a map of the node infection status (your
puzzle input). Clean nodes are shown as .; infected nodes are shown as #.
This map only shows the center of the grid; there are many more nodes
beyond those shown, but none of them are currently infected.

The virus carrier begins in the middle of the map facing up.

For example, suppose you are given a map like this:

..#
#..
...

Then, the middle of the infinite grid looks like this, with the virus
carrier's position marked with [ ]:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . . #[.]. . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .

The virus carrier is on a clean node, so it turns left, infects the node,
and moves left:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . .[#]# . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .

The virus carrier is on an infected node, so it turns right, cleans the
node, and moves up:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . .[.]. # . . .
. . . . # . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .

Four times in a row, the virus carrier finds a clean, infects it, turns
left, and moves forward, ending in the same place and still facing up:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . #[#]. # . . .
. . # # # . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .

Now on the same node as before, it sees an infection, which causes it to
turn right, clean the node, and move forward:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . # .[.]# . . .
. . # # # . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .

After the above actions, a total of 7 bursts of activity had taken place.
Of them, 5 bursts of activity caused an infection.

After a total of 70, the grid looks like this, with the virus carrier
facing up:

. . . . . # # . .
. . . . # . . # .
. . . # . . . . #
. . # . #[.]. . #
. . # . # . . # .
. . . . . # # . .
. . . . . . . . .
. . . . . . . . .

By this time, 41 bursts of activity caused an infection (though most of
those nodes have since been cleaned).

After a total of 10000 bursts of activity, 5587 bursts will have caused an
infection.

Given your actual map, after 10000 bursts of activity, how many bursts
cause a node to become infected? (Do not count nodes that begin infected.)

--- Part Two ---

As you go to remove the virus from the infected nodes, it evolves to resist
your attempt.

Now, before it infects a clean node, it will weaken it to disable your
defenses. If it encounters an infected node, it will instead flag the node
to be cleaned in the future. So:

  - Clean nodes become weakened.
  - Weakened nodes become infected.
  - Infected nodes become flagged.
  - Flagged nodes become clean.

Every node is always in exactly one of the above states.

The virus carrier still functions in a similar way, but now uses the
following logic during its bursts of action:

  - Decide which way to turn based on the current node:
      - If it is clean, it turns left.
      - If it is weakened, it does not turn, and will continue moving in
        the same direction.
      - If it is infected, it turns right.
      - If it is flagged, it reverses direction, and will go back the way
        it came.
  - Modify the state of the current node, as described above.
  - The virus carrier moves forward one node in the direction it is
    facing.

Start with the same map (still using . for clean and # for infected) and
still with the virus carrier starting in the middle and facing up.

Using the same initial state as the previous example, and drawing weakened
as W and flagged as F, the middle of the infinite grid looks like this,
with the virus carrier's position again marked with [ ]:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . . #[.]. . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .

This is the same as before, since no initial nodes are weakened or flagged.
The virus carrier is on a clean node, so it still turns left, instead
weakens the node, and moves left:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . .[#]W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .

The virus carrier is on an infected node, so it still turns right, instead
flags the node, and moves up:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . .[.]. # . . .
. . . F W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .

This process repeats three more times, ending on the previously-flagged
node and facing right:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . W W . # . . .
. . W[F]W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .

Finding a flagged node, it reverses direction and cleans the node:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . W W . # . . .
. .[W]. W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
The weakened node becomes infected, and it continues in the same direction:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . W W . # . . .
.[.]# . W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .

Of the first 100 bursts, 26 will result in infection. Unfortunately,
another feature of this evolved virus is speed; of the first 10000000
bursts, 2511944 will result in infection.

Given your actual map, after 10000000 bursts of activity, how many bursts
cause a node to become infected? (Do not count nodes that begin infected.)
*/

#include <algorithm>
#include <cassert>
#include <complex>
#include <functional>
#include <unordered_map>

#include "main.h"

using namespace std;

template<> struct std::hash<complex<int> > {
    typedef complex<int> argument_type;
    typedef size_t result_type;
    result_type operator()(argument_type const& s) const noexcept {
        result_type const h1 ( hash<int>()(s.real()) );
        result_type const h2 ( hash<int>{}(s.imag()) );
        return h1 ^ (h2 << 1);
    }
};

class Cluster {
    public:
    enum class VirusType {
        REGULAR,
        EVOLVED
    };

    enum class NodeState {
        WEAKENED,
        INFECTED,
        FLAGGED
        // CLEAN nodes aren't tracked.
    };

    Cluster( istream& is, VirusType type ) : virusType_( type ) {
        // Read all input into the map.
        string input;
        int y = 0;
        while ( getline( is, input ) ) {
            int x = 0;
            for ( char c : input ) {
                if ( c == '#' ) {
                    infectedNodes_.insert( { complex<int>{ x, y },
                                           Cluster::NodeState::INFECTED } );
                } else {
                    assert( c == '.' );
                }

                minX_ = min( minX_, x );
                minY_ = min( minY_, y );
                maxX_ = max( maxX_, x );
                maxY_ = max( maxY_, y );

                x++;
            }
            y++;
        }

        int sizeX = maxX_ - minX_ + 1;
        int sizeY = maxY_ - minY_ + 1;

        // Size must be odd to calculate center.
        assert( sizeX % 2 == 1 );
        assert( sizeY % 2 == 1 );

        currentLocation_ = complex<int>{ minX_ + sizeX/2, minY_ + sizeY/2 };
        currentIncrement_ = complex<int>{ 0, -1 }; // facing up.
    }

    void burst() {
        // Direction change multipliers.
        static const complex<int> turnRight { 0, 1 };
        static const complex<int> turnLeft { 0, -1 };
        static const complex<int> turnAround { -1, 0 };

        auto iter = infectedNodes_.find( currentLocation_ );

        if ( virusType_ == VirusType::REGULAR ) {
            if ( iter != infectedNodes_.end() ) {
                // Is already infected
                currentIncrement_ *= turnRight;
                infectedNodes_.erase( iter );
            } else {
                // Is not infected
                currentIncrement_ *= turnLeft;
                infectedNodes_.insert( { currentLocation_,
                                         NodeState::INFECTED } );
                numInfected_ ++;
            }
        } else {
            if ( iter == infectedNodes_.end() ) {
                // CLEAN
                currentIncrement_ *= turnLeft;
                infectedNodes_.insert( { currentLocation_,
                                         NodeState::WEAKENED } );

            } else {
                switch ( iter->second ) {

                case NodeState::WEAKENED:
                    // No direction change.
                    iter->second = NodeState::INFECTED;
                    numInfected_ ++;
                    break;

                case NodeState::INFECTED:
                    currentIncrement_ *= turnRight;
                    iter->second = NodeState::FLAGGED;
                    break;

                case NodeState::FLAGGED:
                    currentIncrement_ *= turnAround;
                    infectedNodes_.erase( iter );
                    break;
                }
            }
        }

        currentLocation_ += currentIncrement_;
    }

    unsigned getNumInfected() const {
        return numInfected_;
    }

    private:
    // Store sparse node array as map of complex.  real is x.  imag will be neg
    // y so that y increases as you go down.  Clean nodes are not stored.
    unordered_map<complex<int>,NodeState> infectedNodes_;
    complex<int> currentLocation_;
    complex<int> currentIncrement_;

    int minX_ = 0;
    int maxX_ = 0;
    int minY_ = 0;
    int maxY_ = 0;
    unsigned numInfected_ = 0;

    const VirusType virusType_;

};

int mainfunc( istream& is, ostream& os, Part part ) {

    Cluster::VirusType virusType;
    unsigned numberOfBursts;

    if ( part == Part::PART1 ) {
        virusType = Cluster::VirusType::REGULAR;
        numberOfBursts = 10000;
    } else {
        virusType = Cluster::VirusType::EVOLVED;
        numberOfBursts = 10000000;
    }

    Cluster cluster( is, virusType );

    for ( unsigned burst = 0; burst < numberOfBursts; burst++ ) {
        cluster.burst();
    }

    os << cluster.getNumInfected() << endl;

    return 0;
}

