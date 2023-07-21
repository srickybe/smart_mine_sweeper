#ifndef STATISTICS_H
#define STATISTICS_H

#include <iosfwd>
#include <memory>
#include "Real.h"

using namespace ngn;

namespace smrtsw {
	
	class Statistics {
	private:
		Real bestFitness;
		Real averageFitness;
		Real fitnessStandardDeviation;
		Real pourcentageOfMinelessSweepers;
		int totalNumberOfCollectedMines;
		std::shared_ptr<int> bestSweeperID;

	public:
		Statistics(
			Real bestFitness,
			Real averageFitness,
			Real fitnessStandardDeviation,
			Real pourcentageOfMinelessSweepers,
			int totalnumberOfCollectedMines,
			std::shared_ptr<int> const & bestSweeperID
		);
		Real getBestFitness() const;
		Real getAverageFitness() const;
		Real getFitnessStandardDeviation() const;
		Real getPourcentageOfMinelessSweepers() const;
		int getTotalNumberOfCollectedMines() const;
		std::shared_ptr<int> getBestSweeperID() const;
		void print(std::ostream & out) const;
	};
	
	std::ostream & operator<<(std::ostream & out, Statistics const & stats);
}

#endif // STATISTICS_H