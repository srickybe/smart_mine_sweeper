#include "Gudermann.h"
#include <iostream>
#include "Math.h"
#include "Vector.h"

namespace ngn {
	
	Gudermann::Gudermann() {

	}

	Real Gudermann::evaluate(Real x) const {
		return (4.0 / Math<Real>::PI * Math<Real>::atan(x) - 1.0);
	}

	Vector Gudermann::evaluate(Vector const & x) const {
		Vector res(x.length());
		
		for (int i = 0; i < res.length(); ++i) {
			res.setElem(i, evaluate(x.getElem(i)));
		}
		
		return res;
	}
	
	std::ostream & Gudermann::print(std::ostream & out) const {
		out << "Gudermann{}";
		
		return out;
	}
}