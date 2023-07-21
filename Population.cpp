#include "Population.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include "Rand.h"

namespace ai {
	
	Population::Population() 
	: genotypes(new Population::Array())
	{
		
	}

	Population::Population(Population const & rhs) 
	: genotypes(rhs.genotypes)
	{
		
	}
	
	Population::Population(ArrayPtr const & chrs) 
	:genotypes(chrs)
	{
	}

	bool Population::add(SharedPtrChromosome const & chr) {
		genotypes->push_back(chr);
		
		return true;
	}
	
	void Population::addAll(Population const & population) {
		addAll(population.genotypes);

	}

	ngn::Real Population::averageFitness() const {
		ngn::Real res = (ngn::Real)0.0;

		for (int i = 0; i < size(); ++i) {
			res += get(i)->getFitness();
		}

		res /= size();

		return res;
	}

	void Population::clear() {
		genotypes->clear();
	}

	void Population::computeFitnesses() {
		for (long unsigned int i = 0; i < genotypes->size(); ++i) {
			genotypes->at(i)->computeFitness();
		}
	}

	SharedPtrChromosome const & Population::first() const {
		return genotypes->at(0);
	}

	SharedPtrChromosome const & Population::get(int i) const {
		return genotypes->at(i);
	}

	/*The ArrayList chrs must be ordered in descending order of fitness
	Returns the N first different best fits
	 */
	Population::ArrayPtr Population::getNBestFit(int nChrs) const {
		std::set<SharedPtrChromosome> tmp;
		int count = 0;

		for (int i = 0; i < this->size() && count < nChrs; ++i) {
			std::pair<typename std::set<SharedPtrChromosome>::iterator,bool> pair;
			pair = tmp.insert(this->get(i));
			
			if (std::get<1>(pair)) {
				++count;
			}
		}

		ArrayPtr res(new std::vector<SharedPtrChromosome>(tmp.begin(), tmp.end()));

		return res;
	}

	bool Population::isEmpty() const {
		return genotypes->empty();
	}

	Population::Iterator Population::begin() const {
		return genotypes->begin();
	}
	
	Population::Iterator Population::end() const {
		return genotypes->end();
	}
	
	void Population::remove(int i) {
		genotypes->erase(genotypes->begin() + i);
	}

	void Population::set(int i, SharedPtrChromosome const & chr) {
		genotypes->operator [](i) = chr;
	}

	void Population::shuffle() {
		for (int i = 0; i < this->size(); ++i) {
			int j = util::Rand<int>::getInstance().next(this->size());
			SharedPtrChromosome const & tmp = this->get(i);
			this->set(i, this->get(j));
			this->set(j, tmp);
		}
	}

	int Population::size() const {
		return genotypes->size();
	}

	void Population::sortInDescendingOrder() {
		class ChromosomePtrComparator {
		public:
			ChromosomePtrComparator() {}
			
			bool operator()(SharedPtrChromosome const & chr1, SharedPtrChromosome const & chr2) const {
				return chr1->getFitness() > chr2->getFitness();
			}
		};
		
		std::sort(genotypes->begin(), genotypes->end(), ChromosomePtrComparator()/*, std::greater<SharedPtrChromosome>()*/);
		
		//for (int unsigned i = 0; i < genotypes->size(); ++i) {
			//std::cout << i << ": " << genotypes->operator[](i) << "\n";
			//std::cout << i << ": " << genotypes->operator[](i)->getFitness() << "\n";
		//}
	}

	Population::ArrayPtr Population::toArrayList() const {
		return genotypes;
	}
	
	void Population::addAll(Population::ArrayPtr const & chromosomes) {
		genotypes->insert(genotypes->end(), chromosomes->begin(), chromosomes->end());
	}
}