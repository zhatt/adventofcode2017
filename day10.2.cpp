/*
--- Part Two ---
The logic you've constructed forms a single round of the Knot Hash
algorithm; running the full thing requires many of these rounds. Some input
and output processing is also required.

First, from now on, your input should be taken not as a list of numbers,
but as a string of bytes instead. Unless otherwise specified, convert
characters to bytes using their ASCII codes. This will allow you to handle
arbitrary ASCII strings, and it also ensures that your input lengths are
never larger than 255. For example, if you are given 1,2,3, you should
convert it to the ASCII codes for each character: 49,44,50,44,51.

Once you have determined the sequence of lengths to use, add the following
lengths to the end of the sequence: 17, 31, 73, 47, 23. For example, if you
are given 1,2,3, your final sequence of lengths should be
49,44,50,44,51,17,31,73,47,23 (the ASCII codes from the input string
combined with the standard length suffix values).

Second, instead of merely running one round like you did above, run a total
of 64 rounds, using the same length sequence in each round. The current
position and skip size should be preserved between rounds. For example, if
the previous example was your first round, you would start your second
round with the same length sequence (3, 4, 1, 5, 17, 31, 73, 47, 23, now
assuming they came from ASCII codes and include the suffix), but start with
the previous round's current position (4) and skip size (4).

Once the rounds are complete, you will be left with the numbers from 0 to
255 in some order, called the sparse hash. Your next task is to reduce
these to a list of only 16 numbers called the dense hash. To do this, use
numeric bitwise XOR to combine each consecutive block of 16 numbers in the
sparse hash (there are 16 such blocks in a list of 256 numbers). So, the
first element in the dense hash is the first sixteen elements of the sparse
hash XOR'd together, the second element in the dense hash is the second
sixteen elements of the sparse hash XOR'd together, etc.

For example, if the first sixteen elements of your sparse hash are as shown
below, and the XOR operator is ^, you would calculate the first output
number like this:

65 ^ 27 ^ 9 ^ 1 ^ 4 ^ 3 ^ 40 ^ 50 ^ 91 ^ 7 ^ 6 ^ 0 ^ 2 ^ 5 ^ 68 ^ 22 = 64

Perform this operation on each of the sixteen blocks of sixteen numbers in
your sparse hash to determine the sixteen numbers in your dense hash.

Finally, the standard way to represent a Knot Hash is as a single
hexadecimal string; the final output is the dense hash in hexadecimal
notation. Because each number in your dense hash will be between 0 and 255
(inclusive), always represent each number as two hexadecimal digits
(including a leading zero as necessary). So, if your first three numbers
are 64, 7, 255, they correspond to the hexadecimal numbers 40, 07, ff, and
so the first six characters of the hash would be 4007ff. Because every Knot
Hash is sixteen such numbers, the hexadecimal representation is always 32
hexadecimal digits (0-f) long.

Here are some example hashes:

The empty string becomes a2582a3a0e66e6e86e3812dcb672a272.
AoC 2017 becomes 33efeb34ea91902bb2f59c9920caa6cd.
1,2,3 becomes 3efbe78a8d82f29979031a4aa0b16a9d.
1,2,4 becomes 63960835bcdc130f0b66d7ff4f6a5a8e.

Treating your puzzle input as a string of ASCII characters, what is the
Knot Hash of your puzzle input? Ignore any leading or trailing whitespace
you might encounter.
*/

#include <algorithm>
#include <cassert>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <numeric>
#include <sstream>
#include <vector>

const size_t hashSize = 256;

using namespace std;

static std::string makeHexString( const vector<int>& v ) {
    std::ostringstream hex;
    hex << std::hex << std::setfill('0');

    for ( auto i : v ) {
        hex << std::setw(2) << static_cast<unsigned>( i );
    }

    return hex.str();
};

int main() {

    // Load ascii stream from cin.
    string input;
    getline( cin, input );
    assert( cin );

    vector<uint8_t> data( input.begin(), input.end() );

    // Add standard suffix.
    data.insert( data.end(), { 17, 31, 73, 47, 23 } );

    vector<int> hash( hashSize * 2 );
    auto hashEnd = hash.begin() + hashSize;

    iota( hash.begin(), hash.begin() + hashSize, 0 );
    iota( hash.begin() + hashSize, hash.begin() + 2*hashSize, 0 );


    unsigned skipSize = 0;
    auto current = hash.begin();

    for ( unsigned round = 0; round < 64; round++ ) {
        for ( auto cmd : data ) {
            assert( cmd <= hashSize );

            auto currentEnd = current + cmd;
            reverse( current, currentEnd );

            if ( currentEnd > hashEnd ) {
                copy( hashEnd, currentEnd, hash.begin() );
            }

            copy( hash.begin(), hashEnd, hashEnd );

            current += skipSize++;
            if ( skipSize >= hashSize ) skipSize -= hashSize;
            if ( current >= hashEnd ) current -= hashSize;

            current += cmd;
            if ( current >= hashEnd ) current -= hashSize;

            assert( current - hash.begin() < 256 );
        }
    }

    hash.resize( hashSize ); 
    vector<int> sparseHash( hashSize / 16 );

    auto sparseIter = sparseHash.begin();
    for ( auto hashIter = hash.begin(); hashIter <= hash.end(); hashIter += 16 ) {
          *sparseIter++ = accumulate( hashIter, hashIter + 16, 0, bit_xor<int>() ); 
    }

    string output = makeHexString( sparseHash );
    cout << output << endl;
}

