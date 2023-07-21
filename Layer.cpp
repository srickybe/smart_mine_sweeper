#include "Layer.h"
#include <iostream>
#include "Function.h"
#include "UnsupportedOperationException.h"

namespace ai {
	
	Layer::Layer() 
	: weights_(),
	biases_(),
	activationFunctions_()
	{
		std::cout << "Layer default constructor\n";
	}

	Layer::Layer(
		ngn::Matrix const & weights, 
		ngn::Vector const & biases, 
		std::shared_ptr<std::vector<ngn::SharedPtrFunction>> const & functions
	) 
	: weights_(weights),
	biases_(biases),
	activationFunctions_(functions)
	{
	}

	Layer::Layer(Layer const & layer) 
	: weights_(layer.weights_),
	biases_(layer.biases_),
	activationFunctions_(layer.activationFunctions_)
	{
	}

	void Layer::copyActivationFunctions(
		std::shared_ptr<std::vector<ngn::SharedPtrFunction>> const & functions
	) 
	{
		this->activationFunctions_ = functions;
	}
	
	bool Layer::equals(Layer const & rhs) const {
		return getWeights().equals(rhs.getWeights(), (ngn::Real)1.0e-6) &&
				getBiases().equals(rhs.getBiases(), (ngn::Real)1.0e-6); 
	}
	
	ngn::SharedPtrFunction const & Layer::getActivationFunction(int i) const {
		return activationFunctions_->operator[](i);
	}

	ngn::Vector const & Layer::getBiases() const {
		return biases_;
	}

	ngn::Real Layer::getWeight(int i, int j) const {
		return weights_.getElem(i, j);
	}

	ngn::Matrix const & Layer::getWeights() const {
		return weights_;
	}

	int Layer::numberOfActivationFunctions() const {
		return activationFunctions_->size();
	}

	int Layer::numberOfInputs() const {
		return weights_.getNCols();
	}

	int Layer::numberOfOutPuts() const {
		return weights_.getNRows();
	}

	ngn::Vector Layer::output(ngn::Vector const & input) const {
		
		if (input.hasNaNElement()) {
			throw UnsupportedOperationException("INPUT HAS A NAN COMPONENT");
		}
		
		/*std::cout << "getWeights() =\n" << getWeights() << "\n";
		std::cout << "inputs =\n" << input << "\n";*/
		
		ngn::Vector tmp_res = getWeights().mult(input);
		tmp_res = tmp_res.sub(getBiases());

		if (numberOfActivationFunctions() == 1) {
			ngn::SharedPtrFunction function = getActivationFunction(0);
			
			if (function == nullptr) {
				throw UnsupportedOperationException("ACTIVATION FUNCTION POINTER IS NULL!");
			}
			
			ngn::Vector res = function->evaluate(tmp_res);
			
			if (res.hasNaNElement()) {
				throw UnsupportedOperationException("OUTPUT HAS A NAN COMPONENT");
			}
			
			return res;
		} else {
			ngn::Vector res(tmp_res.length());

			for (int i = 0; i < res.length(); ++i) {
				ngn::SharedPtrFunction function = getActivationFunction(i);
				
				if (function == nullptr) {
					throw UnsupportedOperationException("ACTIVATION FUNCTION POINTER IS NULL!");
				}
			
				ngn::Real value = function->evaluate(tmp_res.getElem(i));
				res.setElem(i, value);
			}
			
			if (res.hasNaNElement()) {
				throw UnsupportedOperationException("OUTPUT HAS A NAN COMPONENT");
			}
			return res;
		}
	}

	void Layer::print(std::ostream & out) const {
		out << "Layer{\n";
		out << "weights =\n" << getWeights() << "\n";
		out << ", biases =\n" << getBiases() << "\n";
		out << ", activation functions =\n";
		
		for (int i = 0; i < numberOfActivationFunctions(); ++i) {
			out << i << ":\t" << *(getActivationFunction(i)) << "\n";
		}
		
		out << "}";
	}
	
	void Layer::setBiasAtRowWithValue(int row, ngn::Real value) {
		biases_.setElem(row, value);
	}
	
	void Layer::setWeightAtRowAtColumnWithValue(int i, int j, ngn::Real val) {
		weights_.setElem(i, j, val);
	}
	
	std::ostream & operator<<(std::ostream & out, Layer const & layer) {
		/*out << "weights =\n" << layer.getWeights() << "\n";
		out << "biases =\n" << layer.getBiases() << "\n";
		out << "activation functions =\n";
		
		for (int i = 0; i < layer.numberOfActivationFunctions(); ++i) {
			out << i << ":\t" << *(layer.getActivationFunction(i)) << "\n";
		}*/
		layer.print(out);
		return out;
	}
}