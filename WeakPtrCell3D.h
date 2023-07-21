#ifndef WEAK_PTR_CELL3D
#define WEAK_PTR_CELL3D

#include <memory>

namespace ngn {
	
	class Cell3D;
	
	typedef std::weak_ptr<Cell3D> WeakPtrCell3D;
}

#endif // WEAK_PTR_CELL3D