#include "TridiagonalForm.h"

namespace ngn {

    void tridiagonalForm
    (
            Real A[3][3],
            Real Q[3][3],
            Real d[3],
            Real e[2]
            ) {
        // ----------------------------------------------------------------------------
        // Reduces a symmetric 3x3 matrix to tridiagonal form by applying
        // (unitary) Householder transformations:
        //            [ d[0]  e[0]       ]
        //    A = Q . [ e[0]  d[1]  e[1] ] . Q^T
        //            [       e[1]  d[2] ]
        // The function accesses only the diagonal and upper triangular parts of
        // A. The access is read-only.
        // ---------------------------------------------------------------------------

        const int n = 3;
        Real u[n], q[n];
        Real omega, f;
        Real K, h, g;

        // Initialize Q to the identitity matrix
        #ifndef EVALS_ONLY
        for (int i = 0; i < n; i++) {
            Q[i][i] = 1.0;
            for (int j = 0; j < i; j++)
                Q[i][j] = Q[j][i] = 0.0;
        }
        #endif

        // Bring first row and column to the desired form
        h = Math<Real>::sqr(A[0][1]) + Math<Real>::sqr(A[0][2]);
        if (A[0][1] > 0)
            g = -sqrt(h);
        else
            g = sqrt(h);
        e[0] = g;
        f = g * A[0][1];
        u[1] = A[0][1] - g;
        u[2] = A[0][2];

        omega = h - f;
        if (omega > 0.0) {
            omega = 1.0 / omega;
            K = 0.0;
            for (int i = 1; i < n; i++) {
                f = A[1][i] * u[1] + A[i][2] * u[2];
                q[i] = omega * f; // p
                K += u[i] * f; // u* A u
            }
            K *= 0.5 * Math<Real>::sqr(omega);

            for (int i = 1; i < n; i++)
                q[i] = q[i] - K * u[i];

            d[0] = A[0][0];
            d[1] = A[1][1] - 2.0 * q[1] * u[1];
            d[2] = A[2][2] - 2.0 * q[2] * u[2];

            // Store inverse Householder transformation in Q
            #ifndef EVALS_ONLY
            for (int j = 1; j < n; j++) {
                f = omega * u[j];
                for (int i = 1; i < n; i++)
                    Q[i][j] = Q[i][j] - f * u[i];
            }
            #endif

            // Calculate updated A[1][2] and store it in e[1]
            e[1] = A[1][2] - q[1] * u[2] - u[1] * q[2];
        } else {
            for (int i = 0; i < n; i++)
                d[i] = A[i][i];
            e[1] = A[1][2];
        }
    }

    void tridiagonalForm
    (
            Matrix3D const & A,
            Matrix3D & Q,
            Vector3D & d,
            Vector3D & e
    ) {
        // ----------------------------------------------------------------------------
        // Reduces a symmetric 3x3 matrix to tridiagonal form by applying
        // (unitary) Householder transformations:
        //            [ d[0]  e[0]       ]
        //    A = Q . [ e[0]  d[1]  e[1] ] . Q^T
        //            [       e[1]  d[2] ]
        // The function accesses only the diagonal and upper triangular parts of
        // A. The access is read-only.
        // ---------------------------------------------------------------------------

        const int n = 3;
        Real u[n], q[n];
        Real omega, f;
        Real K, h, g;

        // Initialize Q to the identitity matrix
        #ifndef EVALS_ONLY
        for (int i = 0; i < n; i++) {
            Q.set(i, i, (Real) 1.0);

            for (int j = 0; j < i; j++) {
                Q.set(i, j, (Real) 0.0);
                Q.set(j, i, (Real) 0.0);
            }
        }
        #endif

        // Bring first row and column to the desired form
        h = Math<Real>::sqr(A.get(0, 1)) + Math<Real>::sqr(A.get(0, 2));
        if (A.get(0, 1) > 0)
            g = -sqrt(h);
        else
            g = sqrt(h);
        e.setX(g);
        f = g * A.get(0, 1);
        u[1] = A.get(0, 1) - g;
        u[2] = A.get(0, 2);

        omega = h - f;
        if (omega > 0.0) {
            omega = 1.0 / omega;
            K = 0.0;
            for (int i = 1; i < n; i++) {
                f = A.get(1, i) * u[1] + A.get(i, 2) * u[2];
                q[i] = omega * f; // p
                K += u[i] * f; // u* A u
            }
            K *= 0.5 * Math<Real>::sqr(omega);

            for (int i = 1; i < n; i++)
                q[i] = q[i] - K * u[i];

            d.setX(A.get(0, 0));
            d.setY(A.get(1, 1) - 2.0 * q[1] * u[1]);
            d.setZ(A.get(2, 2) - 2.0 * q[2] * u[2]);

            // Store inverse Householder transformation in Q
            #ifndef EVALS_ONLY
            for (int j = 1; j < n; j++) {
                f = omega * u[j];
                for (int i = 1; i < n; i++)
                    Q.set(i, j, Q.get(i, j) - f * u[i]);
            }
            #endif

            // Calculate updated A[1][2] and store it in e[1]
            e.setY(A.get(1, 2) - q[1] * u[2] - u[1] * q[2]);
        } else {
            for (int i = 0; i < n; i++) {
                d.set(i, A.get(i, i));
            }
            e.setY(A.get(1, 2));
        }
    }
}