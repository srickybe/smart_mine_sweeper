#ifndef POPULATION_H
#define POPULATION_H

#include <memory>
#include <vector>
#include "Chromosome.h"
#include "Real.h"

namespace ai {
	
	class Population {
	public:
		typedef std::vector<SharedPtrChromosome> Array;
		typedef std::vector<SharedPtrChromosome>::iterator Iterator;
		typedef std::shared_ptr<Array> ArrayPtr;
		
		Population();
		Population(Population const & rhs);
		Population(ArrayPtr const & chrs);

		bool add(SharedPtrChromosome const & chr);
		void addAll(Population const & population);
		ngn::Real averageFitness() const;
		void clear();
		void computeFitnesses();
		SharedPtrChromosome const & first() const;
		SharedPtrChromosome const & get(int i) const;
		ArrayPtr getNBestFit(int nChrs) const;
		bool isEmpty() const;
		Iterator begin() const;
		Iterator end() const;
		void remove(int i);
		void set(int i, SharedPtrChromosome const & chr);
		void shuffle();
		int size() const;
		void sortInDescendingOrder();
		ArrayPtr toArrayList() const;
		
	private:
		std::shared_ptr<std::vector<SharedPtrChromosome>> genotypes;
		
		void addAll(ArrayPtr const & chromosomes);
	};
}

#endif // POPULATION_H