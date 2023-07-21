#ifndef ORDER_EIGEN_VALUES_H
#define ORDER_EIGEN_VALUES_H

#include "Real.h"

namespace ngn {
    class Matrix3D;
    class Vector3D;

    void order_eigen_values
    (
		Real A[3][3],
		Real w[3]
	);

    void order_eigen_values
    (
		Matrix3D & A,
		Vector3D & w
	);

    ////////////////////////////////////////////////////////////////////////


}

#endif // ORDER_EIGEN_VALUES_H