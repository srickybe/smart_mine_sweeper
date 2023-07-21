#include "Reserve.h"
#include <iostream>
#include "Rand.h"
#include "TestChromo.h"

namespace ai {
	
	Reserve::Reserve() 
	: chromosomesByFitness() 
	{
	}

	bool Reserve::addChromosome(Reserve::ChromosomePtr const & chr) {
		Iterator it = chromosomesByFitness.find(chr->getFitness());
		
		if (it != end()) {
			//std::cout << "it != end()\n";
			//std::cout << "it->second.size() = " << it->second.size() << "\n";
			std::pair<SetIterator, bool> res = (it->second.insert(chr));
			//std::cout << "res.second = " << res.second << "\n";
			return res.second;
		} else {
			//std::cout << "it == end()\n";
			Set set;
			set.insert(chr);
			std::pair<Iterator, bool> res = chromosomesByFitness.insert(std::make_pair(chr->getFitness(), set));
			
			return res.second;
		}
	}

	template <class InputIterator>
	bool Reserve::addAllChromosomes(InputIterator beg, InputIterator end) {
		bool allAdded = true;

		for (InputIterator it = beg; it != end; ++it) {
			if (!addChromosome(*it)) {
				if (allAdded) {
					allAdded = false;
				}
			}
		}

		return allAdded;
	}

	std::shared_ptr<std::vector<Reserve::ChromosomePtr>> 
	Reserve::chromosomesWithFitnessEqualTo(ngn::Real fitness) const {
		ConstIterator it = chromosomesByFitness.find(fitness);
		
		if (it != end()) {
			std::shared_ptr<std::vector<ChromosomePtr>> res(new std::vector<ChromosomePtr>(it->second.begin(), it->second.end()));
			//std::cout << "res->size() = " << res->size() << "\n";
			
			return res;
		} else {
			std::shared_ptr<std::vector<ChromosomePtr>> res(new std::vector<ChromosomePtr>());
			
			return res;
		}
	}
	
	void Reserve::clear() {
		chromosomesByFitness.clear();
	}

	std::shared_ptr<std::vector<Reserve::ChromosomePtr>> Reserve::toArrayList() const {
		std::shared_ptr<std::vector<ChromosomePtr>> res(new std::vector<ChromosomePtr>());

		for (
			ConstReverseIterator it = rbegin();
			it != rend();
			++it
		)
		{
			//res->insert(it->second.begin(), it->second.end());
			for (SetIterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
				res->push_back(*it2);
			}
		}
		
		return res;
	}

	int Reserve::getNumberOfChromosomes() const {
		int res = 0;

		for (
			ConstIterator it = begin();
			it != end();
			++it
		)
		{
			res += it->second.size();
		}
			
		return res;
	}

	std::shared_ptr<std::vector<Reserve::ChromosomePtr>> Reserve::getNBestFitChromosomes(int nChrs) const {
		//std::cout << "std::shared_ptr<std::vector<Chromosome>> getNBestFitChromosomes(int nChrs) const\n";
		
		if (nChrs < 1) {
			return std::shared_ptr<std::vector<ChromosomePtr>>(new std::vector<ChromosomePtr>());
		}
		
		std::shared_ptr<std::vector<ChromosomePtr>> bestFit(new std::vector<ChromosomePtr>());
		int count = 0;

		for (
			ConstReverseIterator it = rbegin();
			it != rend();
			++it
		)
		{
			/*std::cout << "it->first = " << it->first << "\n";
			std::cout << "it->second.size() = " << it->second.size() << "\n";
			std::cout << "nChrs - count = " << nChrs - count << "\n";*/
			
			if ((int)it->second.size() <= nChrs - count) {
				//std::cout << "(int)it->second.size() <= nChrs - count\n";
				bestFit->insert(bestFit->end(), it->second.begin(), it->second.end());
				count += (int)it->second.size();
				//std::cout << "count = " << count << "\n";
			} else {
				SetIterator setIt = it->second.begin();
				
				for (int i = 0; i < nChrs - count; ++i) {
					bestFit->push_back(*setIt);
					/*std::cout << "%%%i = " << i << "\n";
					std::cout << "added to bestFits\n= " << *setIt << "\n";
					std::cout << "fitness = " << setIt->getFitness() << "\n";*/
					++setIt;
				}
				
				count += nChrs - count;
				//std::cout << "count = " << count << "\n";
				break;
			}
		}
		
		/*for (int i = 0; i < bestFit->size(); ++i) {
			std::cout << "+++i = " << i << "\n";
			std::cout << "bestFit->operator[](i) = " << bestFit->operator[](i) << "\n";
			std::cout << "bestFit->operator[](i).getFitness() = " << bestFit->operator[](i).getFitness() << "\n";
		}*/
		
		return bestFit;
	}

	void Reserve::print(std::ostream & out) const {
		int globalCount = 0;
		
		for (
			ConstIterator it1 = begin();
			it1 != end();
			++it1
		)
		{
			out << "fitness = " << it1->first << "\n";
			Set set = it1->second;
			
			for (
				ConstSetIterator it2 = set.begin();
				it2 != set.end();
				++it2
			)
			{
				out << globalCount << ":\n";
				out << *it2 << "\n";
				++globalCount;
			}
		}
		
		out << "\n";
	}
	
	void Reserve::test() {
		util::Rand<ngn::Real>::getInstance().setSeed(0);
		Reserve reserve;
		int nChrs = 100;
		std::vector<std::shared_ptr<TestChromo>> chromos;

		for (int i = 0; i < nChrs; ++i) {
			std::cout << "i = " << i << "\n";
			std::shared_ptr<TestChromo> chromo(new TestChromo(5));
			std::cout << "chromo_i = " << *chromo << "\n";
			chromos.push_back(chromo);
			std::cout << "chromos.push_back(chromo)\n";
			
			if (!reserve.addChromosome(chromo)) {
				std::cout << "chromo_" << i << " not added\n";
			}/* else {
				std::cout << "chromo_" << i << " added\n";
			}*/
		}

		std::cout << "reserve.size() =\n" << reserve.getNumberOfChromosomes() << "\n";
		std::cout << "reserve =\n" << reserve << "\n";
		std::cout << "reserve.addChromosome(tmp.operator[](0)) ?" << reserve.addChromosome(chromos.operator[](0)) << "\n";
		
		//var chrs = reserve.toArrayList();

		//for (var chr : chrs) {
		//	std::cout << "chr =\n" + chr);
		//	std::cout << "chr.getFitness() = " + chr.getFitness());
		//}

		std::cout << "reserve.getNumberOfChromosomes() = " << reserve.getNumberOfChromosomes() << "\n";
		std::shared_ptr<std::vector<ChromosomePtr>> nBestFits = reserve.getNBestFitChromosomes(25);
		std::cout << "nBestFits = \n";
		
		for (int unsigned i = 0; i < nBestFits->size(); ++i) {
			std::cout << "#####chr_" << i <<  " = " << *(nBestFits->operator[](i)) << "\n";
			std::cout << "*****fitness_" << i << " = " << nBestFits->operator[](i)->getFitness() << "\n";
		}
		
		int maxFitness = 3125;
		std::shared_ptr<std::vector<ChromosomePtr>> bestFits = reserve.chromosomesWithFitnessEqualTo(maxFitness);
		std::cout << "bestFits = \n";
		for (int unsigned i = 0; i < bestFits->size(); ++i) {
			std::cout << "#####chr_" << i <<  " = " << *(bestFits->operator[](i)) << "\n";
			std::cout << "*****fitness_" << i << " = " << bestFits->operator[](i)->getFitness() << "\n";
		}
		
		int fitness = 240;
		std::shared_ptr<std::vector<ChromosomePtr>> fits = reserve.chromosomesWithFitnessEqualTo(fitness);
		std::cout << "fits = \n";
		for (int unsigned i = 0; i < fits->size(); ++i) {
			std::cout << "#####chr_" << i <<  " = " << *(fits->operator[](i)) << "\n";
			std::cout << "*****fitness_" << i << " = " << fits->operator[](i)->getFitness() << "\n";
		}
	}
	
	Reserve::Iterator Reserve::begin() {
		return chromosomesByFitness.begin();
	}
	
	Reserve::ConstIterator Reserve::begin() const {
		return chromosomesByFitness.begin();
	}
	
	Reserve::Iterator Reserve::end() {
		return chromosomesByFitness.end();
	}
	
	Reserve::ConstIterator Reserve::end() const {
		return chromosomesByFitness.end();
	}
	
	Reserve::ConstReverseIterator Reserve::rbegin() const {
		return chromosomesByFitness.rbegin();
	}
	
	Reserve::ConstReverseIterator Reserve::rend() const {
		return chromosomesByFitness.rend();
	}
	
	std::ostream & operator <<(std::ostream & out, Reserve const & reserve) {
		reserve.print(out);
		
		return out;
	}
}