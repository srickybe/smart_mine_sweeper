#include "Selector.h"
#include <iostream>

namespace ai {
	
	std::ostream & operator<<(std::ostream & out, Selector const & selector) {
		selector.print(out);
		
		return out;
	}
}