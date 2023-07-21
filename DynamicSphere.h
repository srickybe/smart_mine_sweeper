#ifndef DYNAMIC_SPHERE_H
#define DYNAMIC_SPHERE_H

#include "DynamicIntersectable.h"
#include "DynamicIntersection.h"
#include "Sphere.h"

namespace ngn {
	
	class DynamicSphere: public Sphere, public DynamicIntersectable {
	public:
		DynamicSphere(Vector3D const & center, Real radius, Vector3D const & linVel);
		
		Vector3D const & getLinearVelocity() const;
		DynamicIntersection::Result intersectDynamicPlane(DynamicPlane const & plane) const;
		DynamicIntersection::Result intersectDynamicSphere(DynamicSphere const & sphere) const;
		
	private:
		Vector3D linVel_;
	};
}

#endif // DYNAMIC_SPHERE_H