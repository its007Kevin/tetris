#ifndef MAXLEVEL_H
#define MAXLEVEL_H
#include <exception>

class MaxLevel: public std::exception {

	virtual const char* what() const throw() {
		return "Max level reached";
	}

};

#endif