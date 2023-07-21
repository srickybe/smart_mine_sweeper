#include "CompareTestChromo.h"
#include "TestChromo.h"

namespace ai {
	
	CompareTestChromo::CompareTestChromo() {
	}
	
	bool CompareTestChromo::operator() (const TestChromo & lhs, const TestChromo & rhs) const
	{
		for (int unsigned i = 0; i < lhs.numberOfCoefficients(); ++i) {
			if (lhs.getCoefficient(i) < rhs.getCoefficient(i)) {
				return true;
			}
		}
		
		return false;
	}	
}

