#include "Settings.h"
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include "IllegalArgumentException.h"
#include "Rand.h"
#include "RouletteWheel.h"
#include "Tournament.h"
#include "UnsupportedOperationException.h"

namespace ai {

	Settings::Settings() {
		
	}
	
	Settings::Settings(std::string const & pathName) {
		this->solverSettingsPath = pathName;
		std::ifstream file(solverSettingsPath);
		readVerbose(file);
		readNumberOfThreads(file);
		readRandomSeed(file);
		readPopulationSize(file);
		readCriticalSizeOfReserve(file);
		readMaximumNumberOfGenerations(file);
		readRestartThreshold(file);
		readCrossOverRate(file);
		readMutationRate(file);
		readSelectionRate(file);
		readSelectorTypes(file);
	}

	Settings::Settings(Settings const & settings) :
		solverSettingsPath(settings.solverSettingsPath),
		verbose(settings.verbose),
		numberOfThreads(settings.numberOfThreads),
		seed(settings.seed),
		populationSize(settings.populationSize),
		criticalSizeOfReserve(settings.criticalSizeOfReserve),
		maximumNumberOfGenerations(settings.maximumNumberOfGenerations),
		restartThreshold(settings.restartThreshold),
		crossOverRate(settings.crossOverRate),
		mutationRate(settings.mutationRate),
		selectionRate(settings.selectionRate),
		selectorTypes(settings.selectorTypes),
		selectorParameters(settings.selectorParameters),
		selectors(settings.selectors)
	{
		
	}
	
	void Settings::readVerbose(std::ifstream & file) {
		std::string line;
		std::getline(file, line);
		boost::char_separator<char> separator{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{line, separator};
		boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin();
		
		if (it->compare("is_verbose") != 0) {
			std::string message = "first string = \"" + *it + "\" != \"is_verbose\"" ;
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
		}
		
		++it;
		
		if (it->compare("false") == 0) {
			verbose = false;
		} else {
			verbose = true;	
		}
	}
	
	void Settings::readNumberOfThreads(std::ifstream & file) {
		std::string line;
		std::getline(file, line);
		boost::char_separator<char> separator{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{line, separator};
		boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin();

		if (it->compare("number_of_threads") != 0) {
			std::string message = "first string = \"" + *it + "\" != \"number_of_threads\"" ;
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
		}
		
		++it;
		numberOfThreads = stoi(*it);			
	}
	
	void Settings::readRandomSeed(std::ifstream & file) {
		std::string line;
		std::getline(file, line);
		boost::char_separator<char> separator{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{line, separator};
		boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin();

		if (it->compare("random_seed") != 0) {
			std::string message = "first string = \"" + *it + "\" != \"random_seed\"" ;
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
		}

		++it;
		this->seed = stoi(*it);
		util::Rand<int>::getInstance().setSeed(this->seed);
		util::Rand<ngn::Real>::getInstance().setSeed(this->seed);
	}
	
	void Settings::readPopulationSize(std::ifstream & file) {
		std::string line;
		std::getline(file, line);
		boost::char_separator<char> separator{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{line, separator};
		boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin();

		if (it->compare("population_size") != 0) {
			std::string message = "first string = \"" + *it + "\" != \"population_size\"" ;
			std::cout << "message = " << message << "\n";
			++it;
			std::cout << "second string = " << *(it) << std::endl;
			throw IllegalArgumentException(message);
		}

		++it;
		populationSize = stoi(*it);			
	}
	
	void Settings::readCriticalSizeOfReserve(std::ifstream & file) {
		std::string line;
		std::getline(file, line);
		boost::char_separator<char> separator{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{line, separator};
		boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin();

		if (it->compare("critical_size_of_reserve") != 0) {
			std::string message = "first string = \"" + *it + "\" != \"critical_size_of_reserve\"" ;
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
		}

		++it;
		criticalSizeOfReserve = stoi(*it);			
	}
	
	void Settings::readMaximumNumberOfGenerations(std::ifstream & file) {
		std::string line;
		std::getline(file, line);
		boost::char_separator<char> separator{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{line, separator};
		boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin();

		if (it->compare("maximum_number_of_generations") != 0) {
			std::string message = "first string = \"" + *it + "\" != \"maximum_number_of_generations\"" ;
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
		}

		++it;
		maximumNumberOfGenerations = stoi(*it);			
	}
	
	void Settings::readRestartThreshold(std::ifstream & file) {
		std::string line;
		std::getline(file, line);
		boost::char_separator<char> separator{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{line, separator};
		boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin();

		if (it->compare("restart_threshold") != 0) {
			std::string message = "first string = \"" + *it + "\" != \"restart_threshold\"" ;
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
		}
		
		++it;
		restartThreshold = stoi(*it);			
	}
	
	void Settings::readCrossOverRate(std::ifstream & file) {
		std::string line;
		std::getline(file, line);
		boost::char_separator<char> separator{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{line, separator};
		boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin();

		if (it->compare("cross_over_rate") != 0) {
			std::string message = "first string = \"" + *it + "\" != \"cross_over_rate\"" ;
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
		}

		++it;
		crossOverRate = static_cast<ngn::Real>(stod(*it));			
	}
	
	void Settings::readMutationRate(std::ifstream & file) {
		std::string line;
		std::getline(file, line);
		boost::char_separator<char> separator{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{line, separator};
		boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin();

		if (it->compare("mutation_rate") != 0) {
			std::string message = "first string = \"" + *it + "\" != \"mutation_rate\"" ;
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
		}

		++it;
		mutationRate = static_cast<ngn::Real>(stod(*it));			
	}
	
	void Settings::readSelectionRate(std::ifstream & file) {
		std::string line;
		std::getline(file, line);
		boost::char_separator<char> separator{" "};
		boost::tokenizer<boost::char_separator<char>> tokens{line, separator};
		boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin();

		if (it->compare("selection_rate") != 0) {
			std::string message = "first string = \"" + *it + "\" != \"selection_rate\"" ;
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
		}

		++it;
		selectionRate = static_cast<ngn::Real>(stod(*it));			
	}
	
	void Settings::readSelectorTypes(std::ifstream & file) {
		for (int i = 0; i < numberOfThreads; ++i) {
			std::string line;
			std::getline(file, line);
			boost::char_separator<char> separator{" "};
			boost::tokenizer<boost::char_separator<char>> tokens{line, separator};
			boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin();

			if (it->compare("chromosome_selection") != 0) {
			std::string message = "first string = \"" + *it + "\" != \"chromosome_selection\"" ;
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
			}

			++it;
			this->selectorTypes.push_back(*it);

			if (it->compare("RouletteWheel") == 0) {
				//std::cout << "roulette_Wheel\n";
				selectorParameters.push_back(std::vector<std::string>());
				selectors.push_back(SelectorSmartPtr(new RouletteWheel()));
				//std::cout << "selectors.size() = " << selectors.size() << "\n";
			} else if(it->compare("Tournament") == 0) {
				++it;
				std::string parameter = *it;
				std::vector<std::string> parameters;
				parameters.push_back(parameter);
				selectorParameters.push_back(parameters);
				selectors.push_back(SelectorSmartPtr(new Tournament(std::stoi(parameter))));
				//std::cout << "tournament_size = " << parameter << "\n";
			} else {
				std::string message = "Chromosome Selection function not supported\n";
				std::cout << message;
				throw UnsupportedOperationException("");
			}
		}			
	}
	
	int Settings::getNumberOfThreads() const {
		return numberOfThreads;
	}

	long Settings::getSeed() const {
		return seed;
	}

	std::string Settings::getSolverSettingsPath() const {
		return solverSettingsPath;
	}

	int Settings::getPopulationSize() const {
		return populationSize;
	}

	int Settings::getMaximumNumberOfGenerations() const {
		return maximumNumberOfGenerations;
	}

	int Settings::getRestartThreshold() const {
		return restartThreshold;
	}

	ngn::Real Settings::getCrossOverRate() const {
		return crossOverRate;
	}

	ngn::Real Settings::getMutationRate() const {
		return mutationRate;
	}

	ngn::Real Settings::getSelectionRate() const {
		return selectionRate;
	}

	SelectorSmartPtr const & Settings::getSelector(int i) const {
		if (i < static_cast<int>(selectors.size())) {
			return selectors.operator[](i);
		} else {
			std::string message = "INDEX = ";
			message += std::to_string(i);
			message += " OUT OF BOUNDS (SELECTORS SIZE = ";
			message += std::to_string(selectors.size());
			std::cout << "message = " << message << "\n";
			
			throw IllegalArgumentException(message);
		}
	}
	
	int Settings::numberOfSelectors() const {
		return selectorTypes.size();
	}

	/*Selector getSelector(int i) {
		return this->selectors.get(i);
	}*/

	int Settings::getCriticalSizeOfReserve() const {
		return criticalSizeOfReserve;
	}

	bool Settings::isVerbose() const {
		return verbose;
	}

	
	void Settings::print(std::ostream & out) const {
		out << "Settings{"
			<< ",\nsolverSettingsPath=" << solverSettingsPath
			<< ",\nverbose=" << (verbose ? "true": "false")
			<< ",\nnumberOfThreads=" << numberOfThreads
			<< ",\nseed=" << seed
			<< ",\npopulationSize=" << populationSize
			<< ",\ncriticalSizeOfReserve=" << criticalSizeOfReserve
			<< ",\nmaximumNumberOfGenerations=" << maximumNumberOfGenerations
			<< ",\nrestartThreshold=" << restartThreshold
			<< ",\ncrossOverRate=" << crossOverRate
			<< ",\nmutationRate=" << mutationRate
			<< ",\nselectionRate=" << selectionRate
			//<< ",\nselectionTypes=" << selectorTypes
			<< "}";
	}

	void Settings::test() {
		std::string pathName = "/home/john/NetBeansProjects/SmartMineSweepers/src/smartminesweepers/solver_settings.txt";
		std::cout << "pathName = " << pathName << "\n";
		Settings settings(pathName);
		std::cout << "settings =\n" << settings << "\n";
	}

	std::ostream & operator<<(std::ostream & out, Settings const & settings) {
		settings.print(out);
		
		return out;
	}
}