#ifndef LAYER_H
#define LAYER_H

#include <iosfwd>
#include <memory>
#include "Function.h"
#include "Matrix.h"
#include "Vector.h"

namespace ai {
	
	class Layer {
	public:
		Layer();
		Layer(
			ngn::Matrix const & weights, 
			ngn::Vector const & biases, 
			std::shared_ptr<std::vector<ngn::SharedPtrFunction>> const & functions
		);
		Layer(Layer const & layer);
		
		bool equals(Layer const & rhs) const;
		ngn::SharedPtrFunction const & getActivationFunction(int i) const;
		ngn::Vector const & getBiases() const;
		ngn::Real getWeight(int i, int j) const;
		ngn::Matrix const & getWeights() const;
		int numberOfActivationFunctions() const;
		int numberOfInputs() const;
		int numberOfOutPuts() const;
		ngn::Vector output(ngn::Vector const & input) const;
		void print(std::ostream & out) const;
		void setBiasAtRowWithValue(int row, ngn::Real value);
		void setWeightAtRowAtColumnWithValue(int i, int j, ngn::Real val);
		
	private:
		ngn::Matrix weights_;
		ngn::Vector biases_;
		std::shared_ptr<std::vector<ngn::SharedPtrFunction>> activationFunctions_;
		
		void copyActivationFunctions(
			std::shared_ptr<std::vector<ngn::SharedPtrFunction>> const & functions
		);
	};
	
	
    std::ostream & operator<<(std::ostream & out, Layer const & layer);
}
	
#endif // LAYER_H