#include "IsSharedPtrSmartMineSweeper.h"
#include <memory>
#include "SmartMineSweeper.h"

namespace smrtsw {
	
	IsSharedPtrSmartMineSweeper::IsSharedPtrSmartMineSweeper() {
		
	}
	
	bool IsSharedPtrSmartMineSweeper::test(ngn::SharedPtrPhysicObject3D const & objectPtr) const {
		return std::dynamic_pointer_cast<SmartMineSweeper>(objectPtr) != nullptr;
	}
}