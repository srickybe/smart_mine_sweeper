#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <iosfwd>
#include <memory>
#include "Real.h"

namespace ai {
	
	class Chromosome {

	public:
		virtual void computeFitness() = 0;
		
		virtual std::shared_ptr<Chromosome> copy() const = 0;

		virtual bool crossOver(Chromosome & chr, ngn::Real crossOverRate) = 0;
		
		virtual bool equals(Chromosome const & chr) const = 0;
		
		virtual ngn::Real getFitness() const = 0;
		
		virtual bool isSolution() const = 0;

		virtual bool mutate(ngn::Real mutationRate) = 0;
		
		virtual void print(std::ostream & out) const = 0;
	};
	
	std::ostream & operator<<(std::ostream & out, Chromosome const & chr);
	typedef std::shared_ptr<Chromosome> SharedPtrChromosome;
}

#endif // CHROMOSOME_H