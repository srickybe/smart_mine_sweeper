#ifndef COMPARE_CHROMOSOME_H
#define COMPARE_CHROMOSOME_H

#include "Chromosome.h"

namespace ai {
	
	class CompareChromosome {
	public:
		CompareChromosome();
		
		bool operator() (
			SharedPtrChromosome const & lhs, 
			SharedPtrChromosome const & rhs
		) const;
	};
}

#endif // COMPARE_CHROMOSOME_H