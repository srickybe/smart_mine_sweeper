#include "OrientedEllipsoid.h"
#include <cassert>
#include "Math.h"

namespace ngn {

    Real
    OrientedEllipsoid::tolerance_ = (Real) 1.0e-6;

    
    void OrientedEllipsoid::change_orientation_tolerance(Real tol) {
        assert(tolerance_ > (Real) 0.0);

        tolerance_ = tol;
    }

    
    OrientedEllipsoid::OrientedEllipsoid()
    : center(Vector3D::zero()),
    orientation_(Matrix3D::identity()),
    extents_((Real) 1.0, (Real) 1.0, (Real) 1.0) {
    }

    
    OrientedEllipsoid::OrientedEllipsoid(Vector3D const & center, Matrix3D const & orientation, Vector3D const & extents)
    : center(center),
    orientation_(orientation),
    extents_(extents) {
        assert(this->areValidExtents(extents_));
        assert(this->isValidOrientation(orientation_));
    }

    
    bool OrientedEllipsoid::equalsWithTol(OrientedEllipsoid const & rhs, Real tol)const {
        return getCenter().equalsWithTol(rhs.getCenter(), tol) &&
				getOrientation().equalsWithTol(rhs.getOrientation(), tol) &&
                getExtents().equalsWithTol(rhs.getExtents(), tol);
    }
    
    
    Vector3D const & OrientedEllipsoid::getCenter()const {
        return center;
    }

    
    Matrix3D const & OrientedEllipsoid::getOrientation()const {
        return orientation_;
    }

    
    Vector3D const & OrientedEllipsoid::getExtents()const {
        return extents_;
    }

    
    void OrientedEllipsoid::setCenter(Vector3D const & center) {
        this->center = center;
    }

    
    void OrientedEllipsoid::setOrientation(Matrix3D const & orientation) {
        assert(this->isValidOrientation(orientation));

        orientation_ = orientation;
    }

    
    void OrientedEllipsoid::setExtents(Vector3D const & extents) {
        assert(this->areValidExtents(extents));

        extents_ = extents;
    }

    
    void OrientedEllipsoid::writeTo(std::ostream & out)const {
        out << "center =\n" << center << "\n";
        out << "orientation =\n" << orientation_ << "\n";
        out << "extents =\n" << extents_ << "\n";
    }

    
    bool OrientedEllipsoid::valid()const {
        return ( this->areValidExtents(extents_) &&
                this->isValidOrientation(orientation_));
    }

    
    bool OrientedEllipsoid::areValidExtents(Vector3D const & vertex)const {
        if (vertex.equalsWithTol(Vector3D::zero(), tolerance_)) {
            std::cout << "vertex =\n" << vertex << "\n";
            return false;
        }

        for (int unsigned i = 0; i < 3; ++i) {
            if (vertex.get(i) < (Real) 0.0) {
                return false;
            }
        }

        return true;
    }

    
    bool OrientedEllipsoid::isValidOrientation(Matrix3D const & matrix)const {
        if (!Matrix3D::inv(matrix).equalsWithTol(Matrix3D::transp(matrix), tolerance_)) {
            return false;
        }

        Vector3D axes[3] = {
            Vector3D(matrix.get(0, 0), matrix.get(1, 0), matrix.get(2, 0)),
            Vector3D(matrix.get(0, 1), matrix.get(1, 1), matrix.get(2, 1)),
            Vector3D(matrix.get(0, 2), matrix.get(1, 2), matrix.get(2, 2))
        };

        if (!axes[2].equalsWithTol(axes[0].cross(axes[1]), tolerance_)) {
            return false;
        }

        return true;
    }

    std::ostream & operator<<(std::ostream & out, OrientedEllipsoid const & obv) {
        obv.writeTo(out);

        return out;
    }

    
    const bool overlap_detected(OrientedEllipsoid const & obb1, OrientedEllipsoid const & obb2) {
        return false;
    }

    Real volume(OrientedEllipsoid const & obe) {
        return (Real) (4.0 / 3.0) * Math<Real>::PI * obe.getExtents().getX() * obe.getExtents().getY() * obe.getExtents().getZ();
    }
}