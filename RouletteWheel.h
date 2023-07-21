#ifndef ROULETTE_WHEEL_H
#define ROULETTE_WHEEL_H

#include <iostream>
#include "Chromosome.h"
#include "CompareChromosome.h"
#include "MyChromosome.h"
#include "Population.h"
#include "Rand.h"
#include "Real.h"
#include "Selector.h"
#include "UnsupportedOperationException.h"

namespace ai {
	
	class RouletteWheel: public Selector {
		
	public:
		
		RouletteWheel();
		Population const & getPopulation() const;
		
		void print(std::ostream & out) const;
		void setPopulation(Population const & chrs);
		SharedPtrChromosome select();
		static void test();
		
	private:
		Population population;
		std::vector<ngn::Real> fitnesses;
		ngn::Real sumOfFitnesses;
		std::vector<ngn::Real> cumulativeFitnesses;
		
		void addCumulativeFitness(ngn::Real fitness);
		void addFitness(ngn::Real fitness);
		int populationSize() const;
		bool isPopulationEmpty() const;
		SharedPtrChromosome const & getChromosome(int i) const;
		ngn::Real getFitness(int i) const;
		ngn::Real getSumOfFitnesses() const;
		ngn::Real getCumulativeFitness(int i) const;
		void computeCumulativeFitnesses();
		void computeFitnesses();
	};
	
	std::ostream & operator <<(std::ostream & out, RouletteWheel const & rouletteWheel);
}

#endif // ROULETTE_WHEEL_H