#include "RouletteWheel.h"
#include <map>

namespace ai {
	
	RouletteWheel::RouletteWheel() {
	}

	Population const & RouletteWheel::getPopulation() const {
		return population;
	}

	void RouletteWheel::print(std::ostream & out) const {
		out << "RouletteWheel{";
		//out << "\npopulation=" << population;
		//out << ", \nfitnesses=" << fitnesses;
		//out << ", \nsumFits=" << sumOfFitnesses;
		//out << ", \ncumulFits=" << cumulativeFitnesses;
		out << "\n}";
	}
	
	void RouletteWheel::setPopulation(Population const & chrs) {
		this->population = chrs;
		this->fitnesses = std::vector<ngn::Real>();
		this->cumulativeFitnesses = std::vector<ngn::Real>();
		computeCumulativeFitnesses();
	}

	
	SharedPtrChromosome RouletteWheel::select() {
		if (getSumOfFitnesses() != 0) {
			ngn::Real random = util::Rand<ngn::Real>::getInstance().next();

			for (int index = 0; index < populationSize(); ++index) {
				if (getCumulativeFitness(index) >= random) {
					return getChromosome(index);
				}
			}

			return getChromosome(populationSize() - 1);
		} else {
			if (!isPopulationEmpty()) {
				int index = util::Rand<int>::getInstance().next(populationSize());

				return getChromosome(index);
			} else {
				throw UnsupportedOperationException("");
			}
		}
	}

	void RouletteWheel::test() {
		int nChrs = 5;
		std::vector<ngn::Real> fitnesses;
		Population population;
		std::cout << "OK0\n";

		for (int i = 0; i < nChrs; ++i) {
			fitnesses.push_back((ngn::Real)(util::Rand<int>::getInstance().next(100)));
		}
		
		ngn::Real sum = 0.0;
		
		for (int i = 0; i < nChrs; ++i) {
			sum += fitnesses.at(i);
		}
		
		for (int i = 0; i < nChrs; ++i) {
			fitnesses.operator[](i) = fitnesses.at(i) / sum;
		}

		std::cout << "adding chromosomes to population\n";
		
		for (int i = 0; i < nChrs; ++i) {
			SharedPtrChromosome chr(new MyChromosome(fitnesses.at(i)));
			population.add(chr);
		}
		
		//std::cout << "OK1\n";
		
		RouletteWheel rw;
		rw.setPopulation(population);
		std::map<SharedPtrChromosome, int, CompareChromosome> numberOfChoices;

		for (int i = 0; i < 1.0e8; ++i) {
			SharedPtrChromosome chr = rw.select();
			typename std::map<SharedPtrChromosome, int, CompareChromosome>::iterator it = numberOfChoices.find(chr);
			
			if (it != numberOfChoices.end()) {
				it->second += 1;	
			} else {
				numberOfChoices.insert(std::make_pair(chr, 1));
			}
		}

		std::cout << "numberOfChoices.size() = " << numberOfChoices.size() << "\n";
		int count = 0;
		typename std::map<SharedPtrChromosome, int, CompareChromosome>::iterator it;
		
		for (it = numberOfChoices.begin(); it != numberOfChoices.end(); ++it) {
			std::cout << "i = " + count << "\n";
			std::cout << "Chromosome = " << *(it->first) << "\n";
			std::cout << "number of choices = " << it->second << "\n";
			++count;
		}
	}
	
	void RouletteWheel::addCumulativeFitness(ngn::Real fitness) {
		cumulativeFitnesses.push_back(fitness);
	}

	void RouletteWheel::addFitness(ngn::Real fitness) {
		fitnesses.push_back(fitness);
	}

	int RouletteWheel::populationSize() const {
		return population.size();
	}

	bool RouletteWheel::isPopulationEmpty() const {
		return population.isEmpty();
	}

	SharedPtrChromosome const & RouletteWheel::getChromosome(int i) const {
		return population.get(i);
	}

	ngn::Real RouletteWheel::getFitness(int i) const {
		return fitnesses.at(i);
	}

	ngn::Real RouletteWheel::getSumOfFitnesses() const {
		return sumOfFitnesses;
	}

	ngn::Real RouletteWheel::getCumulativeFitness(int i) const {
		return cumulativeFitnesses.at(i);
	}

	void RouletteWheel::computeCumulativeFitnesses() {
		computeFitnesses();

		if (getSumOfFitnesses() == 0.0) {
			std::cout << "population size = " << populationSize() << "\n";

			return;
		}

		addCumulativeFitness(getFitness(0) / getSumOfFitnesses());

		for (int i = 1; i < populationSize(); ++i) {
			addCumulativeFitness(getCumulativeFitness(i - 1) + getFitness(i) / getSumOfFitnesses());
		}
	}

	void RouletteWheel::computeFitnesses() {
		sumOfFitnesses = 0.0;

		for (int i = 0; i < populationSize(); ++i) {
			addFitness(getChromosome(i)->getFitness());
			sumOfFitnesses += getFitness(i);
		}
	}

	std::ostream & operator <<(std::ostream & out, RouletteWheel const & rouletteWheel) {
		rouletteWheel.print(out);
		
		return out;
	}
}