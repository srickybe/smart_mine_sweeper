#ifndef SETTINGS_H
#define SETTINGS_H

#include <iosfwd>
#include <string>
#include <vector>
#include "Real.h"
#include "Selector.h"

namespace ai {
	
	class Settings {
	public:
		Settings();
		
		Settings(std::string const & pathName);
		
		Settings(Settings const & settings);

		void readVerbose(std::ifstream & file);
		
		void readNumberOfThreads(std::ifstream & file);
		
		void readRandomSeed(std::ifstream & file);
		
		void readPopulationSize(std::ifstream & file);
		
		void readCriticalSizeOfReserve(std::ifstream & file);
		
		void readMaximumNumberOfGenerations(std::ifstream & file);
		
		void readRestartThreshold(std::ifstream & file);
		
		void readCrossOverRate(std::ifstream & file);
		
		void readMutationRate(std::ifstream & file);
		
		void readSelectionRate(std::ifstream & file);
		
		void readSelectorTypes(std::ifstream & file);
		
		int getNumberOfThreads() const;

		long getSeed() const;

		std::string getSolverSettingsPath() const;

		int getPopulationSize() const;

		int getMaximumNumberOfGenerations() const;

		int getRestartThreshold() const;

		ngn::Real getCrossOverRate() const;

		ngn::Real getMutationRate() const;

		ngn::Real getSelectionRate() const;
		
		SelectorSmartPtr const & getSelector(int i) const;
		
		int numberOfSelectors() const;

		/*Selector getSelector(int i) {
			return this->selectors.get(i);
		}*/

		int getCriticalSizeOfReserve() const;

		bool isVerbose() const;
		
		void print(std::ostream & out) const;

		static void test();
		
	private:
		std::string solverSettingsPath;
		bool verbose;
		int numberOfThreads;
		long seed;
		int populationSize;
		int criticalSizeOfReserve;
		int maximumNumberOfGenerations;
		int restartThreshold;
		ngn::Real crossOverRate;
		ngn::Real mutationRate;
		ngn::Real selectionRate;
		std::vector<std::string> selectorTypes;
		std::vector<std::vector<std::string>> selectorParameters;
		std::vector<SelectorSmartPtr> selectors;
	};
	
	std::ostream & operator<<(std::ostream & out, Settings const & settings);
}

#endif // SETTINGS_H