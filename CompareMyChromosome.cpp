#include "CompareMyChromosome.h"
#include "MyChromosome.h"

namespace ai {

	CompareMyChromosome::CompareMyChromosome() {
	}

	bool CompareMyChromosome::operator()(MyChromosome const & lhs, MyChromosome const & rhs) const {
		return lhs.getFitness() == rhs.getFitness();
	}
}