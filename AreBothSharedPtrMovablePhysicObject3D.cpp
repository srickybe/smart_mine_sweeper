#include "AreBothSharedPtrMovablePhysicObject3D.h"
#include <memory>

namespace smrtsw {

	AreBothSharedPtrMovablePhysicObject3D::AreBothSharedPtrMovablePhysicObject3D() {
		
	}
	
	bool AreBothSharedPtrMovablePhysicObject3D::test(ngn::PairOfSharedPtrPhysicObject3D const & objectPairPtr) const {
		return objectPairPtr.first->isMovable() && objectPairPtr.second->isMovable();
	}
}