#ifndef EIGEN_H
#define EIGEN_H

#include "Real.h"

namespace ngn {
    
	class Matrix3D;
    class Vector3D;

    bool eigen
    (
        Matrix3D &,
        Matrix3D &,
        Vector3D &
    );

    bool eigen
    (
        Real[3][3],
        Real[3][3],
        Real[3]
    );

    ////////////////////////////////////////////////////////////////////////

}

#endif // EIGEN_H