#include "Intersectable.h"
#include <iostream>

namespace ngn {
	
	std::ostream & operator << (std::ostream & out, Intersectable const & intersectable) {
		intersectable.print(out);
		
		return out;
	}
}