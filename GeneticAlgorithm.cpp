#include "GeneticAlgorithm.h"
#include <iostream>
#include <thread>
#include "IllegalArgumentException.h"

namespace ai {
	
	GeneticAlgorithm::GeneticAlgorithm(std::vector<Population> const & populationsParam, Settings const & settingsParam) :
		populations(populationsParam),
		settings(settingsParam),
		solvers(),
		threads()
	{
		this->fittest = nullptr;
		this->bestFitness = 0;
		this->startTime = std::chrono::system_clock::now();
		this->verbose = settingsParam.isVerbose();
		this->initializeSolvers();
		this->initializeThreads();
	}

	Population const & GeneticAlgorithm::getPopulation(int i) const {
		if (i < static_cast<int>(populations.size())) {
			return populations.operator[](i);
		} else {
			std::string message = "INDEX I = ";
			message += std::to_string(i);
			message += " OUT OF BOUNDS(POPULATION SIZE = ";
			message += std::to_string(populations.size());
			
			throw IllegalArgumentException(message);
		}
	}
	
	SharedPtrSolver const & GeneticAlgorithm::getSolver(int i) const {
		return solvers.operator[](i);
	}
	
	void GeneticAlgorithm::initializeSolvers() {
		for (int i = 0; i < numberOfThreads(); ++i) {
			/*std::cout << "thread_" << i << "\n";
			std::cout << "this->settings.getSelector(i) = " << *(this->settings.getSelector(i)) << "\n";*/
			std::string solverName = std::to_string(i);
			SharedPtrSolver solver(
				new Solver(
					this->getPopulation(i),
					this->settings.getSelector(i),
					this->settings,
					solverName
				)
			);
			
			solver->setVerbose(settings.isVerbose());
			//std::cout << "OK##\n";
			solvers.push_back(solver);
		}
	}

	void GeneticAlgorithm::initializeThreads() {
		for (int i = 0; i < numberOfThreads(); ++i) {
			threads.emplace_back(&Solver::run, getSolver(i));
		}
	}

	bool GeneticAlgorithm::isVerbose() const {
		return verbose;
	}
	
	int GeneticAlgorithm::numberOfThreads() const {
		return this->settings.getNumberOfThreads();
	}
	
	void GeneticAlgorithm::solve() {
		std::set<int> indexesOfRunningSolvers
				= initializeIndexesOfRunningSolvers();
		startThreads();
		bool on = true && numberOfThreads() > 0;

		while (on) {
			for (int i = 0; i < numberOfThreads() && on; ++i) {
				if (getSolver(i)->hasSolution()) {
					fittest = getSolver(i)->getBestFit();
					
					if (isVerbose()) {
						printMessage1();
					}
					
					on = false;
				} else if (getSolver(i)->hasEnded()) {
					indexesOfRunningSolvers.erase(i);

					if (indexesOfRunningSolvers.empty()) {
						if (isVerbose()) {
							printMessage2();
						}
						
						on = false;
					}
				} else {
					std::cout << "getSolver(i)->hasSolution() == false && getSolver(i)->hasEnded() == false\n";
					SharedPtrChromosome candidate = getSolver(i)->getBestFit();

					if (candidate != nullptr && candidate->getFitness() > bestFitness) {
						fittest = candidate;
						bestFitness = candidate->getFitness();
						
						if (isVerbose()) {
							printMessage3();
						}
					}
				}
			}
		}
	}

	void GeneticAlgorithm::printMessage1() const {
		std::cout << "solution =\n" << fittest << "\n";
	}

	void GeneticAlgorithm::printMessage2() const {
		std::cout << "***All populations have reached" << " the maximum number of generations" << "\n";
		std::cout << "***fittest = " << fittest << "\n";
		std::cout << "***bestFitness = " << bestFitness << "\n";
	}

	void GeneticAlgorithm::printMessage3() const {
		std::cout << "best fitness = " << bestFitness << "\n";
		std::cout << "best solution =\n" << fittest << "\n";
		std::cout << "The program has been running for " << elapsedTime() << " secs" << "\n";
	}

	void GeneticAlgorithm::startThreads() {
		for (int unsigned i = 0; i < threads.size()/*numberOfThreads()*/; ++i) {
			threads.operator[](i).join();
		}
	}

	void GeneticAlgorithm::setVerbose(bool isVerbose) {
		this->verbose = isVerbose;
	}
	
	std::set<int> GeneticAlgorithm::initializeIndexesOfRunningSolvers() const {
		std::set<int> indexesOfSolversStillRunning;

		for (int i = 0; i < numberOfThreads(); ++i) {
			indexesOfSolversStillRunning.insert(i);
		}

		return indexesOfSolversStillRunning;
	}

	Real GeneticAlgorithm::elapsedTime() const {
		std::chrono::duration<double> res = std::chrono::system_clock::now() - startTime;

		return static_cast<Real>(res.count());
	}

	Real GeneticAlgorithm::getBestFitness() const {
		return bestFitness;
	}

	SharedPtrChromosome GeneticAlgorithm::getFittest() const {
		return fittest;
	}

	std::vector<Population> const & GeneticAlgorithm::getPopulations() const {
		return populations;
	}
	
	void GeneticAlgorithm::test() {

	}
}