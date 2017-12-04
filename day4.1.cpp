/*
--- Day 4: High-Entropy Passphrases ---

A new system policy has been put in place that requires all accounts to use a passphrase instead of simply a password. A passphrase consists of a series of words (lowercase letters) separated by spaces.

To ensure security, a valid passphrase must contain no duplicate words.

For example:

aa bb cc dd ee is valid.
aa bb cc dd aa is not valid - the word aa appears more than once.
aa bb cc dd aaa is valid - aa and aaa count as different words.
The system's full passphrase list is available as your puzzle input. How many passphrases are valid?
*/

#include <iostream>
#include <set>
#include <sstream>

int main ( int argc, char **argv ) {
	std::string line;

	int numValid = 0;

	while ( std::getline( std::cin, line) ) {
		std::istringstream parser( line );

		std::set<std::string> m;
		bool valid = true;
		while ( parser ) {
			std::string token;

			parser >> token;
			if ( parser ) {
				if ( m.find( token ) == m.end() ) {
					m.insert( token );
				} else {
					valid = false;
				}
			}
		}

		if ( valid ) numValid ++;
	}

	std::cout << "Num valid: " << numValid << std::endl;
}
