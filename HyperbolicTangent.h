#ifndef HYPERBOLIC_TANGENT_H
#define HYPERBOLIC_TANGENT_H

#include <iosfwd>
#include "Function.h"
#include "Real.h"

namespace ngn {
	
	class Vector;
	class HyperbolicTangent: public Function {
		
	public:
		HyperbolicTangent();
		
		Real evaluate(Real x) const;
		Vector evaluate(Vector const & x) const;
		std::ostream & print(std::ostream & out) const;
	};
	
	std::ostream & operator <<(std::ostream & out, HyperbolicTangent const & ht);
}

#endif // HYPERBOLIC_TANGENT_H