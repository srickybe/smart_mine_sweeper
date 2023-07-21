#ifndef BRAIN_EVOLVER_H
#define BRAIN_EVOLVER_H

#include <memory>
#include <vector>
#include "Population.h"

namespace smrtsw {
	
	class BrainEvolver {
	public:
		virtual std::vector<ai::Population> 
		evolveBrains(std::vector<ai::Population> const & populations) const = 0;
		
	private:
	};
	
	typedef std::shared_ptr<BrainEvolver> SharedPtrBrainEvolver;
}

#endif // BRAIN_EVOLVER_H