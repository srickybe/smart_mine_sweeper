#ifndef SOLVER_H
#define SOLVER_H


#include <iosfwd>
#include <memory>
#include <string>
#include "Population.h"
#include "Real.h"
#include "Reserve.h"
#include "Selector.h"



namespace ai {
	
	class Settings;
	
	class Solver {
	public:
		typedef std::vector<SharedPtrChromosome> ArrayOfChromosomePtr;
		typedef std::shared_ptr<ArrayOfChromosomePtr> PtrToArrayOfChromosomePtr;
		void (Solver::*function)();
	
		Solver(
			Population const & chrs,
			SelectorSmartPtr const & selector,
			Settings const & settings,
			std::string const & name
		);
		/*explicit Solver();
		Solver(Solver const & rhs);*/

		bool addNBestFitFromPopulationToReserve(int nChrs);
		void addNBestFitToReserve();
		void addToAverageFitnessByGeneration(ngn::Real averageFitness);
		
		template <class InputIterator>
		void addToReserve(InputIterator const & beg, InputIterator const & end);
		
		void addToBestFitByGeneration(SharedPtrChromosome const & chr);
		void clearPopulation();
		ngn::Real bestFitness() const;
		void clearReserve();
		void computeAverageFitness();
		void computeFitnesses();
		ngn::Real currentAverageFitness() const;
		SharedPtrChromosome const & getBestFit() const;
		SharedPtrChromosome const & getBestFitOfGeneration(int generation) const;
		int getCriticalSizeOfReserve() const;
		ngn::Real getCrossOverRate() const;
		ngn::Real getCurrentAverageFitness() const;
		int getCurrentGenerationNumber() const;
		int getInitialPopulationSize() const;
		int getGenerationForLocalMaximumTest() const;
		int getMaximumNumberOfGenerations() const;
		ngn::Real getMutationRate() const;
		PtrToArrayOfChromosomePtr getNBestFitFromPopulation(int nChrs) const;
		PtrToArrayOfChromosomePtr getNBestFitFromReserve(int nChrs) const;
		Population const & getPopulation() const;
		int getRestartThreshold() const;
		ngn::Real getSelectionRate() const;
		SelectorSmartPtr const & getSelector() const;
		bool hasEnded() const;
		bool hasSolution() const;
		void incrementCurrentGeneration();
		bool isLocalMinimum();
		bool isStopped() const;
		bool isVerbose() const;
		Population nextGeneration();
		int numberOfBestFits() const;
		int populationSize() const;
		void resetSelector();
		void restart();
		void retainFractionOfPopulation();
		void run();
		void operator()();
		void setBestFit(SharedPtrChromosome const & chr);
		void setPopulation(Population const & chrs);
		SharedPtrChromosome selectParent();
		void setGenerationForLocalMaximumTest(int value);
		void setNextGeneration(Population const & children);
		void setSelector(SelectorSmartPtr const & selector);
		void setStopped(bool stopped);
		void setVerbose(bool isVerbose);
		void shufflePopulation();
		int sizeOfReserve() const;
		void sortPopulation();
		void stop();
		std::ostream & print(std::ostream & out) const;
		void updateBestFit();
		static void test();
		
	private:
		Population population;
		int initialPopulationSize;
		int criticalSizeOfReserve;
		int maximumNumberOfGenerations;
		ngn::Real crossOverRate;
		ngn::Real mutationRate;
		ngn::Real selectionRate;
		int restartThreshold;
		SharedPtrChromosome bestFit;
		ArrayOfChromosomePtr bestFitByGeneration;
		std::vector<ngn::Real> averageFitnessByGeneration;
		Reserve reserve;
		SelectorSmartPtr selector;
		std::string name;
		int currentGenerationNumber;
		int generationForLocalMaximumTest;
		bool stopped;
		bool verbose;
		
		/*Solver();
		Solver(Solver const & rhs);*/
	};
	
	typedef std::shared_ptr<Solver> SharedPtrSolver;
};

#endif // SOLVER_H