#ifndef GUDERMANN_H
#define GUDERMANN_H

#include <iosfwd>
#include "Function.h"
#include "Real.h"

namespace ngn {
	
	class Vector;
	
	class Gudermann: public Function {

	public:
		Gudermann();

		Real evaluate(Real x) const;
		Vector evaluate(Vector const & x) const;
		std::ostream & print(std::ostream & out) const;
	};
}

#endif // GUDERMANN_H