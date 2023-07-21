#include "MyChromosome.h"
#include <iostream>
#include "UnsupportedOperationException.h"

namespace ai {

	MyChromosome::MyChromosome(ngn::Real param) 
	:fitness(param)
	{
	}
	
	void MyChromosome::computeFitness() {
	}

	std::shared_ptr<Chromosome> MyChromosome::copy() const {
		throw UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
	}
	
	bool MyChromosome::crossOver(Chromosome & chr, ngn::Real crossOverRate) {
		throw UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
	}
	
	bool MyChromosome::equals(Chromosome const & chr) const {
		MyChromosome const * other = dynamic_cast<MyChromosome const *>(&chr);
 
		return fitness < other->fitness;
	}
	
	ngn::Real MyChromosome::getFitness() const {
		return fitness;
	}
	
	bool MyChromosome::isSolution() const {
		throw UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
	}
	
	bool MyChromosome::mutate(ngn::Real mutationRate) {
		throw UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
	}
	
	void MyChromosome::print(std::ostream & out) const {
		out << "MyChromosome{" << "fitness=" << fitness << "}";
	}
	
	std::ostream & operator <<(std::ostream & out, MyChromosome const & chr) {
		chr.print(out);
		
		return out;
	}
}