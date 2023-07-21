#ifndef PAIR_OF_SHARED_PTR_PHYSIC_OBJECT3D_H
#define PAIR_OF_SHARED_PTR_PHYSIC_OBJECT3D_H

#include <utility>
#include "SharedPtrPhysicObject3D.h"

namespace ngn {
	typedef std::pair<SharedPtrPhysicObject3D, SharedPtrPhysicObject3D> PairOfSharedPtrPhysicObject3D;
}

#endif // PAIR_OF_SHARED_PTR_PHYSIC_OBJECT3D_H