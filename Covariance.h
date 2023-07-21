#ifndef COVARIANCE_H
#define COVARIANCE_H

//#include "linear_algebra.h"
#include "Matrix3D.h"
#include "Vector3D.h"

#include <cassert>
#include <vector>

namespace ngn {
    class Matrix3D;
    class Vector3D;

    
    class Covariance {
    public:
        Covariance();

        Matrix3D operator()(
                std::vector<Vector3D> const & vertices,
                Vector3D const & center
                ) const;

        Matrix3D operator()(
                std::vector<Vector3D> const & vertices,
                Vector3D const & center,
                std::vector<Vector3D> &distances
                ) const;

        Matrix3D operator()(
                std::vector<Vector3D> const & vertices,
                std::vector<int unsigned> const & indices,
                Vector3D const & center
                ) const;

        Matrix3D operator()(
                std::vector<Vector3D> const & vertices,
                std::vector<int unsigned> const & indices,
                Vector3D const & center,
                std::vector<Vector3D> &distances
                ) const;
    };

    ////////////////////////////////////////////////////////////////////////

}

#endif // COVARIANCE_H