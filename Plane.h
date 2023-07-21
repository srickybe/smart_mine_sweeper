#ifndef PLANE_H
#define PLANE_H

#include "Intersectable.h"
#include "Intersection.h"
#include "Vector3D.h"

namespace ngn {

    class Sphere;
	
    class Plane: public Intersectable {
    public:
        static Plane fromNormalAndPoint(Vector3D const & normal, Vector3D const & point);

        Plane(Vector3D const & normal, Vector3D const & point);
        Plane(Vector3D const & normal, Real distance);

        Vector3D const & getPoint() const;
        Real getDistance() const;
        Vector3D const & getNormal() const;
        Real distanceFromPoint(Vector3D const & vec) const;

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
        Vector3D normal_;
        Vector3D point_;
        Real distance_;

        bool isValidNormal(Vector3D const & normal) const;
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////

}

#endif // PLANE_H