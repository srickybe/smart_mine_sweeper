#ifndef DEFAULT_ACTIVATION_FUNCTION_H
#define DEFAULT_ACTIVATION_FUNCTION_H

#include <iosfwd>
#include "Function.h"
#include "Real.h"
#include "Sigmoid.h"

namespace ai {
	
	class Vector;
	
	class DefaultActivationFunction: public ngn::Function {
		
	public:
		DefaultActivationFunction();

		ngn::Real evaluate(ngn::Real x) const;
		ngn::Vector evaluate(ngn::Vector const & x) const;
		std::ostream & print(std::ostream & out) const;
		
	private:
		ngn::Real p;
		ngn::Sigmoid sigmoid;
	};
	
	std::ostream & operator<<(std::ostream & out, DefaultActivationFunction const & function);
}

#endif // DEFAULT_ACTIVATION_FUNCTION_H