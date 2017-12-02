#ifndef MINLEVEL_H
#define MINLEVEL_H
#include <exception>

class MinLevel: public std::exception {

	virtual const char* what() const throw() {
		return "Minimum level reached";
	}

};

#endif