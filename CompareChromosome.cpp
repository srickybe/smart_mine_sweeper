#include "CompareChromosome.h"

namespace ai {

	CompareChromosome::CompareChromosome() {
		
	}
	
	bool CompareChromosome::operator() (
		SharedPtrChromosome const & lhs, 
		SharedPtrChromosome const & rhs
	) const {
		return lhs->equals(*rhs);
	}
}