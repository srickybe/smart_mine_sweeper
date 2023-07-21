#ifndef IS_SHARED_PTR_MINE_H
#define IS_SHARED_PTR_MINE_H

#include "PhysicObject3D.h"
#include "PredicateOfSharedPtrPhysicObject3D.h"
#include "SharedPtrPhysicObject3D.h"

namespace smrtsw {
	
	class IsSharedPtrMine: public ngn::PredicateOfSharedPtrPhysicObject3D {
	public: 
		IsSharedPtrMine();
		
		bool test(ngn::SharedPtrPhysicObject3D const & objectPtr) const;
	};
}

#endif // IS_SHARED_PTR_MINE_H