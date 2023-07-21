#ifndef TRIDIAGONAL_FORM_H
#define TRIDIAGONAL_FORM_H

#include "Math.h"
#include "Matrix3D.h"
#include "Vector3D.h"
#include <cmath>

namespace ngn {
    class Matrix3D;
    class Vector3D;

    void tridiagonalForm
    (
            Real[3][3],
            Real[3][3],
            Real[3],
            Real[2]
            );

    void tridiagonalForm
    (
            Matrix3D const &,
            Matrix3D &,
            Vector3D &,
            Vector3D &
            );

    ////////////////////////////////////////////////////////////////////////

}

#endif // TRIDIAGONAL_FORM_H