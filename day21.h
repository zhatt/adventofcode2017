#ifndef DAY21_H
#define DAY21_H

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <sstream>

#include "main.h"

int simulate( std::istream& is, std::ostream& os, Part part,
              unsigned numIterations );

class Pixels {

    protected:
    std::string pixelString_;
    size_t size_;

    // x goes left to right
    // y goes top to bottom
    size_t coordToIndex( size_t x, size_t y ) const {
        size_t index = y * (size_+1) + x;
        return index;
    }

    public:

    Pixels() :size_( 0 ) {}

    Pixels( const std::string& p ) :
        pixelString_( p ) {

        if ( pixelString_.size() == 0 ) {
            throw std::invalid_argument( "null string" );
        }

        size_t numSlash = std::count( pixelString_.begin(), pixelString_.end(),
                                      '/');

        size_ = numSlash + 1;

        if ( pixelString_.size() != size_* size_ + size_ - 1 ) {
            throw std::invalid_argument( "wrong string length" );
        }

        for( size_t i = 0; i < pixelString_.size(); i ++ ) {
            if ( ((i+1) % (size_+1)) == 0 ) {
                if ( pixelString_[i] != '/' ) {
                    throw std::invalid_argument( "expecting /" );
                }

            } else {
                if ( pixelString_[i] == '/' ) {
                    throw std::invalid_argument( "not expecting /" );
                }
            }
        }
    }

    bool operator==( const Pixels& other ) const {
        return pixelString_ == other.pixelString_;
    }

    std::string getString() const {
        return pixelString_;
    }

    std::string getRowString( size_t row ) const {
        assert( row < size_ );

        return pixelString_.substr( row * (size_+1), size_ );
    }

    size_t size() const {
        return size_;
    }

    void mirrorHoriz() {
        for ( size_t x = 0; x < size_; ++x ) {
            for ( size_t y = 0; y < size_/2; ++y ) {
                std::swap( pixelString_[ coordToIndex( x, y ) ],
                           pixelString_[ coordToIndex( x, size_-y-1 ) ] );
            }
        }
    }

    void mirrorVert() {
        for ( size_t x = 0; x < size_/2; ++x ) {
            for ( size_t y = 0; y < size_; ++y ) {
                std::swap( pixelString_[ coordToIndex( x, y ) ],
                           pixelString_[ coordToIndex( size_-x-1, y ) ] );
            }
        }
    }

    void rotateCCW() {
        // Copy original to get / and size.
        std::string newPixels( pixelString_ );

        for ( size_t x = 0; x < size_; ++x ) {
            for ( size_t y = 0; y < size_; ++y ) {
                newPixels[ coordToIndex( x, y ) ] =
                    pixelString_[ coordToIndex( size_-y-1, x ) ];
            }
        }
        pixelString_ = newPixels;
    }

    Pixels getSubPixels( size_t colIndex, size_t rowIndex, unsigned size ) {

        std::string s;
        s.reserve( size*size + size-1 );

        for ( unsigned y = 0; y < size; y++ ) {
            for ( unsigned x = 0; x < size; x++ ) {
                s += pixelString_[ coordToIndex( colIndex+x, rowIndex+y ) ];
            }
            if ( y + 1 != size ) {
                s += "/";
            }
        }

        return Pixels( s );
    }

    size_t numMatching( char c ) const {
        return count( pixelString_.begin(), pixelString_.end(), c );
    }

};

template<> struct std::hash<Pixels> {
    typedef Pixels argument_type;
    typedef size_t result_type;
    result_type operator()(argument_type const& s) const noexcept {
        result_type const h1 ( hash<string>()(s.getString() ) );
        return h1;
    }
};

class Picture : public std::list<std::list<Pixels>> {
    public:

    Picture( const Pixels& initial ) {
        this->push_back( std::list<Pixels>() );
        auto row1 = this->begin();
        row1->push_back( initial );
    }

    void flatten() {
        std::stringstream tmp;

        // Walk grid
        for ( auto& row : *this ) {
            size_t subrowSize = 1; // Gets set below once subgrid is available.
            for ( size_t subrowIndex = 0; subrowIndex < subrowSize;
                  subrowIndex++ ) {

                for ( auto& subgrid : row ) {
                    subrowSize = subgrid.size();
                    tmp << subgrid.getRowString( subrowIndex );
                }
                tmp << "/";
            }
        }

        this->resize( 1 );
        this->front().clear();
        if ( tmp.str().size() ) {
            // Strip last /
            this->front().emplace_front(
                tmp.str().substr( 0, tmp.str().size() - 1 ) );
        }
    }

    void reduce() {
        assert( this->size() == 1 );
        assert( this->begin()->size() == 1 );

        Pixels old = front().front();

        size_t size = front().front().size();
        size_t step;

        if ( size % 2 == 0 ) {
            step = 2;
        } else if ( size % 3 == 0 ) {
            step = 3;
        } else {
            assert( !"Bad size" );
        }

        this->clear();

        // Walk grid
        for ( size_t rowIndex = 0; rowIndex < old.size();
              rowIndex += step ) {

            this->emplace_back();

            for ( size_t colIndex = 0; colIndex < old.size();
                  colIndex += step ) {

                Pixels subPixels( old.getSubPixels( colIndex, rowIndex, step ) );

                this->back().push_back( subPixels );
            }
        }
    }

    void print( std::ostream& os, std::string delim = "" ) const {

        // Walk grid
        for ( auto& row : *this ) {
            size_t subrowSize = 1;  // Gets set below once subgrid is available.
            for ( size_t subrowIndex = 0; subrowIndex < subrowSize;
                    subrowIndex++ ) {

                for ( auto& subgrid : row ) {
                    subrowSize = subgrid.size();
                    os << delim;
                    os << subgrid.getRowString( subrowIndex );
                }
                os << delim;
                os << "\n";
            }
        }
    }
};

std::ostream& operator<<( std::ostream& os, const Picture& grid );

#endif // DAY21_H
