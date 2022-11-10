/*
 * Knot hash function.  See Day 10.
*/

#ifndef KNOTHASH_H
#define KNOTHASH_H

#include <algorithm>
#include <boost/range/join.hpp>
#include <numeric>
#include <vector>

std::vector<uint8_t> knotHash( const std::vector<uint8_t>& data,
    unsigned numRounds = 64, bool useSuffix = true, bool reduce = true ) {

    const size_t hashSize = 256;


    std::vector<uint8_t> hash( hashSize * 2 );
    auto hashEnd = hash.begin() + hashSize;

    std::iota( hash.begin(), hash.begin() + hashSize, 0 );
    std::iota( hash.begin() + hashSize, hash.begin() + 2*hashSize, 0 );

    unsigned skipSize = 0;
    auto current = hash.begin();

    std::vector<uint8_t> suffix{ 17, 31, 73, 47, 23 };
    std::vector<uint8_t> nosuffix;

    for ( unsigned round = 0; round < numRounds; round++ ) {
        for ( auto cmd : boost::join( data, useSuffix ? suffix : nosuffix ) ) {

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

    if ( reduce ) {
        std::vector<uint8_t> sparseHash( hashSize / 16 );

        auto sparseIter = sparseHash.begin();
        for ( auto hashIter = hash.begin(); hashIter < hash.end();
              hashIter += 16 ) {

            *sparseIter++ = accumulate( hashIter, hashIter + 16, 0,
                                        std::bit_xor<uint8_t>() );
        }
        return sparseHash;
    } else {
        return hash;
    }
}

#endif // KNOTHASH_H
