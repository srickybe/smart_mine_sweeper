#ifndef CELL3D_SHARED_PTR_H
#define CELL3D_SHARED_PTR_H

#include <memory>

namespace ngn {
	
	class Cell3D;
	
	typedef std::shared_ptr<Cell3D> SharedPtrCell3D;
}

#endif // CELL3D_SHARED_PTR_H