#include "IsSharedPtrPhysicObject3D.h"
#include <memory>

namespace ngn {
	
	IsSharedPtrPhysicObject3D::IsSharedPtrPhysicObject3D() {
		
	}
	
	bool IsSharedPtrPhysicObject3D::test(ngn::SharedPtrPhysicObject3D const & objectPtr) const {
		return objectPtr != nullptr;
	}
}