#ifndef DAY24_H
#define DAY24_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>


class Component : public std::pair<unsigned,unsigned> {
    using pair::pair;
};

inline std::ostream& operator<<( std::ostream& os, const Component& c ) {
    return os << c.first << '/' << c.second;
}

template<> struct std::less<Component> {
    bool operator() (const Component& x, const Component& y) const {
        if ( x.first < y.first ) return true;
        if ( x.first> y.first ) return false;
        return ( x.second <= y.second );
    }
    typedef Component first_argument_type;
    typedef Component second_argument_type;
    typedef bool result_type;
};

class ComponentSet : public std::set<Component> {
    public:
    using set::set;

    // Get set of components that have the same strength on either connector.
    void getCompatible( const unsigned strength, ComponentSet& s ) const {
        s.clear();

        std::copy_if ( this->begin(), this->end(),
                       std::inserter( s, s.begin() ),
            [ strength ]( const Component& c ) {
                return strength == c.first || strength == c.second;
            } );
    }
};

inline std::ostream& operator<<( std::ostream& os, const ComponentSet& s ) {
    for ( const auto& c : s ) {
        os << c << "\n";
    }
    return os;
}

#endif // DAY24_H
