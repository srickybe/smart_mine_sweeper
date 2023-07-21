#ifndef BRAIN_H
#define BRAIN_H

#include <iosfwd>
#include <memory>
#include "Chromosome.h"
#include "NeuralNetwork.h"
#include "Real.h"

namespace smrtsw {
	
	class Brain: public ai::NeuralNetwork, public ai::Chromosome {
	public:
		Brain();
		Brain(NeuralNetwork const & neuralNetwork, int collectedMines);
		Brain(Brain const & brain);
		
		bool equals(Chromosome const & chr) const;
		ngn::Real getMaximumWeightVariation() const;
		int getNumberOfCollectedMines() const;
		void incrementNumberOfCollectedMines(int numberOfMines);
		void computeFitness();
		ai::SharedPtrChromosome copy() const;
		bool crossOver(Chromosome & chr, ngn::Real crossOverRate);
		ngn::Real getFitness() const;
		bool isSolution() const;
		bool mutate(ngn::Real mutationRate);
		void print(std::ostream & out) const;
		void setNumberOfCollectedMines(int numberOfCollectedMines);
		void setMaximumWeightVariation(ngn::Real maximumWeightVariation);
		static void test();
		
	private:
		ngn::Real fitness;
		int numberOfCollectedMines;
		ngn::Real maximumWeightVariation;
	};

	typedef std::shared_ptr<Brain> SharedPtrBrain;
	std::ostream & operator <<(std::ostream & out, Brain const & brain);
}

#endif // BRAIN_H