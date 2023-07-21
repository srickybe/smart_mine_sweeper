#include "Function.h"

namespace ngn {
	
	std::ostream & operator << (std::ostream & out, Function const & function) {
		return function.print(out);
	}
}