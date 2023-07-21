#include "Chromosome.h"
#include <iostream>

namespace ai {
	
	std::ostream & operator<<(std::ostream & out, Chromosome const & chr) {
		chr.print(out);
		
		return out;
	}
}