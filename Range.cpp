#include "Range.h"
#include "IllegalArgumentException.h"

namespace ngn {
	
	Range::Range() 
	: min(0),
	max(0)
	{
	}
	
	Range::Range(Real min, Real max) {
		if (min < max) {
			this->min = min;
			this->max = max;
		} else {
			throw IllegalArgumentException(std::to_string(min).append("is not inferior to ").append(std::to_string(max)));
		}
	}

	Range::Range(Range const & rhs) {
		this->min = rhs.min;
		this->max = rhs.max;
	}
	
	Real Range::getMin() const {
		return min;
	}

	Real Range::getMax() const {
		return max;
	}

	Real Range::interval() const {
		return max - min;
	}
}