#ifndef ORIENTED_ELLIPSOID_H
#define ORIENTED_ELLIPSOID_H


#include <iostream>
#include "Matrix3D.h"
#include "Vector3D.h"

namespace ngn {

    
    class OrientedEllipsoid {
    public:
        static void change_orientation_tolerance(Real);

        OrientedEllipsoid();
        OrientedEllipsoid(Vector3D const &, Matrix3D const &, Vector3D const &);

        Vector3D const & getCenter()const;
        Vector3D const & getExtents()const;
        Matrix3D const & getOrientation()const;

        void setCenter(Vector3D const & center);
        void setExtents(Vector3D const &);
        void setOrientation(Matrix3D const &);

        bool equalsWithTol(OrientedEllipsoid const & rhs, Real tol)const;
        void writeTo(std::ostream &)const;

    private:
        Vector3D center;
        Matrix3D orientation_;
        Vector3D extents_;

        static Real tolerance_;

        bool valid()const;
        bool areValidExtents(Vector3D const &)const;
        bool isValidOrientation(Matrix3D const &)const;
    };

    
    const bool overlap_detected(OrientedEllipsoid const &, OrientedEllipsoid const &);    
    Real volume(OrientedEllipsoid const &);
	std::ostream & operator<<(std::ostream &, OrientedEllipsoid const &);

    ////////////////////////////////////////////////////////////////////////

}

#endif // ORIENTED_BOUNDING_ELLIPSOID_H
