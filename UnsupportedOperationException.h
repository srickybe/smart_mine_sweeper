#ifndef UNSUPPORTED_OPERATION_EXCEPTION_H
#define UNSUPPORTED_OPERATION_EXCEPTION_H

#include <exception>
#include <string>

class UnsupportedOperationException: public std::exception {
public:
	UnsupportedOperationException(std::string const & message);
	char const * what() const throw();
	
private:
	std::string message_;
};

#endif // UNSUPPORTED_OPERATION_EXCEPTION_H