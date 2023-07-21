#include "DynamicPlane.h"
#include "UnsupportedOperationException.h"

namespace ngn {
	
	DynamicPlane::DynamicPlane(Vector3D const & normal, Real distance, Vector3D const & linVel) :
		Plane(normal, distance),
		linVel_(linVel)
	{
		
	}
	
	Vector3D const & DynamicPlane::getLinearVelocity() const {
		return linVel_;
	}	
	
	DynamicIntersection::Result DynamicPlane::intersectDynamicPlane(DynamicPlane const & plane) const {
		throw UnsupportedOperationException("");
	}
	
	DynamicIntersection::Result DynamicPlane::intersectDynamicSphere(DynamicSphere const & sphere) const {
		DynamicIntersection::Result result = DynamicIntersection::planeIntersectSphere(*this, sphere);
		
		return result;
	}
}