#ifndef DEFAULT_BRAIN_EVOLVER_H
#define DEFAULT_BRAIN_EVOLVER_H
	
#include "BrainEvolver.h"
#include "Settings.h"

namespace smrtsw {
	
	class DefaultBrainEvolver: public BrainEvolver {
	public:
		DefaultBrainEvolver(ai::Settings const & GASettings);
	
		std::vector<ai::Population>
		evolveBrains(std::vector<ai::Population> const & populations) const;
		
	private:
		ai::Settings GASettings_;
	};	
}

#endif // DEFAULT_BRAIN_EVOLVER_H