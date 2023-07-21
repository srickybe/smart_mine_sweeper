#include "Solver.h"
#include <iostream>
#include "Chromosome.h"
#include "IllegalArgumentException.h"
#include "Math.h"
#include "Real.h"
#include "Settings.h"
#include "UnsupportedOperationException.h"

namespace ai {
	
	Solver::Solver(
			Population const & chrs,
			SelectorSmartPtr const & select,
			Settings const & settings,
			std::string const & name
	) :
		population(chrs),
		initialPopulationSize(chrs.size()),
		criticalSizeOfReserve(settings.getCriticalSizeOfReserve()),
		maximumNumberOfGenerations(settings.getMaximumNumberOfGenerations()),
		crossOverRate(settings.getCrossOverRate()),
		mutationRate(settings.getMutationRate()),
		selectionRate(settings.getSelectionRate()),
		restartThreshold(settings.getRestartThreshold()),
		bestFit(),
		bestFitByGeneration(),
		averageFitnessByGeneration({chrs.averageFitness()}),
		reserve(),
		selector(select),
		name(name),
		currentGenerationNumber(0),
		generationForLocalMaximumTest(settings.getRestartThreshold()),
		stopped(false),
		verbose(settings.isVerbose())
	{
		
	}

	//
	//population must be sorted in descending order
	//
	bool Solver::addNBestFitFromPopulationToReserve(int nChrs) {
		if (nChrs <= 0) {
			throw IllegalArgumentException("Number of chromosomes inferior or equal to zero");
		}

		int count = 0;

		/*ChromosomePtr chr : population*/
		for (int i = 0; i < populationSize(); ++i) {
			if (reserve.addChromosome(population.get(i))) {
				++count;
			}

			if (count == nChrs) {
				break;
			}
		}

		if (isVerbose()) {
			if (count != nChrs) {
				std::cout << "Less than " << nChrs << " chromosomes added\n";
			}
		}

		return count == nChrs;
	}

	void Solver::addNBestFitToReserve() {
		int numberOfChromosomes = populationSize() / getRestartThreshold();
		addNBestFitFromPopulationToReserve(numberOfChromosomes);

		if (sizeOfReserve() > getCriticalSizeOfReserve()) {
			if (isVerbose()) {
				std::cout << "###Thread-" << name << "...reserve has passed the maximum\n";
				std::cout << "...reserve size = " << reserve.getNumberOfChromosomes() << "\n";
			}

			Solver::PtrToArrayOfChromosomePtr nBestFit;
			nBestFit = getNBestFitFromReserve(getInitialPopulationSize());
			clearReserve();
			addToReserve(nBestFit->begin(), nBestFit->end());

			if (isVerbose()) {
				std::cout << "new size = " << sizeOfReserve() <<"\n";
			}
		}
	}

	void Solver::addToAverageFitnessByGeneration(ngn::Real averageFitness) {
		averageFitnessByGeneration.push_back(averageFitness);
	}

	template <class InputIterator>
	void Solver::addToReserve(InputIterator const & beg, InputIterator const & end) {
		for (InputIterator it = beg; it != end; ++it) {
			reserve.addChromosome(*it);
		}
	}

	void Solver::addToBestFitByGeneration(SharedPtrChromosome const & chr) {
		bestFitByGeneration.push_back(chr);
	}

	void Solver::clearPopulation() {
		population.clear();
	}

	ngn::Real Solver::bestFitness() const {
		if (bestFit != 0) {
			return bestFit->getFitness();
		} else {
			return 0;
		}
	}

	void Solver::clearReserve() {
		reserve.clear();
	}

	void Solver::computeAverageFitness() {
		addToAverageFitnessByGeneration(population.averageFitness());
	}

	void Solver::computeFitnesses() {
		population.computeFitnesses();
	}

	ngn::Real Solver::currentAverageFitness() const {
		return averageFitnessByGeneration.operator[](averageFitnessByGeneration.size() - 1);
	}

	SharedPtrChromosome const & Solver::getBestFit() const {
		return bestFit;
	}

	SharedPtrChromosome const & Solver::getBestFitOfGeneration(int generation) const {
		return bestFitByGeneration.operator[](generation);
	}

	int Solver::getCriticalSizeOfReserve() const {
		return criticalSizeOfReserve;
	}

	ngn::Real Solver::getCrossOverRate() const {
		return crossOverRate;
	}

	ngn::Real Solver::getCurrentAverageFitness() const {
		return averageFitnessByGeneration.operator[](averageFitnessByGeneration.size() - 1);
	}

	int Solver::getCurrentGenerationNumber() const {
		return currentGenerationNumber;
	}

	int Solver::getInitialPopulationSize() const {
		return initialPopulationSize;
	}

	int Solver::getGenerationForLocalMaximumTest() const {
		return generationForLocalMaximumTest;
	}

	int Solver::getMaximumNumberOfGenerations() const {
		return maximumNumberOfGenerations;
	}

	ngn::Real Solver::getMutationRate() const {
		return mutationRate;
	}

	Solver::PtrToArrayOfChromosomePtr 
	Solver::getNBestFitFromPopulation(int nChrs) const {
		Solver::PtrToArrayOfChromosomePtr res;
		res = population.getNBestFit(nChrs);
		
		//for (int unsigned i = 1; i < res->size(); ++i) {
			//SharedPtrChromosome chr1 = res->operator [](i-1);
			//SharedPtrChromosome chr2 = res->operator [](i);
			
			//if (chr1->getFitness() < chr2->getFitness()) {
				//throw UnsupportedOperationException("chr1->getFitness() < chr2->getFitness()");
			//}
		//}

		return res;
	}

	Solver::PtrToArrayOfChromosomePtr 
	Solver::getNBestFitFromReserve(int nChrs) const {
		Solver::PtrToArrayOfChromosomePtr res;
		res = reserve.getNBestFitChromosomes(nChrs);

		return res;
	}

	Population const & Solver::getPopulation() const {
		return population;
	}

	int Solver::getRestartThreshold() const {
		return restartThreshold;
	}

	ngn::Real Solver::getSelectionRate() const {
		return selectionRate;
	}

	SelectorSmartPtr const & Solver::getSelector() const {
		return selector;
	}

	bool Solver::hasEnded() const {
		/*std::cout << "getCurrentGenerationNumber() = " << getCurrentGenerationNumber() << "\n";
		std::cout << "getMaximumNumberOfGenerations() = " << getMaximumNumberOfGenerations() << "\n";*/
		return getCurrentGenerationNumber() == getMaximumNumberOfGenerations();
	}

	bool Solver::hasSolution() const {
		if (bestFit != 0) {
			return bestFit->isSolution();
		} else {
			return false;
		}
	}

	void Solver::incrementCurrentGeneration() {
		currentGenerationNumber = currentGenerationNumber + 1;
	}

	bool Solver::isLocalMinimum() {
		if (getCurrentGenerationNumber() >= getGenerationForLocalMaximumTest()) {
			int gen = numberOfBestFits() - 1;
			int lastGen = getCurrentGenerationNumber() - getRestartThreshold() + 1;

			while (gen >= lastGen) {
				SharedPtrChromosome chr1 = getBestFitOfGeneration(gen);
				SharedPtrChromosome chr2 = getBestFitOfGeneration(gen - 1);
				bool haveEqualFitnesses = 
					ngn::Math<ngn::Real>::areEqualWithTol(
						chr1->getFitness(), 
						chr2->getFitness(), 
						(ngn::Real)1.0e-6
					);
				
				if (!haveEqualFitnesses) {
					setGenerationForLocalMaximumTest(gen + getRestartThreshold());

					return false;
				} else {
					gen -= 1;
				}
			}

			setGenerationForLocalMaximumTest(
					getCurrentGenerationNumber() + getRestartThreshold());

			return true;
		} else {
			return false;
		}
	}

	bool Solver::isStopped() const {
		return stopped;
	}

	bool Solver::isVerbose() const {
		return verbose;
	}

	Population Solver::nextGeneration() {
		Population children;

		while (children.size() < getInitialPopulationSize()) {
			SharedPtrChromosome parent1 = selectParent();
			SharedPtrChromosome parent2 = selectParent();
			SharedPtrChromosome child1 = parent1->copy();
			SharedPtrChromosome child2 = parent2->copy();
			child1->crossOver(*child2, getCrossOverRate());
			child1->mutate(getMutationRate());
			child2->mutate(getMutationRate());
			children.add(child1);
			children.add(child2);
		}

		return children;
	}

	int Solver::numberOfBestFits() const {
		return bestFitByGeneration.size();
	}

	int Solver::populationSize() const {
		return population.size();
	}

	void Solver::resetSelector() {
		selector->setPopulation(population);
	}

	void Solver::restart() {
		clearPopulation();
		setPopulation(reserve.toArrayList());
	}

	void Solver::retainFractionOfPopulation() {
		if (getSelectionRate() < 1.0) {
			int nChrs = (int) (getInitialPopulationSize() * getSelectionRate());
			Solver::PtrToArrayOfChromosomePtr nBestFit;
			nBestFit = getNBestFitFromPopulation(nChrs);
			setPopulation(nBestFit);
			
			if (isVerbose()) {
				std::cout << "nChrs = " << nChrs << "\n";
			
				for (int unsigned i = 0; i < nBestFit->size(); ++i) {
					std::cout << i << ": fitness = " << nBestFit->operator[](i)->getFitness() << "\n";
				}
			}
		} else {
			if (isVerbose()) {
				std::cout << "selection rate >= 1.0. All chromosomes are selected for reproduction\n";
			}
		}
	}

	
	void Solver::run() {
		while (getCurrentGenerationNumber() < getMaximumNumberOfGenerations()
				&& !isStopped()) {

			if (isVerbose()) {
				if (getCurrentGenerationNumber() % 200 == 0) {
					std::cout << "###Thread-" << name
							<< "...generation-" << getCurrentGenerationNumber()
							<< "...bestFit = " << bestFit
							<< "...best_fitness = " << bestFitness()
							<< "...average_fitness = " << currentAverageFitness()
							<< "...reserve size = " << reserve.getNumberOfChromosomes()
							<< "\n";
				}
			}

			if (isLocalMinimum()) {
				if (isVerbose()) {
					std::cout << "@@@Thread-" << name
							<< "...generation-" << getCurrentGenerationNumber()
							<< "...RESTARTING"
							<< "...bestFit = " << bestFit
							<< "...average_fitness = " << currentAverageFitness()
							<< "...reserve size = " << sizeOfReserve()
							<< "\n";
				}
				restart();
			}

			sortPopulation();
			computeAverageFitness();
			updateBestFit();
			addToBestFitByGeneration(getBestFit());
			addNBestFitToReserve();

			if (hasSolution()) {
				std::cout << "Thread " << name << "\tgeneration " << getCurrentGenerationNumber() << ":\n";
				std::cout << "#-!!!!!-#SOLUTION = " << getBestFit() << "\n";
				return;
			}

			retainFractionOfPopulation();
			resetSelector();
			Population nextGen = nextGeneration();

			if (isVerbose()) {
				if (nextGen.size() < getInitialPopulationSize()) {
					std::cout << "----------Population size has decreased !!!\n";
				}
			}

			setNextGeneration(nextGen);
			computeFitnesses();
			incrementCurrentGeneration();
		}
	}

	void Solver::operator()() {
		run();
	}
	
	void Solver::setBestFit(SharedPtrChromosome const & chr) {
		bestFit = chr;
	}

	void Solver::setPopulation(Population const & chrs) {
		this->population = chrs;
	}

	SharedPtrChromosome Solver::selectParent() {
		return getSelector()->select();
	}

	void Solver::setGenerationForLocalMaximumTest(int value) {
		generationForLocalMaximumTest = value;
	}

	void Solver::setNextGeneration(Population const & children) {
		this->population = children;
	}

	void Solver::setSelector(SelectorSmartPtr const & selector) {
		this->selector = selector;
	}

	void Solver::setStopped(bool stopped) {
		this->stopped = stopped;
	}

	void Solver::setVerbose(bool isVerbose) {
		this->verbose = isVerbose;
	}

	void Solver::shufflePopulation() {
		population.shuffle();
	}

	int Solver::sizeOfReserve() const {
		return reserve.getNumberOfChromosomes();
	}

	void Solver::sortPopulation() {
		population.sortInDescendingOrder();
	}

	void Solver::stop() {
		this->stopped = true;
	}

	
	std::ostream & Solver::print(std::ostream & out) const {
		out << "Solver{\n";
		//out << "\npopulation =\n" << population;
		out << ", \nmaxGenerations=\n" << maximumNumberOfGenerations;
		out << ", \ncrossOverRate=\n" << crossOverRate;
		out << ", \nmutationRate=\n" << mutationRate;
		//out << ", \nbestFit=\n" << *bestFit;
		//out << ", \nselector=\n" << *selector;
		out << "\n}";
		
		return out;
	}

	void Solver::updateBestFit() {
		if (getBestFit() != 0) {
			for (int i = 0; i < populationSize(); ++i) {
				SharedPtrChromosome chr = population.get(i);
				
				if (chr->getFitness() > getBestFit()->getFitness()) {
					setBestFit(chr);
				}
			}
		} else {
			if (!population.isEmpty()) {
				setBestFit(population.first());
			} else {
				throw UnsupportedOperationException("Population is empty!!!");
			}
		}
	}
	
	void Solver::test() {
		
	}
}