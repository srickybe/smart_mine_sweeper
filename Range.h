#ifndef RANGE_H
#define RANGE_H

#include "Real.h"

namespace ngn {
	
	class Range {
	public: 
		Range();
		Range(Real min, Real max);
		Range(Range const & rhs);
		
		Real getMin() const;
		Real getMax() const;
		Real interval() const;
		
	private:
		Real min;
		Real max;
	};
}

#endif // RANGE_H