#ifndef TEST_CHROMO_H
#define TEST_CHROMO_H

#include <iosfwd>
#include <memory>
#include <vector>
#include "Chromosome.h"

namespace ai {
	
	class TestChromo: public Chromosome {
	public:
		
		TestChromo();
		TestChromo(int numberOfCoefficients);
		TestChromo(TestChromo const & rhs);
		bool operator==(TestChromo const & rhs) const;
		bool operator>(TestChromo const & rhs) const;
		ngn::Real getCoefficient(int i) const;
		ngn::Real getFitness() const;
		int unsigned numberOfCoefficients() const;
		
		void computeFitness();
		std::shared_ptr<Chromosome> copy() const;
		bool crossOver(Chromosome & chr, ngn::Real crossOverRate);
		bool equals(Chromosome const & chr) const;
		bool isSolution() const;
		bool mutate(ngn::Real mutationRate);
		void print(std::ostream & out) const;
		
	private:
		std::vector<int> coefficients;
		ngn::Real fitness;
	};
	
	std::ostream & operator <<(std::ostream & out, TestChromo const & chromo);
}

#endif // TEST_CHROMO_H