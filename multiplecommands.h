#ifndef MULTIPLECOMMANDS_H
#define MULTIPLECOMMANDS_H
#include <exception>
#include <stdexcept>
#include <string>

class MultipleCommands: public std::runtime_error {
public:
	MultipleCommands(const std::string &input) noexcept: std::runtime_error("Multiple commands contain '" + input + "' as a substring") {}

};

#endif