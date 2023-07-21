#include "order_eigen_values.h"
#include "Matrix3D.h"
#include "Vector3D.h"

namespace ngn {
	
    void order_eigen_values
    (
		Real A[3][3],
		Real w[3]
	) {
        int unsigned indices[3] = {0, 1, 2};
        int unsigned temp;
        bool reordered = false;

        if (w[indices[0]] < w[indices[1]]) {
            reordered = true;
            temp = indices[1];
            indices[1] = indices[0];
            indices[0] = temp;
        }

        if (w[indices[1]] < w[indices[2]]) {
            reordered = true;
            temp = indices[2];
            indices[2] = indices[1];
            indices[1] = temp;

            if (w[indices[1]] > w[indices[0]]) {
                temp = indices[1];
                indices[1] = indices[0];
                indices[0] = temp;
            }
        }

        if (reordered) {
            Real temp_mat[3][3];
            Real temp_vec[3];

            for (int unsigned i = 0; i < 3; ++i) {
                temp_vec[i] = w[i];

                for (int unsigned j = 0; j < 3; ++j) {
                    temp_mat[i][j] = A[i][j];
                }
            }

            for (int unsigned i = 0; i < 2; ++i) {
                if (indices[i] != i) {
                    w[i] = temp_vec[indices[i]];
                    A[0][i] = temp_mat[0][indices[i]];
                    A[1][i] = temp_mat[1][indices[i]];
                    A[2][i] = temp_mat[2][indices[i]];
                }
            }

            w[2] = temp_vec[indices[2]];
        }

        A[0][2] = A[1][0] * A[2][1] - A[2][0] * A[1][1];
        A[1][2] = A[2][0] * A[0][1] - A[0][0] * A[2][1];
        A[2][2] = A[0][0] * A[1][1] - A[1][0] * A[0][1];
    }

    void order_eigen_values
    (
		Matrix3D & A,
		Vector3D & w
	) {
        int unsigned indices[3] = {0, 1, 2};
        int unsigned temp;
        bool reordered = false;

        if (w.get(indices[0]) < w.get(indices[1])) {
            reordered = true;
            temp = indices[1];
            indices[1] = indices[0];
            indices[0] = temp;
        }

        if (w.get(indices[1]) < w.get(indices[2])) {
            reordered = true;
            temp = indices[2];
            indices[2] = indices[1];
            indices[1] = temp;

            if (w.get(indices[1]) > w.get(indices[0])) {
                temp = indices[1];
                indices[1] = indices[0];
                indices[0] = temp;
            }
        }

        if (reordered) {
            Matrix3D temp_mat(A);
            Vector3D temp_vec(w);

            for (int unsigned i = 0; i < 2; ++i) {
                if (indices[i] != i) {
                    w.set(i, temp_vec.get(indices[i]));
                    A.set(0, i, temp_mat.get(0, indices[i]));
                    A.set(1, i, temp_mat.get(1, indices[i]));
                    A.set(2, i, temp_mat.get(2, indices[i]));
                }
            }

            w.set(2, temp_vec.get(indices[2]));
        }

        A.set(0, 2, A.get(1, 0) * A.get(2, 1) - A.get(2, 0) * A.get(1, 1));
        A.set(1, 2, A.get(2, 0) * A.get(0, 1) - A.get(0, 0) * A.get(2, 1));
        A.set(2, 2, A.get(0, 0) * A.get(1, 1) - A.get(1, 0) * A.get(0, 1));
    }
}