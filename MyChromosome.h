#ifndef MY_CHROMOSOME_H
#define MY_CHROMOSOME_H

#include <iosfwd>
#include <memory>
#include "Chromosome.h"
#include "Real.h"

namespace ai {
	
	class MyChromosome: public Chromosome {

	public:
		MyChromosome(ngn::Real fitness);
		
		void computeFitness();

		std::shared_ptr<Chromosome> copy() const;

		bool crossOver(Chromosome & chr, ngn::Real crossOverRate);

		bool equals(Chromosome const & chr) const;
		
		ngn::Real getFitness() const ;

		bool isSolution() const;

		bool mutate(ngn::Real mutationRate);

		void print(std::ostream & out) const;
		
	private:
		ngn::Real fitness;
	};
	
	std::ostream & operator <<(std::ostream & out, MyChromosome const & chr);
}

#endif // MY_CHROMOSOME_H