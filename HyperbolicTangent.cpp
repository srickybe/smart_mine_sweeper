#include "HyperbolicTangent.h"
#include <iostream>
#include "Math.h"
#include "Vector.h"

namespace ngn {

	HyperbolicTangent::HyperbolicTangent() {
		
	}
	
	Real HyperbolicTangent::evaluate(Real x) const {
		Real exp2x = Math<Real>::exp(2 * x);
		
		return (exp2x - 1) / (exp2x + 1);
	}

	Vector HyperbolicTangent::evaluate(Vector const & x) const {
		Vector res(x.length());
		
		for (int i = 0; i < res.length(); ++i) {
			res.setElem(i, evaluate(x.getElem(i)));
		}
		
		return res;
	}
	
	std::ostream & HyperbolicTangent::print(std::ostream & out) const {
		out << "HyperbolicTangent\n";
		
		return out;
	}
	
	std::ostream & operator <<(std::ostream & out, HyperbolicTangent const & ht) {
		ht.print(out);
		
		return out;
	}
}