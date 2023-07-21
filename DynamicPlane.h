#ifndef DYNAMIC_PLANE_H
#define DYNAMIC_PLANE_H

#include "DynamicIntersectable.h"
#include "DynamicIntersection.h"
#include "Plane.h"
#include "Real.h"


namespace ngn {
	
	class DynamicSphere;
	class Vector3D;
	
	class DynamicPlane: public Plane, public DynamicIntersectable {
	public:
		DynamicPlane(Vector3D const & normal, Real distance, Vector3D const & linVel);
		
		Vector3D const & getLinearVelocity() const;	
		DynamicIntersection::Result intersectDynamicPlane(DynamicPlane const & plane) const;
		DynamicIntersection::Result intersectDynamicSphere(DynamicSphere const & sphere) const;

	private:
		Vector3D linVel_;
	};
}

#endif // DYNAMIC_PLANE_H