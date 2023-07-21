#include "IsSharedPtrMine.h"
#include <memory>
#include "Mine.h"

namespace smrtsw {
	
	IsSharedPtrMine::IsSharedPtrMine() {
		
	}
	
	bool IsSharedPtrMine::test(ngn::SharedPtrPhysicObject3D const & objectPtr) const {
		return std::dynamic_pointer_cast<Mine>(objectPtr) != nullptr;
	}
}