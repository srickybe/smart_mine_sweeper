#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iosfwd>
#include <memory>
#include "Real.h"

namespace ngn {
	
	class Vector;
	
	class Function{
	public:
		virtual Real evaluate(Real x) const = 0;
		virtual Vector evaluate(Vector const & x) const = 0;
		virtual std::ostream & print(std::ostream & out) const = 0; 
	};

	std::ostream & operator << (std::ostream & out, Function const & function);
	
	typedef std::shared_ptr<Function> SharedPtrFunction;
}

#endif // FUNCTION_HPP