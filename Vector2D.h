#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iosfwd>
#include <memory>
#include "Math.h"
#include "Real.h"

namespace ngn
{
    
    class Vector2D {

        private:
            static Real const EPS;
            Real coords[2];

		public:
            static Vector2D add(Vector2D const & lhs, Vector2D const & rhs);
            static Real cross(Vector2D const & lhs, Vector2D const & rhs);
			static Vector2D componentProduct(Vector2D const & lhs, Vector2D const & rhs);
            static Vector2D cross(Real lhs, Vector2D const & rhs);
            static Vector2D cross(Vector2D const & lhs, Real rhs);
			static Real distance(Vector2D const & lhs, Vector2D const & rhs);
			static Real distanceSquared(Vector2D const & lhs, Vector2D const & rhs);
            static Vector2D div(Vector2D const & lhs, Real rhs);
            static Vector2D mult(Vector2D const & lhs, Real rhs);
            static Vector2D negate(Vector2D const & rhs);
            static Vector2D norm(Vector2D const & rhs);
            static Vector2D sub(Vector2D const & lhs, Vector2D const & rhs);
            static Vector2D zero();
            static Vector2D x_axis();
            static Vector2D y_axis();
            static Vector2D star(Real angularVelocity, Vector2D const & rhs);
            
            Vector2D();
            Vector2D(Real x, Real y);
            Vector2D(Vector2D const & vec);
            
            bool equals(Vector2D const & rhs, Real eps) const;
            
            Real getX() const;
            Real getY() const;
            void setX(Real val);
            void setY(Real val);
            
            Vector2D & add(Vector2D const & rhs);
			Real angle() const;
            Real angle(Vector2D const & rhs) const;
            Real cosAngle(Vector2D const & rhs) const;
            Real cross(Vector2D const & rhs) const;
            Vector2D & div(Real rhs);
            Real dot(Vector2D const & rhs) const;
            Real get(int i) const;
			bool isColinear(Vector2D const & rhs, Real tol) const;
            Real length() const;
            Real lengthSquared() const;
            Vector2D & negate();
            Vector2D & norm();
            Vector2D & mult(Real rhs);
			Real const * constantPointerToCoordinates() const;
            Vector2D & sub(Vector2D const & rhs);
            
            bool isUnit() const;
    };

	std::ostream & operator<<(std::ostream & out, Vector2D const & vec);
	typedef std::shared_ptr<Vector2D> Vector2DSmartPtr;
//////////////////////////////////////////////////////////////////////////////////////////

}

#endif // VECTOR2D_H