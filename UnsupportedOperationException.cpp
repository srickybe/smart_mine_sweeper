#include "UnsupportedOperationException.h"
#include <iostream>

UnsupportedOperationException::UnsupportedOperationException(std::string const & message) 
: message_(message)
{
	std::cout << "message = " << message << "\n";
}
	
	
char const * UnsupportedOperationException::what() const throw() {
	return message_.c_str();
}