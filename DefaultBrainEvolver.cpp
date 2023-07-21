#include "DefaultBrainEvolver.h"
#include "GeneticAlgorithm.h"

namespace smrtsw {
	
	DefaultBrainEvolver::DefaultBrainEvolver(ai::Settings const & GASettings) :
		GASettings_(GASettings)
	{
		
	}

	std::vector<ai::Population>
	DefaultBrainEvolver::evolveBrains(std::vector<ai::Population> const & populations) const {
		ai::GeneticAlgorithm algorithm(populations, GASettings_);
		algorithm.solve();
		std::vector<ai::Population> result = algorithm.getPopulations();

		return result;
	}
}