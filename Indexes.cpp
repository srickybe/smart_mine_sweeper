#include "Indexes.h"

namespace ngn {
	
	std::ostream & operator <<(std::ostream & out, Indexes const & indexes) {
		return indexes.print(out);
	}
}