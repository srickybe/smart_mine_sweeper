#ifndef LINE_SEGMENT_H
#define LINE_SEGMENT_H

#include "Intersectable.h"
#include "Vector3D.h"

namespace ngn {
	
	class LineSegment: public Intersectable {
	public:
		LineSegment();
		LineSegment(Vector3D const & origin, Vector3D const & direction, Real length);
		
		Vector3D const & getOrigin() const;
		Vector3D const & getDirection() const;
		Real getLength() const;
		
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
		Vector3D origin_;
		Vector3D direction_;
		Real length_;
	};
}

#endif // LINE_SEGMENT_H