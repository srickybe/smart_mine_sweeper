#include "Tournament.h"
#include <iostream>
#include "Math.h"
#include "Population.h"
#include "Rand.h"
#include "Real.h"
#include "UnsupportedOperationException.h"

namespace ai {
	
	Tournament::Tournament(int sizeParam) 
	: population(),
	copy(),
	size(sizeParam)
	{
	}

	
	Tournament::ChromosomePtr Tournament::select() { 
		
		if (population.isEmpty()) {
			throw UnsupportedOperationException("Population is empty!!!");
		}
		
		int choice = util::Rand<int>::getInstance().next(population.size());

		ChromosomePtr bestFit = population.get(choice);
		ngn::Real bestFitness = population.get(choice)->getFitness();
		int nChoices = ngn::Math<int>::min(size, population.size());
		
		for (int j = 1; j < nChoices; ++j) {
			int index = util::Rand<int>::getInstance().next(population.size());
			ChromosomePtr chr = population.get(index);
			ngn::Real eval = population.get(index)->getFitness();

			if (eval > bestFitness) {
				bestFitness = eval;
				bestFit = chr;
				choice = index;
			}
		}

		population.remove(choice);
		replete();

		return bestFit;
	}

	
	void Tournament::setPopulation(Population const & chromos) {
		if (!chromos.isEmpty()) {
			this->population = Population();
			this->population.addAll(chromos);
			this->copy = Population();
			this->copy.addAll(chromos);
		} else {
			throw UnsupportedOperationException("chromos is empty!!!");
		}
	}

	void Tournament::replete() {
		if (population.isEmpty()) {
			this->population.addAll(this->copy);
		}
	}

	int Tournament::getSize() const {
		return size;
	}

	void Tournament::print(std::ostream & out) const {
		out << "Tournament{" << "size=" << size << "}";
	}
}