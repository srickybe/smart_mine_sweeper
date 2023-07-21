#include "Vector3D.h"
#include <iomanip>
#include <iostream>
#include <cassert>
#include <cmath>
#include "Math.h"
#include "Matrix3D.h"

namespace ngn {
    Vector3D const Vector3D::x_axis() {
        return Vector3D(1.0, 0.0, 0.0);
    }

    
    Vector3D const Vector3D::y_axis() {
        return Vector3D(0.0, 1.0, 0.0);
    }

    
    Vector3D const Vector3D::z_axis() {
        return Vector3D(0.0, 0.0, 1.0);
    }

    
    Vector3D const Vector3D::zero() {
        return Vector3D(0.0, 0.0, 0.0);
    }

    
    Vector3D::Vector3D()
    : coords() {
        /*coords[0] = 0;
        coords[1] = 0;
        coords[2] = 0;*/
    }

    
    Vector3D::Vector3D(Real x, Real y, Real z) {
        coords[0] = x;
        coords[1] = y;
        coords[2] = z;
    }

    
    Vector3D::Vector3D(Vector3D const & vec) {
        coords[0] = vec.coords[0];
        coords[1] = vec.coords[1];
        coords[2] = vec.coords[2];
    }

    
    Real const * Vector3D::constantPointerToCoordinates() const {
        return &coords[0];
    }

    
    Real Vector3D::getX() const {
        return coords[0];
    }

    
    Real Vector3D::getY() const {
        return coords[1];
    }

    
    Real Vector3D::getZ() const {
        return coords[2];
    }

    
    void Vector3D::setX(Real val) {
        coords[0] = val;
    }

    
    void Vector3D::setY(Real val) {
        coords[1] = val;
    }

    
    void Vector3D::setZ(Real val) {
        coords[2] = val;
    }

    Vector3D Vector3D::abs(Vector3D const & vec) {
		return Vector3D(
			Math<Real>::abs(vec.getX()), 
			Math<Real>::abs(vec.getY()), 
			Math<Real>::abs(vec.getZ())
		);
	}
	
	Vector3D & Vector3D::abs() {
		coords[0] = Math<Real>::abs(coords[0]);
		coords[1] = Math<Real>::abs(coords[1]);
		coords[2] = Math<Real>::abs(coords[2]);
		
		return *this;
	}
	
    Vector3D & Vector3D::add(Vector3D const & rhs) {
        setX(getX() + rhs.getX());
        setY(getY() + rhs.getY());
        setZ(getZ() + rhs.getZ());

        return *this;
    }

    
    Vector3D Vector3D::add(
            Vector3D const & lhs,
            Vector3D const & rhs
            ) {
        return Vector3D(
                lhs.coords[0] + rhs.coords[0],
                lhs.coords[1] + rhs.coords[1],
                lhs.coords[2] + rhs.coords[2]);
    }

    
    bool Vector3D::equalsWithTol(Vector3D const & vec, Real eps) const {
        return Math<Real>::areEqualWithTol(coords[0], vec.coords[0], eps)
                && Math<Real>::areEqualWithTol(coords[1], vec.coords[1], eps)
                && Math<Real>::areEqualWithTol(coords[2], vec.coords[2], eps);
    }

    Vector3D Vector3D::componentProduct(Vector3D const & rhs) const
    {
        return Vector3D(coords[0] * rhs.coords[0], coords[1] * rhs.coords[1], coords[2] * rhs.coords[2]);
    }
	
	Real Vector3D::distanceFrom(Vector3D const & rhs) const {
		return sqrt(squaredDistanceFrom(rhs));
	}
	
	Real Vector3D::squaredDistanceFrom(Vector3D const & rhs) const {
		Vector3D tmp(*this);
		tmp.sub(rhs);
		
		return tmp.dot(tmp);
	}
	
    Vector3D Vector3D::cross(Vector3D const & rhs) const {
        return Vector3D(
                coords[1] * rhs.coords[2] - coords[2] * rhs.coords[1],
                coords[2] * rhs.coords[0] - coords[0] * rhs.coords[2],
                coords[0] * rhs.coords[1] - coords[1] * rhs.coords[0]
                );
    }

    
    Vector3D Vector3D::cross(
            Vector3D const & lhs,
            Vector3D const & rhs) {
        return Vector3D(
                lhs.coords[1] * rhs.coords[2] - lhs.coords[2] * rhs.coords[1],
                lhs.coords[2] * rhs.coords[0] - lhs.coords[0] * rhs.coords[2],
                lhs.coords[0] * rhs.coords[1] - lhs.coords[1] * rhs.coords[0]
                );
    }

    
    Real Vector3D::dot(Vector3D const & rhs) const {
        return coords[0] * rhs.coords[0] + coords[1] * rhs.coords[1]
                + coords[2] * rhs.coords[2];
    }

    Real Vector3D::distanceFrom(Vector3D const & lhs, Vector3D const & rhs) {
		return lhs.distanceFrom(rhs);
	}
	
    Vector3D & Vector3D::div(Real rhs) {
        return this->mult((Real) 1.0 / rhs);
    }

    
    Vector3D Vector3D::div(Vector3D const & lhs, Real rhs) {
        return Vector3D::mult(lhs, (Real) 1.0 / rhs);
    }

    
    Real Vector3D::get(int i) const {
        return coords[i];
    }

    
    bool Vector3D::isColinear(Vector3D const & rhs, Real tol) const {
        assert(tol >= 0);

        Real dotProduct = this->dot(rhs); 
        Real lengthProduct = this->length() * rhs.length();
        
        if (lengthProduct == (Real)0.0) {
            return false;
            //throw Vector3DNullVectorInColinearityTestException("");
        }
        
        return Math<Real>::areEqualWithTol(Math<Real>::abs(dotProduct/lengthProduct), (Real)1.0, tol);
    }

    
    Real Vector3D::length() const {
        return Math<Real>::sqrt(lengthSquared());
    }

    
    Real Vector3D::lengthSquared() const {
        return dot(*this);
    }

    
    Vector3D & Vector3D::negate() {
        coords[0] = -coords[0];
        coords[1] = -coords[1];
        coords[2] = -coords[2];

        return *this;
    }

    
    Vector3D Vector3D::negate(Vector3D const & rhs) {
        return Vector3D(
                -rhs.coords[0],
                -rhs.coords[1],
                -rhs.coords[2]
                );
    }

    
    Vector3D & Vector3D::norm() {
        mult(1.0 / length());

        return *this;
    }

    
    Vector3D Vector3D::norm(Vector3D const & rhs) {
        Vector3D res = Vector3D(rhs);
        res.norm();

        return res;
    }

    
    Vector3D & Vector3D::mult(Real rhs) {
        coords[0] *= rhs;
        coords[1] *= rhs;
        coords[2] *= rhs;

        return *this;
    }

    
    Vector3D Vector3D::mult(Vector3D const & lhs, Real rhs) {
        return Vector3D(lhs.coords[0] * rhs, lhs.coords[1] * rhs, lhs.coords[2] * rhs);
    }

    
    Vector3D Vector3D::mult(Real lhs, Vector3D const & rhs) {
        return Vector3D::mult(rhs, lhs);
    }

    
    Vector3D & Vector3D::sub(Vector3D const & rhs) {
        coords[0] -= rhs.coords[0];
        coords[1] -= rhs.coords[1];
        coords[2] -= rhs.coords[2];

        return *this;
    }

    
    void Vector3D::set(int i, Real val) {
        coords[i] = val;
    }

    
	Real Vector3D::squaredDistanceFrom(Vector3D const & lhs, Vector3D const & rhs) {
		return lhs.squaredDistanceFrom(rhs);
	}
	
	
    Vector3D Vector3D::sub(Vector3D const & lhs, Vector3D const & rhs) {
        return Vector3D(
                lhs.coords[0] - rhs.coords[0],
                lhs.coords[1] - rhs.coords[1],
                lhs.coords[2] - rhs.coords[2]
                );
    }

    
    Matrix3D Vector3D::tensorProduct(
            Vector3D const & lhs,
            Vector3D const & rhs) {
        Matrix3D res(
                lhs.getX() * rhs.getX(),
                lhs.getX() * rhs.getY(),
                lhs.getX() * rhs.getZ(),
                lhs.getY() * rhs.getX(),
                lhs.getY() * rhs.getY(),
                lhs.getY() * rhs.getZ(),
                lhs.getZ() * rhs.getX(),
                lhs.getZ() * rhs.getY(),
                lhs.getZ() * rhs.getZ()
                );

        return res;
    }

    
    Matrix3D Vector3D::tensorProduct(
            Vector3D const & rhs
            ) const {
        Matrix3D res;

        for (int i = 0; i < 3; ++i) {
            res.set(i, i, get(i) * rhs.get(i));

            for (int j = i + 1; j < 3; ++j) {
                res.set(i, j, get(i) * rhs.get(j));
                res.set(j, i, res.get(i, j));
            }
        }

        return res;
    }

    
    bool Vector3D::isUnit(Real tol) const {
        return Math<Real>::areEqualWithTol(length(), (Real) 1.0, tol);
    }

    
    
    Matrix3D Vector3D::star(Matrix3D const & rhs) const {
        Matrix3D lhs(
                0.0, -getZ(), getY(),
                getZ(), 0.0, -getX(),
                -getY(), getX(), 0.0
                );

        return lhs.mult(rhs);
    }

    
    std::ostream & operator<<(std::ostream & out, Vector3D const & vec) {
        out << std::right << std::setw(12) << std::setprecision(6);
        out << vec.getX();

        out << std::right << std::setw(12) << std::setprecision(6);
        out << vec.getY();

        out << std::right << std::setw(12) << std::setprecision(6);
        out << vec.getZ();

        return out;
    }

    
    std::istream & operator>>(std::istream & in, Vector3D & vec) {
		Real tmp;
        in >> tmp;
		vec.setX(tmp);
        in >> tmp;
		vec.setY(tmp);
        in >> tmp;
		vec.setZ(tmp);

        return in;
    }

    
    void testVector3() {
        Vector3D v1(1.25, -1.50, 5.0);
        assert(1.25 == v1.get(0));
        assert(1.25 == v1.getX());
        assert(-1.50 == v1.get(1));
        assert(-1.50 == v1.getY());
        assert(5.0 == v1.get(0));
        assert(5.0 == v1.getZ());

        Vector3D v2(-0.75, 3.7, 3.0);
        v1.add(v2);
        assert(v1.getX() == 0.50);
        assert(v1.getY() == 1.20);
        assert(v1.getZ() == 2.00);

        Vector3D v3 = Vector3D::add(v1, v2);
        assert(v3.getX() == -0.25);
        assert(v3.getY() == 4.90);
        assert(v3.getZ() == 0.0);
		
		std::cout << "v3 = " << v3 << "\n";
    }
}