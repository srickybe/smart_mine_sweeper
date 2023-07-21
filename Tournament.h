#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <memory>
#include "Selector.h"

namespace ai {

	class Population;
	
	class Tournament: public Selector {
	public:
		typedef std::shared_ptr<Population> PopulationPtr;
		typedef std::shared_ptr<Chromosome> ChromosomePtr;
		
		Tournament(int sizeParam);
		
		ChromosomePtr select();
		void setPopulation(Population const & chromos);
		void replete();
		int getSize() const;
		void print(std::ostream & out) const;
		
	private:
		Population population;
		Population copy;
		int size;
	};
}

#endif // TOURNAMENT_H