#include "NeuralNetwork.h"
#include <iostream>
#include "Function.h"
#include "Math.h"
#include "Matrix.h"
#include "Vector.h"

namespace ai {
	
	NeuralNetwork::NeuralNetwork() 
	: layers_(),
	weightRange_()
	{
	}

	NeuralNetwork::NeuralNetwork(ngn::Range const & weightRange)
	: layers_(),
	weightRange_(weightRange)
	{
	}

	NeuralNetwork::NeuralNetwork(NeuralNetwork const & rhs) 
	: layers_()
	{
		for (int i = 0; i < rhs.numberOflayers(); ++i) {
			addLayer(rhs.getLayer(i));
		}

		setweightRange(rhs.getweightRange());
	}

	NeuralNetwork NeuralNetwork::nullWeights(
		int nInputs,
		std::vector<int> const & nNeuronsByLayer,
		ngn::Range const & weightRange,
		std::vector<std::shared_ptr<std::vector<ngn::SharedPtrFunction>>> const & functions
	)
	{
		NeuralNetwork res(weightRange);
		ngn::Matrix weights = 
			ngn::Matrix::zero(
				nNeuronsByLayer[0],
				nInputs
			);
		ngn::Vector biases = ngn::Vector::zero(nNeuronsByLayer[0]);
		Layer layer(
			weights,
			biases,
			functions.operator [](0)
		);
		res.addLayer(layer);

		for (int unsigned i = 1; i < nNeuronsByLayer.size(); ++i) {
			weights = ngn::Matrix::zero(
					nNeuronsByLayer[i],
					nNeuronsByLayer[i - 1]
			);
			biases = ngn::Vector::zero(nNeuronsByLayer[i]);
			layer = Layer(
				weights,
				biases,
				functions.operator [](i)
			);
			res.addLayer(layer);
		}

		return res;
	}
		
	NeuralNetwork NeuralNetwork::random(
			int nInputs,
			std::vector<int> const & nNeuronsByLayer,
			ngn::Range const & weightRange,
			std::vector<std::shared_ptr<std::vector<ngn::SharedPtrFunction>>> const & functions
	) {
		NeuralNetwork res(weightRange);
		ngn::Matrix weights = ngn::Matrix::random(
				nNeuronsByLayer[0],
				nInputs,
				weightRange);
		ngn::Vector biases = ngn::Vector::random(nNeuronsByLayer[0], weightRange);
		Layer layer(
			weights,
			biases,
			functions.operator [](0)
		);
		res.addLayer(layer);

		for (int unsigned i = 1; i < nNeuronsByLayer.size(); ++i) {
			weights = ngn::Matrix::random(
					nNeuronsByLayer[i],
					nNeuronsByLayer[i - 1],
					weightRange
			);
			biases = ngn::Vector::random(nNeuronsByLayer[i], weightRange);
			layer = Layer(
				weights,
				biases,
				functions.operator [](i)
			);
			res.addLayer(layer);
		}

		return res;
	}

	bool NeuralNetwork::equals(NeuralNetwork const & rhs) const {
		if (numberOflayers() == rhs.numberOflayers()) {
			for (int i = 0; i < numberOflayers(); ++i) {
				if (!getLayer(i).equals(rhs.getLayer(i))) {
					return false;
				}
			}
			
			return true;
		} else {
			return false;
		}
	}
	
	Layer const & NeuralNetwork::getLayer(int i) const {
		return layers_[i];
	}

	ngn::Range const & NeuralNetwork::getweightRange() const {
		return weightRange_;
	}

	void NeuralNetwork::setBiasAtRowInLayerWithValue(int row, int iLayer, ngn::Real value) {
		layers_.operator [](iLayer).setBiasAtRowWithValue(row, value);
	}
	
	void NeuralNetwork::setLayer(int i, Layer const & layer) {
		layers_.operator[](i) = layer;
	}

	void NeuralNetwork::setWeightAtRowAtColumnInLayerWithValue(
		int row, 
		int column, 
		int iLayer, 
		ngn::Real value
	) 
	{
		layers_.operator [](iLayer).setWeightAtRowAtColumnWithValue(row, column, value);
	}
	
	void NeuralNetwork::setweightRange(ngn::Range const & weightRange) {
		this->weightRange_ = weightRange;
	}
	
	void NeuralNetwork::addLayer(Layer const & layer) /*throws IllegalArgumentException*/ {
		layers_.push_back(layer);
	}

	ngn::Real NeuralNetwork::maximumWeight() const {
		return weightRange_.getMax();
	}

	ngn::Real NeuralNetwork::minimumWeight() const {
		return weightRange_.getMin();
	}

	int NeuralNetwork::numberOflayers() const {
		return layers_.size();
	}

	ngn::Vector NeuralNetwork::output(ngn::Vector const & input) const {
		ngn::Vector res = input;

		for (int i = 0; i < numberOflayers(); ++i) {
			//std::cout << "£££££layer" << i << "\n";
			ngn::Vector tmp_res = getLayer(i).output(res);
			res = tmp_res;
		}

		return res;
	}

	void NeuralNetwork::print(std::ostream & out) const {
		out << "NeuralNetwork{";
		
		for (int unsigned i = 0; i < layers_.size(); ++i) {
			out << "layer_" << i << " = ";
			layers_.operator [](i).print(out);
		}
		
		out << "}";
	}
	
	ngn::Real NeuralNetwork::weightInterval() const {
		return weightRange_.interval();
	}

	void NeuralNetwork::test() {
		ngn::Matrix matrix1(4, 3);
		matrix1.setElem(0, 0, 0.374182);
		matrix1.setElem(0, 1, 0.512688);
		matrix1.setElem(0, 2, 0.972949);
		matrix1.setElem(1, 0, 0.516321);
		matrix1.setElem(1, 1, 0.294556);
		matrix1.setElem(1, 2, 0.700643);
		matrix1.setElem(2, 0, 0.916293);
		matrix1.setElem(2, 1, 0.141639);
		matrix1.setElem(2, 2, 0.519504);
		matrix1.setElem(3, 0, 0.530974);
		matrix1.setElem(3, 1, 0.390093);
		matrix1.setElem(3, 2, 0.017157);

		std::cout << "matrix1 =\n" << matrix1 << std::endl;

		ngn::Vector biases1(4);
		biases1.setElem(0, 0.4246);
		biases1.setElem(1, 0.9219);
		biases1.setElem(2, 0.4961);
		biases1.setElem(3, 0.7299);

		std::cout << "biases1 =\n" << biases1 << std::endl;

		std::shared_ptr<std::vector<ngn::SharedPtrFunction>> functions;

		class MyFunction: public ngn::Function {
		public:
			MyFunction() {
				
			}
			
			ngn::Real getParam() const {
				return param;
			}
			
			ngn::Real evaluate(ngn::Real x) const {
				return 1.0 / (1.0 + ngn::Math<ngn::Real>::exp(-x / param));
			}
			
			ngn::Vector evaluate(ngn::Vector const & x) const {
				ngn::Vector res(x.length());

				for (int i = 0; i < x.length(); ++i) {
					res.setElem(i, this->evaluate(x.getElem(i)));
				}

				return res;
			}
			
			std::ostream & print(std::ostream & out) const {
				out << "MyFunction{param = " << param << "}\n";

				return out;
			}
			
		private:
			ngn::Real const param = ngn::Math<ngn::Real>::E;
		};

		ngn::SharedPtrFunction function(new MyFunction());
		functions->push_back(function);
		functions->push_back(function);
		functions->push_back(function);
		functions->push_back(function);
		std::cout << "*****1\n";

		Layer layer1(matrix1, biases1, functions);
		std::cout << "layer1 =\n" << layer1 << "\n";

		ngn::Vector inputs(3);
		inputs.setElem(0, 0.7061);
		inputs.setElem(1, 0.3858);
		inputs.setElem(2, 0.4453);

		ngn::Matrix matrix2(2, 4);
		matrix2.setElem(0, 0, 0.495229);
		matrix2.setElem(0, 1, 0.426617);
		matrix2.setElem(0, 2, 0.183168);
		matrix2.setElem(0, 3, 0.479958);
		matrix2.setElem(1, 0, 0.403384);
		matrix2.setElem(1, 1, 0.096612);
		matrix2.setElem(1, 2, 0.827144);
		matrix2.setElem(1, 3, 0.378100);
		std::cout << "$$$$$2\n";
		std::cout << "matrix2 =\n" << matrix2 << std::endl;

		ngn::Vector biases2(2);
		biases2.setElem(0, 0.91087);
		biases2.setElem(1, 0.2085);
		std::cout << "biases2 =\n" << biases2 << std::endl;

		std::shared_ptr<std::vector<ngn::SharedPtrFunction>> functions2;
		functions2->push_back(function);
		functions2->push_back(function);

		std::cout << "#####3\n";
		
		Layer layer2(matrix2, biases2, functions2);
		std::cout << "layer2 =\n" << layer2 << "\n";
		ngn::Range weightRange(-1.0, 1.0);
		NeuralNetwork cnn(weightRange);
		cnn.addLayer(layer1);
		cnn.addLayer(layer2);

		ngn::Vector res = cnn.output(inputs);

		std::cout << "res = " << res << std::endl;
		//std::cout << "cnn=\n" << cnn << std::endl;
	}
}