#ifndef IS_SHARED_PTR_PHYSIC_OBJECT_3D_H
#define IS_SHARED_PTR_PHYSIC_OBJECT_3D_H

#include "PredicateOfSharedPtrPhysicObject3D.h"

namespace ngn {
	
	class IsSharedPtrPhysicObject3D: public PredicateOfSharedPtrPhysicObject3D {
	public:
		IsSharedPtrPhysicObject3D();
		
		bool test(SharedPtrPhysicObject3D const & objectPtr) const;
	};
}

#endif // IS_SHARED_PTR_PHYSIC_OBJECT_3D_H