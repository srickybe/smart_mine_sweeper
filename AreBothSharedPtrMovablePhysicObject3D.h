#ifndef ARE_BOTH_SHARED_PTR_MOVABLE_PHYSIC_OBJECT_3D_H
#define ARE_BOTH_SHARED_PTR_MOVABLE_PHYSIC_OBJECT_3D_H

#include "PhysicObject3D.h"
#include "PredicateOfPairOfSharedPtrPhysicObject3D.h"

namespace smrtsw {
	
	class AreBothSharedPtrMovablePhysicObject3D: public ngn::PredicateOfPairOfSharedPtrPhysicObject3D {
	public:
		AreBothSharedPtrMovablePhysicObject3D();
		
		bool test(ngn::PairOfSharedPtrPhysicObject3D const & objectPairPtr) const;
	};
}

#endif // ARE_BOTH_SHARED_PTR_MOVABLE_PHYSIC_OBJECT_3D_H