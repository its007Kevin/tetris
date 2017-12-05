#ifndef INVALIDMOVE_H
#define INVALIDMOVE_H
#include <exception>

class InvalidMove: public std::exception {
public:
	virtual const char* what() const throw() {
		return "Invalid Move";
	}

};

#endif

