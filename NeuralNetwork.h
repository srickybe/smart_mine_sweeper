#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <iosfwd>
#include <vector>
#include "Layer.h"
#include "Range.h"
#include "Real.h"

namespace ai {
	
	class NeuralNetwork {
		
	public:
		NeuralNetwork();
		NeuralNetwork(ngn::Range const & weightRange);
		NeuralNetwork(NeuralNetwork const & rhs);

		static
		NeuralNetwork nullWeights(
			int nInputs,
			std::vector<int> const & nNeuronsByLayer,
			ngn::Range const & weightRange,
			std::vector<std::shared_ptr<std::vector<ngn::SharedPtrFunction>>> const & functions
		);
		
		static 
		NeuralNetwork random(
			int nInputs,
			std::vector<int> const & nNeuronsByLayer,
			ngn::Range const & weightRange,
			std::vector<std::shared_ptr<std::vector<ngn::SharedPtrFunction>>> const & functions
		);
		 
		bool equals(NeuralNetwork const & rhs) const;
		Layer const & getLayer(int i) const;
		ngn::Range const & getweightRange() const;
		void setBiasAtRowInLayerWithValue(int row, int iLayer, ngn::Real value);
		void setLayer(int i, Layer const & layer);
		void setWeightAtRowAtColumnInLayerWithValue(int row, int column, int iLayer, ngn::Real value);
		void setweightRange(ngn::Range const & weightRange);
		void addLayer(Layer const & layer);
		ngn::Real maximumWeight() const;
		ngn::Real minimumWeight() const;
		int numberOflayers() const;
		ngn::Vector output(ngn::Vector const & input) const;
		void print(std::ostream & out) const;
		ngn::Real weightInterval() const;
		static void test();
		
	private:
		std::vector<Layer> layers_;
		ngn::Range weightRange_;
	};
}

#endif // NEURAL_NETWORK_H