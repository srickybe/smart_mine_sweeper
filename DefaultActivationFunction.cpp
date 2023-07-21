#include "DefaultActivationFunction.h"
#include <iostream>
#include "Vector.h"

namespace ai {
	
	DefaultActivationFunction::DefaultActivationFunction() 
	: p((ngn::Real)0.1),
	sigmoid((ngn::Real)0.1)
	{
	}

	ngn::Real DefaultActivationFunction::evaluate(ngn::Real x) const {
		return 0.5 - sigmoid.evaluate(x);
	}

	
	ngn::Vector DefaultActivationFunction::evaluate(ngn::Vector const & x) const {
		ngn::Vector res(x.length());

		for (int i = 0; i < x.length(); ++i) {
			res.setElem(i, evaluate(x.getElem(i)));
		}

		return res;
	}
	
	std::ostream & DefaultActivationFunction::print(std::ostream & out) const {
		out << "DefaultActivationFunction{}";
		
		return out;
	}
}