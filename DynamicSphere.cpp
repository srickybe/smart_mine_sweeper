#include "DynamicSphere.h"

namespace ngn {
	
	DynamicSphere::DynamicSphere(Vector3D const & center, Real radius, Vector3D const & linVel) :
		Sphere(center, radius),
		linVel_(linVel)
	{
		
	}
	
	Vector3D const & DynamicSphere::getLinearVelocity() const {
		return linVel_;
	}
	
	DynamicIntersection::Result DynamicSphere::intersectDynamicPlane(DynamicPlane const & plane) const {
		DynamicIntersection::Result result = DynamicIntersection::planeIntersectSphere(plane, *this);
		
		return result;
	}
	
	DynamicIntersection::Result DynamicSphere::intersectDynamicSphere(DynamicSphere const & sphere) const {
		DynamicIntersection::Result result = DynamicIntersection::sphereIntersectSphere(*this, sphere);
		
		return result;
	}
}