#ifndef AXIS_ALIGNED_BOX_H
#define AXIS_ALIGNED_BOX_H

#include "Intersectable.h"
#include "Matrix3D.h"
#include "Vector3D.h"

namespace ngn {
	class Sphere;

	class AxisAlignedBox3D: public Intersectable { 
	public:
		static AxisAlignedBox3D fromMinMax(Vector3D const & min, Vector3D const & max);
		
		AxisAlignedBox3D();
		AxisAlignedBox3D(Vector3D const & center, Vector3D const & halfExtents);
		Vector3D const & getCenter() const;
		Vector3D const & getHalfExtents() const;
		
		Vector3D const & getPosition() const;
		void setPosition(Vector3D const & position);
		Matrix3D const & getOrientation() const;
		void setOrientation(Matrix3D const & orientation);
		Intersection::Result intersectIntersectable(Intersectable const & intersectable) const;
		Intersection::Result intersectAxisAlignedBox3D(AxisAlignedBox3D const & box) const;
		Intersection::Result intersectLineSegment(LineSegment const & lineSegment) const;
		Intersection::Result intersectOrientedBox3D(OrientedBox3D const & box) const;
		Intersection::Result intersectPlane(Plane const & plane) const;
		Intersection::Result intersectSphere(Sphere const & sphere) const;
		void print(std::ostream & out) const;
		
	private:
		Vector3D center_;
		Vector3D halfExtents_;
		static Matrix3D const orientation_;
		
		static bool validMinMax(Vector3D const & min, Vector3D const & max);
	};
}

#endif // AXIS_ALIGNED_BOX_H