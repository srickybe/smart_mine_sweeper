#include "IsMovableNonMovablePair.h"

namespace smrtsw {
	
	IsMovableNonMovablePair::IsMovableNonMovablePair() {
		
	}
	
	bool IsMovableNonMovablePair::test(ngn::PairOfSharedPtrPhysicObject3D const & objectPairPtr) const {
		bool test1 = objectPairPtr.first->isMovable();
		bool test2 = objectPairPtr.second->isMovable();
		
		//return (test1 && !test2) || (!test1 && test2);
		return test1 != test2;
	}
}