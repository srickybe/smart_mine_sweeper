#ifndef RESERVE_1_H
#define RESERVE_1_H

#include <iosfwd>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include "Chromosome.h"
#include "CompareChromosome.h"
#include "Real.h"

namespace ai {

	class Reserve;
	class CompareTestChromo;
	std::ostream & operator <<(std::ostream & out, Reserve const & reserve);
	
	class Reserve {

	public:
		typedef SharedPtrChromosome ChromosomePtr;
		typedef std::set<ChromosomePtr, CompareChromosome> Set;
		typedef std::map<ngn::Real, Set> ChromosomeMap;
		typedef typename ChromosomeMap::iterator Iterator;
		typedef typename ChromosomeMap::const_iterator ConstIterator;
		typedef typename ChromosomeMap::const_reverse_iterator ConstReverseIterator;
		typedef typename Set::iterator SetIterator;
		typedef typename Set::const_iterator ConstSetIterator;
		
		
		Reserve();

		bool addChromosome(Reserve::ChromosomePtr const & chr);
		
		template <class InputIterator>
		bool addAllChromosomes(InputIterator beg, InputIterator end);
		
		std::shared_ptr<std::vector<ChromosomePtr>> 
		chromosomesWithFitnessEqualTo(ngn::Real fitness) const;
		
		void clear();
		
		std::shared_ptr<std::vector<ChromosomePtr>> toArrayList() const;

		int getNumberOfChromosomes() const;

		std::shared_ptr<std::vector<ChromosomePtr>> getNBestFitChromosomes(int nChrs) const;
		
		void print(std::ostream & out) const;
		
		static void test();
		
	private:
		ChromosomeMap chromosomesByFitness;
		
		Iterator begin();
		ConstIterator begin() const;
		Iterator end();
		ConstIterator end() const;
		ConstReverseIterator rbegin() const;
		ConstReverseIterator rend() const;
	};
	
	
	std::ostream & operator <<(std::ostream & out, Reserve const & reserve);
}

#endif // RESERVE_1_H