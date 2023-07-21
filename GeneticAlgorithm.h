#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <chrono>
#include <ctime>
#include <set>
#include <thread>
#include <vector>
#include "Chromosome.h"
#include "Population.h"
#include "Real.h"
#include "Settings.h"
#include "Solver.h"

using namespace ngn;

namespace ai {
	
	class GeneticAlgorithm {
	private:
		std::vector<Population> populations;
		Settings settings;
		std::vector<SharedPtrSolver> solvers;
		std::vector<std::thread> threads;
		SharedPtrChromosome fittest;
		Real bestFitness;
		std::chrono::time_point<std::chrono::system_clock> startTime;
		bool verbose;

	public:
		GeneticAlgorithm(
			std::vector<Population> const & populationsParam, 
			Settings const & settingsParam
		);
		
		Population const & getPopulation(int i) const;
		SharedPtrSolver const & getSolver(int i) const;
		void initializeSolvers();
		void initializeThreads();
		bool isVerbose() const;
		int numberOfThreads()const;
		void solve();
		void printMessage1() const;
		void printMessage2() const;
		void printMessage3() const;
		void startThreads();
		void setVerbose(bool isVerbose);
		std::set<int> initializeIndexesOfRunningSolvers() const;
		Real elapsedTime() const;
		Real getBestFitness() const;
		SharedPtrChromosome getFittest() const;
		std::vector<Population> const & getPopulations() const;
		static void test();
	};
}

#endif // GENETIC_ALGORITHM_H