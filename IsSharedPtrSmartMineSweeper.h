#ifndef IS_SHARED_PTR_SMART_MINE_SWEEPER_H
#define IS_SHARED_PTR_SMART_MINE_SWEEPER_H

#include "PredicateOfSharedPtrPhysicObject3D.h"
#include "SharedPtrPhysicObject3D.h"

namespace smrtsw {
	
	class IsSharedPtrSmartMineSweeper: public ngn::PredicateOfSharedPtrPhysicObject3D {
	public: 
		IsSharedPtrSmartMineSweeper();
		
		bool test(ngn::SharedPtrPhysicObject3D const & objectPtr) const;
	};
}

#endif // IS_SHARED_PTR_SMART_MINE_SWEEPER_H