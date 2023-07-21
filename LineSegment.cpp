#include "LineSegment.h"
#include <iostream>
#include "UnsupportedOperationException.h"

namespace ngn {
	
	LineSegment::LineSegment() :
		origin_(Vector3D::zero()),
		direction_(Vector3D::x_axis()),
		length_(1.0)
	{
		
	}
	
	LineSegment::LineSegment(Vector3D const & origin, Vector3D const & direction, Real length) :
		origin_(origin),
		direction_(direction),
		length_(length)
	{
		
	}
	
	Vector3D const & LineSegment::getOrigin() const {
		return origin_;
	}
	
	Vector3D const & LineSegment::getDirection() const {
		return direction_;
	}
	
	Real LineSegment::getLength() const {
		return length_;
	}
	
	Vector3D const & LineSegment::getPosition() const {
		return getOrigin();
	}
	
	void LineSegment::setPosition(Vector3D const & position) {
		origin_ = position;
	}
	
	Matrix3D const & LineSegment::getOrientation() const {
		throw UnsupportedOperationException("");
	}
	
	void LineSegment::setOrientation(Matrix3D const & orientation) {
		throw UnsupportedOperationException("");
	}
	
	Intersection::Result LineSegment::intersectIntersectable(Intersectable const & intersectable) const {
		return intersectable.intersectLineSegment(*this);
	}
	
	Intersection::Result LineSegment::intersectAxisAlignedBox3D(AxisAlignedBox3D const & box) const {
		throw UnsupportedOperationException("");
	}
	
	Intersection::Result LineSegment::intersectLineSegment(LineSegment const & lineSegment) const {
		throw UnsupportedOperationException("");
	}
	
	Intersection::Result LineSegment::intersectOrientedBox3D(OrientedBox3D const & box) const {
		throw UnsupportedOperationException("");
	}
	
	Intersection::Result LineSegment::intersectPlane(Plane const & plane) const {
		throw UnsupportedOperationException("");
	}
	
	Intersection::Result LineSegment::intersectSphere(Sphere const & sphere) const {
		return Intersection::lineSegmentIntersectSphere(*this, sphere);
	}
	
	void LineSegment::print(std::ostream & out) const {
		
	}
}