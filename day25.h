#ifndef DAY25_H
#define DAY25_H

#include <iosfwd>
#include <map>
#include <utility>

struct Rule {
    unsigned writeValue;
    enum class Direction { LEFT = -1, RIGHT = 1 } direction;
    char nextState;
};

class Rules : public std::map<std::pair<char,unsigned>,Rule> {
    using map::map;
};

class Tape : public std::map<unsigned,unsigned> {
    using map::map;
};

void loadRules( std::istream& is, char& beginState, unsigned& numSteps,
                Rules& rules );
#endif // DAY25_H
