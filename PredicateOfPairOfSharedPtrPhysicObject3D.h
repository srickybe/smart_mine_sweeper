#ifndef PREDICATE_OF_PAIR_OF_SHARED_PTR_PHYSIC_OBJECT3D_H
#define PREDICATE_OF_PAIR_OF_SHARED_PTR_PHYSIC_OBJECT3D_H

#include "PairOfSharedPtrPhysicObject3D.h"

namespace ngn {
	class PredicateOfPairOfSharedPtrPhysicObject3D {
	public:
		virtual bool test(PairOfSharedPtrPhysicObject3D const & objectPairPtr) const = 0;
	};
}

#endif // PREDICATE_OF_PAIR_OF_SHARED_PTR_PHYSIC_OBJECT3D_H