#ifndef IS_STATIC_NON_STATIC_PAIR_H
#define IS_STATIC_NON_STATIC_PAIR_H

#include "PhysicObject3D.h"
#include "PredicateOfPairOfSharedPtrPhysicObject3D.h"

namespace smrtsw {
	
	class IsMovableNonMovablePair: public ngn::PredicateOfPairOfSharedPtrPhysicObject3D {
	public:
		IsMovableNonMovablePair();
		
		bool test(ngn::PairOfSharedPtrPhysicObject3D const & objectPairPtr) const;
	};
}

#endif // IS_STATIC_NON_STATIC_PAIR_H