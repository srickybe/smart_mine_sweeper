#include "Vector2D.h"
#include <cassert>
#include <iomanip>
#include <iostream>

namespace ngn {

    Real const Vector2D::EPS = 1.0e-6;

     Vector2D Vector2D::zero() {
        return Vector2D(0.0, 0.0);
    }

     Vector2D Vector2D::x_axis() {
        return Vector2D(1.0, 0.0);
    }

     Vector2D Vector2D::y_axis() {
        return Vector2D(0.0, 1.0);
    }

     Vector2D Vector2D::star(Real angularVelocity, Vector2D const & rhs) {
        return Vector2D(-angularVelocity * rhs.getY(), angularVelocity * rhs.getX());
    }

     Vector2D::Vector2D() {
    }

     Vector2D::Vector2D(Real x, Real y) {
        coords[0] = x;
        coords[1] = y;
    }

     Vector2D::Vector2D(Vector2D const & vec) {
        coords[0] = vec.coords[0];
        coords[1] = vec.coords[1];
    }

     Real Vector2D::getX() const {
        return coords[0];
    }

     Real Vector2D::getY() const {
        return coords[1];
    }

     void Vector2D::setX(Real val) {
        coords[0] = val;
    }

     void Vector2D::setY(Real val) {
        coords[1] = val;
    }

     Vector2D & Vector2D::add(Vector2D const & rhs) {
        setX(getX() + rhs.getX());
        setY(getY() + rhs.getY());

        return *this;
    }

     Vector2D Vector2D::add(Vector2D const & lhs, Vector2D const & rhs) {
        return Vector2D(
                lhs.coords[0] + rhs.coords[0],
                lhs.coords[1] + rhs.coords[1]);
    }

	Real Vector2D::angle() const {
        return Math<Real>::atan2(this->coords[1], this->coords[0]);
    }
	
     Real Vector2D::angle(Vector2D const & rhs) const {
        /*Vevel Kahan formula*/
        /*Vector2D v1(this).norm();
        Vector2D v2(rhs).norm();
        Vector2D v3(v1).add(v2);
        Vector2D v4(v1).sub(v2);
        
        return 2 * Math<Real>::atan2(v4.length(), v3.length());*/

        return Math<Real>::atan2(this->cross(rhs), this->dot(rhs));
    }

	Vector2D Vector2D::componentProduct(Vector2D const & lhs, Vector2D const & rhs) {
		return Vector2D(lhs.getX() * rhs.getX(), lhs.getY() * rhs.getY());
	}
	
     Real Vector2D::cosAngle(Vector2D const & rhs) const {
        return this->dot(rhs) / (this->length() * rhs.length());
    }

     Real Vector2D::cross(Vector2D const & rhs) const {
        return coords[0] * rhs.coords[1] - coords[1] * rhs.coords[0];
    }

     Real Vector2D::cross(Vector2D const & lhs, Vector2D const & rhs) {
        return lhs.coords[0] * rhs.coords[1] - lhs.coords[1] * rhs.coords[0];
    }

     Vector2D Vector2D::cross(Real lhs, Vector2D const & rhs) {
        return Vector2D(
                -lhs * rhs.coords[1],
                lhs * rhs.coords[0]
        );
    }

     Vector2D Vector2D::cross(Vector2D const & lhs, Real rhs) {
        return Vector2D(
                rhs * lhs.coords[1],
                -rhs * lhs.coords[0]
        );
    }

	Real Vector2D::distance(Vector2D const & lhs, Vector2D const & rhs) {
		return Math<Real>::sqrt(Vector2D::distanceSquared(lhs, rhs));
	}
	
	Real Vector2D::distanceSquared(Vector2D const & lhs, Vector2D const & rhs) {
		Vector2D diff(Vector2D::sub(lhs, rhs));
		
		return diff.lengthSquared();
	}
	
     Real Vector2D::dot(Vector2D const & rhs) const {
        return coords[0] * rhs.coords[0] + coords[1] * rhs.coords[1];
    }

	bool Vector2D::equals(Vector2D const & rhs, Real eps) const {
		return (Math<Real>::abs(getX() - rhs.getX()) <= eps) && (Math<Real>::abs(getY() - rhs.getY()) <= eps);
	}
	
     Real Vector2D::get(int i) const {
        return coords[i];
    }

    bool Vector2D::isColinear(Vector2D const & rhs, Real tol) const {
        assert(tol >= 0);

        Real dotProduct = this->dot(rhs); 
        Real lengthProduct = this->length() * rhs.length();
        
        if (lengthProduct == (Real)0.0) {
            return false;
            //throw Vector3DNullVectorInColinearityTestException("");
        }
        
        return Math<Real>::areEqualWithTol(Math<Real>::abs(dotProduct/lengthProduct), (Real)1.0, tol);
    }
	
     Real Vector2D::length() const {
        return Math<Real>::sqrt(lengthSquared());
    }

     Real Vector2D::lengthSquared() const {
        return dot(*this);
    }

     Vector2D & Vector2D::negate() {
        coords[0] = -coords[0];
        coords[1] = -coords[1];

        return *this;
    }

     Vector2D Vector2D::negate(Vector2D const & rhs) {
        return Vector2D(-rhs.coords[0], -rhs.coords[1]);
    }

     Vector2D & Vector2D::norm() {
        mult(1.0 / length());

        return *this;
    }

     Vector2D Vector2D::norm(Vector2D const & rhs) {
        Vector2D res(rhs);
        res.norm();

        return res;
    }

     Vector2D & Vector2D::mult(Real rhs) {
        coords[0] *= rhs;
        coords[1] *= rhs;

        return *this;
    }
    
     Vector2D & Vector2D::div(Real rhs) {
        coords[0] /= rhs;
        coords[1] /= rhs;

        return *this;
    }

     Vector2D Vector2D::mult(Vector2D const & lhs, Real rhs) {
        return Vector2D(lhs.coords[0] * rhs, lhs.coords[1] * rhs);
    }

     Vector2D Vector2D::div(Vector2D const & lhs, Real rhs) {
        return Vector2D(lhs.coords[0] / rhs, lhs.coords[1] / rhs);
    }
    
	Real const * Vector2D::constantPointerToCoordinates() const {
		return &coords[0];
	}
	
     Vector2D & Vector2D::sub(Vector2D const & rhs) {
        coords[0] -= rhs.coords[0];
        coords[1] -= rhs.coords[1];

        return *this;
    }

     Vector2D Vector2D::sub(Vector2D const & lhs, Vector2D const & rhs) {
        return Vector2D(
                lhs.coords[0] - rhs.coords[0],
                lhs.coords[1] - rhs.coords[1]
        );
    }

     bool Vector2D::isUnit() const {
        return Math<Real>::abs(length() - 1.0) < EPS;
    }


    /* void testVector2() {
        Vector2D v1(1.25, -1.50);
        assert 1.25 == v1.get(0);
        assert 1.25 == v1.getX();
        assert -1.50 == v1.get(1);
        assert -1.50 == v1.getY();
        assert 5.0 == v1.get(0);

        Vector2D v2(-0.75, 3.7);
        v1.add(v2);
        assert v1.getX() == 0.50;
        assert v1.getY() == 1.20;

        Vector2D v3 = Vector2D.add(v1, v2);
        assert v3.getX() == -0.25;
        assert v3.getY() == 4.90;

        Vector2D v4(4.0, 0.0);
        Vector2D v5(0.0, 0.1);
        System.out.println("v4.angle(v5) = " + v4.angle(v5) / Math<Real>::PI + "Pi rad");
        System.out.println("v5.angle(v4) = " + v5.angle(v4) / Math<Real>::PI + "Pi rad");
    }*/	
	
	std::ostream & operator<<(std::ostream & out, Vector2D const & vec) {
        out << std::right << std::setw(12) << std::setprecision(6);
        out << vec.getX();

        out << std::right << std::setw(12) << std::setprecision(6);
        out << vec.getY();

        return out;
	}
}