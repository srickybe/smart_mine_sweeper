#include "Plane.h"
#include "Intersection.h"
#include "Sphere.h"
#include "UnsupportedOperationException.h"

namespace ngn {

    
    Plane::Plane(Vector3D const & normal, Vector3D const & point) {
        if (isValidNormal(normal)) {
            this->normal_ = normal;
            this->point_ = point;
            this->distance_ = point.dot(normal);
        } else {
            //throw IllegalArgumentException();
        }
    }

    
    Plane::Plane(Vector3D const & normal, Real distance) {
        if (isValidNormal(normal)) {
            this->normal_ = normal;
            this->distance_ = distance;
            this->point_ = Vector3D::mult(this->normal_, distance_);
        } else {
            //
        }
    }

    
    Plane Plane::fromNormalAndPoint(Vector3D const & normal, Vector3D const & point) {
        return Plane(normal, point);
    }

    
    bool Plane::isValidNormal(Vector3D const & normal) const {
		Real tol = 1.0e-6;
        return normal.isUnit(tol);
    }

    
    Vector3D const & Plane::getPoint() const {
        return point_;
    }

    
    Vector3D const & Plane::getNormal() const {
        return normal_;
    }

    
    Real Plane::getDistance() const {
        return distance_;
    }

    
    Real Plane::distanceFromPoint(Vector3D const & vec) const {
        return Vector3D::sub(vec, this->point_).dot(normal_);
    }

	Vector3D const & Plane::getPosition() const {
		throw UnsupportedOperationException("");
	}
	
	void Plane::setPosition(Vector3D const & position) {
		
	}
		
	Matrix3D const & Plane::getOrientation() const {
		throw UnsupportedOperationException("");
	}
	
	void Plane::setOrientation(Matrix3D const & orientation) {
		throw UnsupportedOperationException("");
	}
		
    Intersection::Result Plane::intersectIntersectable(Intersectable const & intersectable) const {
        return intersectable.intersectPlane(*this);
    }

    Intersection::Result Plane::intersectAxisAlignedBox3D(AxisAlignedBox3D const & box) const {
        throw UnsupportedOperationException("");
    }
    
	Intersection::Result Plane::intersectLineSegment(LineSegment const & lineSegment) const {
		throw UnsupportedOperationException("");
	}
	
    Intersection::Result Plane::intersectOrientedBox3D(OrientedBox3D const & box) const {
        return Intersection::orientedBox3DIntersectPlane(box, *this);
    }

    Intersection::Result Plane::intersectPlane(Plane const & plane) const {
        return Intersection::Result(true);
    }

    Intersection::Result Plane::intersectSphere(Sphere const & sphere) const {
        return Intersection::planeIntersectSphere(*this, sphere);
		/*Real distance = this->distanceFromPoint(sphere.getCenter());

        return Intersection::Result(distance <= sphere.getRadius());*/
    }
	
	void Plane::print(std::ostream & out) const {
		throw UnsupportedOperationException("");
	}
}