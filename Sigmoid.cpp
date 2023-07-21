#include "Sigmoid.h"
#include <iostream>
#include "Math.h"
#include "Vector.h"

namespace ngn {
	
	Sigmoid::Sigmoid(Real param) 
	: p(param)
	{
	}

	Real Sigmoid::evaluate(Real x) const {
		return 1.0 / (1.0 + Math<Real>::exp(-x / p));
	}

	Vector Sigmoid::evaluate(Vector const & x) const {
		Vector res(x.length());

		for (int i = 0; i < res.length(); ++i) {
			res.setElem(i, evaluate(x.getElem(i)));
		}

		return res;
	}

	std::ostream & Sigmoid::print(std::ostream & out) const {
		out << "Sigmoid{" << "p=" << p << "}";
		
		return out;
	}

	void Sigmoid::test() {
		Sigmoid s(1.0);
		std::cout << "s(0.0) = " << (Real)(s.evaluate(0.0)) << "\n";
	}
	
	std::ostream & operator<<(std::ostream & out, Sigmoid const & sigmoid) {
		return sigmoid.print(out);
	}
}