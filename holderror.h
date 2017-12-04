#ifndef HOLDERROR_H
#define HOLDERROR_H
#include <exception>

class HoldError: public std::exception {

	virtual const char* what() const throw() {
		return "You cannot hold twice in one turn!";
	}

};

#endif