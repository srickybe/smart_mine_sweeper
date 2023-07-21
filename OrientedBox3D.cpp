#include "OrientedBox3D.h"
#include "IllegalArgumentException.h"
#include "Intersection.h"
#include "Math.h"
#include "UnsupportedOperationException.h"
#include <iostream>
#include <vector>


namespace ngn {
    
    OrientedBox3D::OrientedBox3D() {
        center_ = Vector3D::zero();
        orientation_ = Matrix3D::zero();
        halfExtents_ = Vector3D::zero();
    }

    
    OrientedBox3D::OrientedBox3D(
            Vector3D const & center,
            Matrix3D const & orientation,
            Vector3D const & extents
            ) {
        this->center_ = center;
        this->orientation_ = orientation;
        this->halfExtents_ = extents;
    }

    
    Vector3D const & OrientedBox3D::getCenter() const {
        return center_;
    }

    
    void OrientedBox3D::setCenter(Vector3D const & center) {
        this->center_ = center;
    }

    
    Matrix3D const & OrientedBox3D::getOrientation() const {
        return orientation_;
    }

    
    void OrientedBox3D::setOrientation(Matrix3D const & orientation) {
        this->orientation_ = orientation;
    }

    
    Vector3D const & OrientedBox3D::getHalfExtents() const {
        return halfExtents_;
    }

    
    void OrientedBox3D::setHalfExtents(Vector3D const & halfExtents) {
        for (int i = 0; i < 3; ++i) {
            if (halfExtents.get(i) < 0.0) {
                std::cout << "halfExtents coordinate is inferior or equal to zero\n";
                throw IllegalArgumentException("halfExtents coordinate is inferior or equal to zero");
            }
        }

        this->halfExtents_ = halfExtents;
    }

    
    bool OrientedBox3D::contains(Vector3D const & point) const {
        Vector3D dist(Vector3D::sub(point, getCenter()));
        Vector3D dots(Matrix3D::transp(getOrientation()).mult(dist));

        for (int i = 0; i < 3; ++i) {
            if (Math<Real>::abs(dots.get(i)) > getHalfExtents().get(i)) {
                return false;
            }
        }

        return true;
    }

    std::vector<Vector3D> OrientedBox3D::corners() const {
		std::vector<Vector3D> points;
		points.push_back(Vector3D(-halfExtents_.getX(), -halfExtents_.getY(), -halfExtents_.getZ()).add(getCenter()));
		points.push_back(Vector3D(halfExtents_.getX(), -halfExtents_.getY(), -halfExtents_.getZ()).add(getCenter()));
		points.push_back(Vector3D(-halfExtents_.getX(), halfExtents_.getY(), -halfExtents_.getZ()).add(getCenter()));
		points.push_back(Vector3D(halfExtents_.getX(), halfExtents_.getY(), -halfExtents_.getZ()).add(getCenter()));
		points.push_back(Vector3D(-halfExtents_.getX(), -halfExtents_.getY(), halfExtents_.getZ()).add(getCenter()));
		points.push_back(Vector3D(halfExtents_.getX(), -halfExtents_.getY(), halfExtents_.getZ()).add(getCenter()));
		points.push_back(Vector3D(-halfExtents_.getX(), halfExtents_.getY(), halfExtents_.getZ()).add(getCenter()));
		points.push_back(Vector3D(halfExtents_.getX(), halfExtents_.getY(), halfExtents_.getZ()).add(getCenter()));

		return points;		
	}
	
    bool OrientedBox3D::equals(OrientedBox3D const & rhs, Real tol) const {
        return getCenter().equalsWithTol(rhs.getCenter(), tol) 
			&& getOrientation().equalsWithTol(rhs.getOrientation(), tol) 
			&& getHalfExtents().equalsWithTol(rhs.getHalfExtents(), tol);
    }

    
    Real OrientedBox3D::volume() const {
        return 8.0 * halfExtents_.getX() * halfExtents_.getY() * halfExtents_.getZ();
    }

	Vector3D const & OrientedBox3D::getPosition() const {
		return getCenter();
	}
	
	void OrientedBox3D::setPosition(Vector3D const & position) {
		center_ = position;
	}
		
	Intersection::Result OrientedBox3D::intersectIntersectable(Intersectable const & intersectable) const {
		return intersectable.intersectOrientedBox3D(*this);
	}
	
	Intersection::Result OrientedBox3D::intersectAxisAlignedBox3D(AxisAlignedBox3D const & box) const {
		throw UnsupportedOperationException("");
	}
	
	Intersection::Result OrientedBox3D::intersectLineSegment(LineSegment const & lineSegment) const {
		throw UnsupportedOperationException("");
	}
	
	Intersection::Result OrientedBox3D::intersectOrientedBox3D(OrientedBox3D const & box) const {
		Intersection::Result result = Intersection::orientedBox3DIntersectOrientedBox3D(*this, box);
		
		return result;
	}
	
	Intersection::Result OrientedBox3D::intersectPlane(Plane const & plane) const {
		Intersection::Result result = Intersection::orientedBox3DIntersectPlane(*this, plane);
		
		return result;
	}
	
	Intersection::Result OrientedBox3D::intersectSphere(Sphere const & sphere) const {
		Intersection::Result result = Intersection::orientedBox3DIntersectSphere(*this, sphere);
		
		return result;
	}
    
	void OrientedBox3D::print(std::ostream & out) const {
        out << "center = " << getCenter() << "\n";
        out << "orientation =\n" << getOrientation() << "\n";
        out << "halfExtents = " << getHalfExtents() << "\n";
	}
	
    std::ostream & operator<<(std::ostream& out, OrientedBox3D const & box) {
        box.print(out);

        return out;
    }
}