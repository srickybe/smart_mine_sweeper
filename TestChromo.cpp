#include "TestChromo.h"
#include <iostream>
#include "Rand.h"

namespace ai {
	
	TestChromo::TestChromo() 
	: coefficients(),
	fitness(0) 
	{
		
	}
	
	TestChromo::TestChromo(int numberOfCoefficients) 
	: coefficients(numberOfCoefficients)
	{
		fitness = 1;
		
		for (int i = 0; i < numberOfCoefficients; ++i) {
			coefficients.operator[] (i) 
				= 1 + util::Rand<int>::getInstance().next(numberOfCoefficients);
			fitness *= coefficients.operator[] (i) ;
		}
	}
	
	TestChromo::TestChromo(TestChromo const & rhs) 
	: coefficients(rhs.coefficients),
	fitness(rhs.fitness)
	{
	}

	bool TestChromo::operator==(TestChromo const & rhs) const {
		return getFitness() == rhs.getFitness();
	}
	
	bool TestChromo::operator>(TestChromo const & rhs) const {
		return getFitness() > rhs.getFitness();
	}
	
	ngn::Real TestChromo::getCoefficient(int i) const {
		return coefficients.operator [](i);
	}
	
	ngn::Real TestChromo::getFitness() const {
		return fitness;
	}
	
	int unsigned TestChromo::numberOfCoefficients() const {
		return coefficients.size();
	}

	void TestChromo::print(std::ostream & out) const {
		for (int unsigned i = 0; i < numberOfCoefficients(); ++i) {
			out << "___" << getCoefficient(i);
		}
		
		out << "\n";
	}
	
	std::ostream & operator <<(std::ostream & out, TestChromo const & chromo) {
		chromo.print(out);
		
		return out;
	}
	
	void TestChromo::computeFitness(){
		
	}
	
	std::shared_ptr<Chromosome> TestChromo::copy() const {
		return std::shared_ptr<Chromosome>();
	}
	
	bool TestChromo::crossOver(Chromosome & chr, ngn::Real crossOverRate){
		return false;
	}
	
	bool TestChromo::equals(Chromosome const & chr) const {
		TestChromo const * other = dynamic_cast<TestChromo const *>(&chr);
		
		for (int unsigned i = 0; i < numberOfCoefficients(); ++i) {
			if (getCoefficient(i) < other->getCoefficient(i)) {
				return true;
			}
		}
		
		return false;
	}
	
	bool TestChromo::isSolution() const {
		return false;
	}
	
	bool TestChromo::mutate(ngn::Real mutationRate) {
		return false;
	}
}