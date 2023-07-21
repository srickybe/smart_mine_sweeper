#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iosfwd>
#include <memory>
#include "Real.h"

namespace ngn {
	
	class Matrix3D;
	
	class Vector3D {
	public:
        static Vector3D const x_axis();
        static Vector3D const y_axis();
        static Vector3D const z_axis();
        static Vector3D const zero();

		static Vector3D abs(Vector3D const & vec);
        static Vector3D add(Vector3D const & lhs, Vector3D const & rhs);
        static Vector3D cross(Vector3D const & lhs, Vector3D const & rhs);
		static Real distanceFrom(Vector3D const & lhs, Vector3D const & rhs);
        static Vector3D div(Vector3D const & lhs, Real rhs);
        static Vector3D mult(Vector3D const & lhs, Real rhs);
        static Vector3D mult(Real lhs, Vector3D const & rhs);
        static Vector3D negate(Vector3D const & rhs);
        static Vector3D norm(Vector3D const & rhs);
		static Real squaredDistanceFrom(Vector3D const & lhs, Vector3D const & rhs);
        static Vector3D sub(Vector3D const & lhs, Vector3D const & rhs);
        static Matrix3D tensorProduct(Vector3D const & lhs, Vector3D const & rhs);

        Vector3D();
        Vector3D(Real x, Real y, Real z);
        Vector3D(Vector3D const & vec);

        Real const * constantPointerToCoordinates() const;
        Real getX() const;
        Real getY() const;
        Real getZ() const;

        void setX(Real val);
        void setY(Real val);
        void setZ(Real val);

		Vector3D & abs();
        Vector3D & add(Vector3D const & rhs);
		Vector3D componentProduct(Vector3D const & rhs) const;
        Vector3D cross(Vector3D const & rhs) const;
		Real distanceFrom(Vector3D const & rhs) const;
		Real squaredDistanceFrom(Vector3D const & rhs) const;
        Real dot(Vector3D const & rhs) const;
        Vector3D & div(Real rhs);
        bool equalsWithTol(Vector3D const & rhs, Real eps)const;
        Real get(int i) const;
        bool isColinear(Vector3D const & rhs, Real tol) const;
        bool isUnit(Real tol) const;
        Real length() const;
        Real lengthSquared() const;
        Vector3D & negate();
        Vector3D & norm();
        Vector3D & mult(Real rhs);
        void set(int i, Real val);
        Vector3D & sub(Vector3D const & rhs);
        Matrix3D tensorProduct(Vector3D const & rhs) const;
        Matrix3D star(Matrix3D const & rhs) const;
		
	private:
		Real coords[3];
	};

	std::ostream & operator<<(std::ostream & out, Vector3D const & vec);
	typedef std::shared_ptr<Vector3D> SharedPtrVector3D;
}

#endif // VECTOR3D_H