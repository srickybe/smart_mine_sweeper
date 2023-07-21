#ifndef SIGMOID_H
#define SIGMOID_H

#include <iosfwd>
#include "Function.h"
#include "Real.h"


namespace ngn {
	
	class Vector;
	
	class Sigmoid: public Function {
	public:
		Sigmoid(Real param);

		Real evaluate(Real x) const;
		Vector evaluate(Vector const & x) const;
		std::ostream & print(std::ostream & out) const;
		static void test();
		
	private:
		Real p;
	};
	
	
	std::ostream & operator<<(std::ostream & out, Sigmoid const & sigmoid);
}

#endif // SIGMOID_H