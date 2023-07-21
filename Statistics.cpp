#include "Statistics.h"
#include <iostream>

namespace smrtsw {
	
	Statistics::Statistics(
		Real bestFitness,
		Real averageFitness,
		Real fitnessStandardDeviation,
		Real pourcentageOfMinelessSweepers,
		int totalnumberOfCollectedMines,
		std::shared_ptr<int> const & bestSweeperID
	) {
		this->bestFitness = bestFitness;
		this->averageFitness = averageFitness;
		this->fitnessStandardDeviation = fitnessStandardDeviation;
		this->pourcentageOfMinelessSweepers = pourcentageOfMinelessSweepers;
		this->totalNumberOfCollectedMines = totalnumberOfCollectedMines;
		this->bestSweeperID = bestSweeperID;
	}

	Real Statistics::getBestFitness() const {
		return bestFitness;
	}

	Real Statistics::getAverageFitness() const {
		return averageFitness;
	}

	Real Statistics::getFitnessStandardDeviation() const {
		return fitnessStandardDeviation;
	}

	Real Statistics::getPourcentageOfMinelessSweepers() const {
		return pourcentageOfMinelessSweepers;
	}

	int Statistics::getTotalNumberOfCollectedMines() const {
		return totalNumberOfCollectedMines;
	}

	std::shared_ptr<int> Statistics::getBestSweeperID() const {
		return bestSweeperID;
	}


	void Statistics::print(std::ostream & out) const {
		out << "Statistics{"
			<< "\nbestFitness=" << bestFitness
			<< ", \naverageFitness=" << averageFitness
			<< ", \nfitnessStandardDeviation=" << fitnessStandardDeviation
			<< ", \npourcentageOfMinelessSweepers=" << pourcentageOfMinelessSweepers
			<< ", \ntotalNumberOfCollectedMines=" << totalNumberOfCollectedMines
			<< ", \nbestSweeperID=" << (bestSweeperID != nullptr ? std::to_string(*bestSweeperID): "nullptr")
			<< "\n}";
	}
	
	std::ostream & operator<<(std::ostream & out, Statistics const & stats) {
		stats.print(out);
		
		return out;
	}
}