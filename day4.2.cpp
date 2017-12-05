/*
--- Part Two ---

For added security, yet another system policy has been put in place. Now, a valid passphrase must contain no two words that are anagrams of each other - that is, a passphrase is invalid if any word's letters can be rearranged to form any other word in the passphrase.

For example:

abcde fghij is a valid passphrase.
abcde xyz ecdab is not valid - the letters from the third word can be rearranged to form the first word.
a ab abc abd abf abj is a valid passphrase, because all letters need to be used when forming another word.
iiii oiii ooii oooi oooo is valid.
oiii ioii iioi iiio is not valid - any of these words can be rearranged to form any other word.
Under this new system policy, how many passphrases are valid?
*/

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <sstream>
#include <string>

int main ( int argc, char **argv ) {
    std::string line;

    int numValid = 0;

    while ( std::getline( std::cin, line) ) {
        std::istringstream parser( line );

        std::unordered_set<std::string> m;
        bool valid = true;
        while ( parser ) {
            std::string token;

            parser >> token;
            if ( parser ) {
                std::sort(token.begin(), token.end());

                if ( m.find( token ) == m.end() ) {
                    m.insert( token );
                } else {
                    valid = false;
                }
            }
        }

        if ( valid ) numValid ++;
    }

    std::cout << numValid << std::endl;
}
