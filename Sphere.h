#ifndef SPHERE_H
#define SPHERE_H

#include <iosfwd>
#include "Intersectable.h"
#include "Matrix3D.h"
#include "Real.h"
#include "Vector3D.h"

namespace ngn {
	class AxisAlignedBox3D;

	class Sphere: public Intersectable {
	public:
        static Sphere fromOnePoint(Vector3D const & p0);
        static Sphere fromTwoPoints(Vector3D const & p0, Vector3D const & p1);
        static Sphere fromThreePoints(Vector3D const & p1, Vector3D const & p2, Vector3D const & p3);
        static Sphere fromFourPoints(Vector3D const & p1, Vector3D const & p2, Vector3D const & p3, Vector3D const & p4);
		
		Sphere();
		Sphere(Vector3D const & cent, Real rad);
		Vector3D const & getCenter() const;
		Real getRadius() const;
		bool contains(Vector3D const & point) const;
		bool containsWithTol(Vector3D const & point, Real tol) const;
		std::pair<bool, Real> contains2(Vector3D const & point) const;
		Real distanceBetweenSurfaces(Sphere const & rhs) const;
		bool equalsWithTol(Sphere const & rhs, Real tol) const;
		
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
		Real volume() const;
		
	private:
		Vector3D center;
		Real radius;
		Matrix3D orientation;
		
        static Sphere smallestSphereFromTwoOfThreePoints(Vector3D const & p1, Vector3D const & p2, Vector3D const & p3);
        static Sphere smallestSphereFromSomeOfFourPoints(Vector3D const & p1, Vector3D const & p2, Vector3D const & p3, Vector3D const & p4);
	};

	std::ostream & operator<<(std::ostream & out, Sphere const & sphere);
}

#endif // SPHERE_H