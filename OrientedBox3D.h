#ifndef ORIENTED_BOX_3D_H
#define ORIENTED_BOX_3D_H

#include <vector>
#include "Intersection.h"
#include "Intersectable.h"
#include "Matrix3D.h"
#include "Vector3D.h"

namespace ngn {

    
    class OrientedBox3D: public Intersectable {
    public:
        OrientedBox3D();
        OrientedBox3D(Vector3D const & center, Matrix3D const & orientation, Vector3D const & extents);

        Vector3D const & getCenter() const;
        void setCenter(Vector3D const & center);

        Matrix3D const & getOrientation() const;
        void setOrientation(Matrix3D const & orientation);

        Vector3D const & getHalfExtents() const;
        void setHalfExtents(Vector3D const & halfExtents);

        bool contains(Vector3D const & point) const;bool equals(OrientedBox3D const & rhs, Real tol) const;
        Real volume() const;

		std::vector<Vector3D> corners() const;
		
		Vector3D const & getPosition() const;
		void setPosition(Vector3D const & position);
		Intersection::Result intersectIntersectable(Intersectable const & intersectable) const;
		Intersection::Result intersectAxisAlignedBox3D(AxisAlignedBox3D const & box) const;
		Intersection::Result intersectLineSegment(LineSegment const & lineSegment) const;
		Intersection::Result intersectOrientedBox3D(OrientedBox3D const & box) const;
		Intersection::Result intersectPlane(Plane const & plane) const;
		Intersection::Result intersectSphere(Sphere const & sphere) const;
		void print(std::ostream & out) const;

    private:
        Vector3D center_;
        Matrix3D orientation_;
        Vector3D halfExtents_;
    };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif // ORIENTED_BOX_3D_H
