#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include <iosfwd>
#include <memory>
#include "Intersection.h"

namespace ngn {

	class AxisAlignedBox3D;
	class Intersection;
	class LineSegment;
	class Matrix3D;
	class OrientedBox3D;
	class Plane;
	class Sphere;
	class Vector3D;

	class Intersectable {
	public:
		virtual Vector3D const & getPosition() const = 0;
		virtual void setPosition(Vector3D const & position) = 0;
		virtual Matrix3D const & getOrientation() const = 0;
		virtual void setOrientation(Matrix3D const & orientation) = 0;
		virtual Intersection::Result intersectIntersectable(Intersectable const & intersectable) const = 0;
		virtual Intersection::Result intersectAxisAlignedBox3D(AxisAlignedBox3D const & box) const = 0;
		virtual Intersection::Result intersectLineSegment(LineSegment const & lineSegment) const = 0;
		virtual Intersection::Result intersectOrientedBox3D(OrientedBox3D const & box) const = 0;
		virtual Intersection::Result intersectPlane(Plane const & plane) const = 0;
		virtual Intersection::Result intersectSphere(Sphere const & sphere) const = 0;
		virtual void print(std::ostream & out) const = 0;
	};
	
	typedef std::shared_ptr<Intersectable> SharedPtrIntersectable;
	std::ostream & operator << (std::ostream & out, Intersectable const & intersectable);
}

#endif // INTERSECTABLE_H