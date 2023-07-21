#include "AxisAlignedBox3D.h"
#include <cmath>
#include "IllegalArgumentException.h"
#include "Sphere.h"
#include "UnsupportedOperationException.h"

using namespace std;

namespace ngn {
	
	Matrix3D const AxisAlignedBox3D::orientation_ = Matrix3D::identity();
	
	AxisAlignedBox3D::AxisAlignedBox3D() :
		center_(0.0, 0.0, 0.0),
		halfExtents_(0.0, 0.0, 0.0)
	{
	   
	}

	AxisAlignedBox3D::AxisAlignedBox3D(Vector3D const & center, Vector3D const & halfExtents) :
		center_(center),
		halfExtents_(halfExtents)
	{
	   
	}
	
	AxisAlignedBox3D AxisAlignedBox3D::fromMinMax(Vector3D const & min, Vector3D const & max) {
		if (!AxisAlignedBox3D::validMinMax(min, max)) {
			throw IllegalArgumentException("min and max are not valid!");
		}
		
		Vector3D center = Vector3D::mult(0.5, Vector3D::add(max, min));
		Vector3D halfExtents = Vector3D::mult(0.5, Vector3D::sub(max, min));
		AxisAlignedBox3D result(center, halfExtents);
		
		return result;
	}
	
	Vector3D const & AxisAlignedBox3D::getCenter() const {
		return center_;
	}

	Vector3D const & AxisAlignedBox3D::getHalfExtents() const {
		return halfExtents_;
	}

	Vector3D const & AxisAlignedBox3D::getPosition() const {
		return getCenter();
	}
	
	void AxisAlignedBox3D::setPosition(Vector3D const & position) {
		center_ = position;
	}
		
	Matrix3D const & AxisAlignedBox3D::getOrientation() const {
		return orientation_;
	}
	
	void AxisAlignedBox3D::setOrientation(Matrix3D const & orientation) {
		throw UnsupportedOperationException("");
	}
		
    bool AxisAlignedBox3D::validMinMax(Vector3D const & min, Vector3D const & max) {
        for (int i = 0; i < 3; ++i) {
            if (min.get(i) > max.get(i)) {
                return false;
            }
        }

        return true;
    }
	
	Intersection::Result AxisAlignedBox3D::intersectIntersectable(Intersectable const & intersectable) const {
		return intersectable.intersectAxisAlignedBox3D(*this);
	}
	
	Intersection::Result AxisAlignedBox3D::intersectAxisAlignedBox3D(AxisAlignedBox3D const & box) const {
		throw UnsupportedOperationException("");
	}
	
	Intersection::Result AxisAlignedBox3D::intersectLineSegment(LineSegment const & lineSegment) const {
		throw UnsupportedOperationException("");
	}
	
	Intersection::Result AxisAlignedBox3D::intersectOrientedBox3D(OrientedBox3D const & box) const {
		throw UnsupportedOperationException("");
	}
	
	Intersection::Result AxisAlignedBox3D::intersectPlane(Plane const & plane) const {
		throw UnsupportedOperationException("");
	}
	
	Intersection::Result AxisAlignedBox3D::intersectSphere(Sphere const & sphere) const {
		return Intersection::axisAlignedBox3DIntersectSphere(*this, sphere);
	}
	
	void AxisAlignedBox3D::print(std::ostream & out) const {
		throw UnsupportedOperationException("");
	}
	
	/*bool AxisAlignedBox3D::intersectSphere(Sphere const & sphere) const {
		Vector3D dist = Vector3D::sub(sphere.getCenter(), getCenter());

		for (int i = 0; i < 3; ++i) {
			if (abs(dist.get(i)) > getHalfExtents().get(i) + sphere.getRadius()) {
				return false;
			}
		}

		return true;
	}*/
}
