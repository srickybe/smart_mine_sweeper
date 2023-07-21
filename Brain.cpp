#include "Brain.h"
#include <iostream>
#include "Math.h"
#include "Rand.h"
#include "Sigmoid.h"

namespace smrtsw {
	
	Brain::Brain() : 
		NeuralNetwork(),
		fitness(0),
		numberOfCollectedMines(0),
		maximumWeightVariation(0)
	{
	}
	
	Brain::Brain(NeuralNetwork const & neuralNetwork, int collectedMines) :
		NeuralNetwork(neuralNetwork),
		fitness(collectedMines),
		numberOfCollectedMines(collectedMines),
		maximumWeightVariation(0.05 * NeuralNetwork::weightInterval())
	{
	}

	Brain::Brain(Brain const & brain) :
		NeuralNetwork(brain),
		fitness(brain.getNumberOfCollectedMines()),
		numberOfCollectedMines(brain.getNumberOfCollectedMines()),
		maximumWeightVariation(brain.getMaximumWeightVariation())
	{

	}

	
	bool Brain::equals(Chromosome const & chr) const {
		if (this == &chr) {
			return true;
		}

		Brain const * other = dynamic_cast<Brain const*>(&chr);
		
		return NeuralNetwork::equals(*(dynamic_cast<NeuralNetwork const*>(other)))
					&& getNumberOfCollectedMines()
					== other->getNumberOfCollectedMines();
	}

	ngn::Real Brain::getMaximumWeightVariation() const {
		return maximumWeightVariation;
	}

	int Brain::getNumberOfCollectedMines() const {
		return numberOfCollectedMines;
	}

	void Brain::incrementNumberOfCollectedMines(int numberOfMines) {
		setNumberOfCollectedMines(getNumberOfCollectedMines() + numberOfMines);
	}

	
	void Brain::computeFitness() {
		fitness = getNumberOfCollectedMines();//1.0e4 / (1 + getNumberOfCollectedMines());
	}

	
	ai::SharedPtrChromosome Brain::copy() const {
		return ai::SharedPtrChromosome(new Brain(*this));
	}

	
	bool Brain::crossOver(Chromosome & chr, ngn::Real crossOverRate) {
		if (util::Rand<ngn::Real>::getInstance().next() < crossOverRate) {
			int randomLayerIndex = util::Rand<int>::getInstance().next(this->numberOflayers());
			int randomNeuronIndex = util::Rand<int>::getInstance().next(this->getLayer(randomLayerIndex).numberOfOutPuts());
			NeuralNetwork const * other = dynamic_cast<NeuralNetwork const *>(&chr);
			ai::Layer layer = this->getLayer(randomLayerIndex);
			ai::Layer otherLayer = other->getLayer(randomLayerIndex);

			for (int i = 0; i < layer.numberOfInputs(); ++i) {
				ngn::Real tmp = layer.getWeight(randomNeuronIndex, i);
				layer.setWeightAtRowAtColumnWithValue(randomNeuronIndex, i, otherLayer.getWeight(randomNeuronIndex, i));
				otherLayer.setWeightAtRowAtColumnWithValue(randomNeuronIndex, i, tmp);
			}

			return true;
		} else {
			return false;
		}
	}

	
	ngn::Real Brain::getFitness() const {
		return fitness;
	}

	
	bool Brain::isSolution() const {
		return false;
	}

	
	bool Brain::mutate(ngn::Real mutationRate) {
		bool mutated = false;

		for (int i = 0; i < this->numberOflayers(); ++i) {
			ai::Layer layer = this->getLayer(i);

			for (int j = 0; j < layer.numberOfOutPuts(); ++j) { //number of neurons
				for (int k = 0; k < layer.numberOfInputs(); ++k) { //number of weights in neuron j
					ngn::Real r = util::Rand<ngn::Real>::getInstance().next();

					if (r < mutationRate) {
						ngn::Real delta = util::Rand<ngn::Real>::getInstance().next() * getMaximumWeightVariation();

						while (delta == 0.0) {
							delta = util::Rand<ngn::Real>::getInstance().next() * getMaximumWeightVariation();
							std::cout << "delta == 0.0" << "\n";
							std::cout << "getMaximumWeightVariation() = " << getMaximumWeightVariation() << "\n";
							std::cout << "super.weightInterval() = " << NeuralNetwork::weightInterval() << "\n";
						}

						ngn::Real min = ngn::Math<ngn::Real>::max(layer.getWeight(j, k) - delta, NeuralNetwork::minimumWeight());
						ngn::Real max = ngn::Math<ngn::Real>::min(layer.getWeight(j, k) + delta, NeuralNetwork::maximumWeight());
						ngn::Real randomWeight = util::Rand<ngn::Real>::getInstance().next(min, max);

						layer.setWeightAtRowAtColumnWithValue(j, k, randomWeight);

						if (!mutated) {
							mutated = true;
						}
					}
				}
			}
		}

		return mutated;
	}

	void Brain::print(std::ostream & out) const {
		out << "Brain{fitness = " << fitness;
		out << ", numberOfCollectedMines = " << numberOfCollectedMines;
		out << ", maximumWeightVariation = " << maximumWeightVariation;
		out << ", neuralNetwork =\n";
		NeuralNetwork::print(out);
		out << "}";
	}
	
	void Brain::setNumberOfCollectedMines(int numberOfCollectedMines) {
		this->numberOfCollectedMines = numberOfCollectedMines;
		computeFitness();
	}

	void Brain::setMaximumWeightVariation(ngn::Real maximumWeightVariation) {
		this->maximumWeightVariation = maximumWeightVariation;
	}

	
	void Brain::test() {
		int nInputs = 4;
		std::vector<int> nNeuronsByLayer;
		nNeuronsByLayer.push_back(10);
		nNeuronsByLayer.push_back(2);
		ngn::Range weightRange(-1.0, 1.0);
		
		class StepFunction: public ngn::Function {
		public:
			
			StepFunction(ngn::Real sigmoidParam) :
				sigmoid(sigmoidParam)
			{
				
			}
			
			ngn::Real evaluate(ngn::Real x) const {
				return sigmoid.evaluate(x);
			}
			
			ngn::Vector evaluate(ngn::Vector const & x) const {
				ngn::Vector res(x.length());
				
				for (int i = 0; i < res.length(); ++i) {
					res.setElem(i, evaluate(res.getElem(i)));
				}
				
				return res;
			}

			std::ostream & print(std::ostream & out) const {
				out << "{sigmoid=" << sigmoid << '}';
				
				return out;
			}
			
		private:
			ngn::Sigmoid sigmoid;
		};
		
		std::shared_ptr<StepFunction> function = std::make_shared<StepFunction>(0.5);
		std::vector<std::shared_ptr<std::vector<std::shared_ptr<ngn::Function>>>> functions;
		functions.push_back(std::make_shared<std::vector<std::shared_ptr<ngn::Function>>>());
		
		for (int unsigned i = 0; i < nNeuronsByLayer.size(); ++i) {
			int nNeurons = nNeuronsByLayer.operator [](i);
			
			for (int j = 0; j < nNeurons; ++j) {
				functions.operator [](i)->push_back(function);
			}
		}
		
		NeuralNetwork cnn = NeuralNetwork::random(nInputs, nNeuronsByLayer, weightRange, functions);
		int numberOfCollectedMines = 0;
		Brain brain(cnn, numberOfCollectedMines);
		std::cout << "brain=\n" << brain << "\n";
		
		/*try {
			try (FileOutputStream fileOut = new FileOutputStream("/tmp/brain.ser"); ObjectOutputStream out = new ObjectOutputStream(fileOut)) {
				out.writeObject(brain);
			}
			System.out.printf("Serialized data is saved in /tmp/brain.ser");
		} catch (IOException i) {
			System.err.println("Brain SerializeDemo IOException");
			System.err.println("i.getClass() = " + i.getClass());
			System.err.println("i.getMessage() = " + i.getMessage());
		}
		
		Brain brain2 = null;
		
		try {
			try (FileInputStream fileIn = new FileInputStream("/tmp/brain.ser"); ObjectInputStream in = new ObjectInputStream(fileIn)) {
				brain2 = (Brain) in.readObject();
			}
		} catch (IOException i) {
			System.err.println("Brain DeserializeDemo IOException");
			System.err.println("i.getMessage() = " + i.getMessage());
			return;
		} catch (ClassNotFoundException c) {
			System.err.println("Brain class not found");
			return;
		}

		std::cout << "Brain Deserialized Simulation...");
		std::cout << "brain2: \n" + brain2);*/
	}
	
	std::ostream & operator <<(std::ostream & out, Brain const & brain) {
		brain.print(out);
		
		return out;
	}
}