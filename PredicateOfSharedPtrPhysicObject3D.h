#ifndef PREDICATE_OF_SHARED_PTR_PHYSIC_OBJECT_3D_H
#define PREDICATE_OF_SHARED_PTR_PHYSIC_OBJECT_3D_H

#include "SharedPtrPhysicObject3D.h"

namespace ngn {
	
	class PredicateOfSharedPtrPhysicObject3D {
	public:
		virtual bool test(SharedPtrPhysicObject3D const & objectPtr) const = 0;
	};	
}

#endif // PREDICATE_OF_SHARED_PTR_PHYSIC_OBJECT_3D_H