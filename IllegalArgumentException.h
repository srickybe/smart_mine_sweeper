#ifndef ILLEGAL_ARGUMENT_EXCEPTION_H
#define ILLEGAL_ARGUMENT_EXCEPTION_H

#include <exception>
#include <string>

class IllegalArgumentException: std::exception {
public:
	IllegalArgumentException(std::string const & message) : message_(message) {
		
	}
	
	char const * what() const throw() {
		return message_.c_str();
	}
	
private:
	std::string message_;
};

#endif // ILLEGAL_ARGUMENT_EXCEPTION_H