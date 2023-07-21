#ifndef DYNAMIC_INTERSECTABLE_H
#define DYNAMIC_INTERSECTABLE_H

#include "DynamicIntersection.h"

namespace ngn {
	
	class DynamicPlane;
	class DynamicSphere;
	
    class DynamicIntersectable {
	public:
		virtual 
		DynamicIntersection::Result 
		intersectDynamicIntersectable(DynamicIntersectable const & object) const = 0;

		virtual 
		DynamicIntersection::Result 
		intersectDynamicPlane(DynamicPlane const & plane) const = 0;

		virtual 
		DynamicIntersection::Result 
		intersectDynamicSphere(DynamicSphere const & sphere) const = 0;
	};
}

#endif // DYNAMIC_INTERSECTABLE_H