#include "Eigen.h"
#include "Math.h"
#include "Matrix3D.h"
#include "TridiagonalForm.h"
#include "Vector3D.h"

namespace ngn {

    bool eigen(Matrix3D & A, Matrix3D & Q, Vector3D & w) 
    {
        const int n = 3;
        Vector3D e; // The third element is used only as temporary workspace
        Real g, r, p, f, b, s, c, t; // Intermediate storage
        int nIter;
        int m;

        //Transform A to real tridiagonal form by the Householder method
        tridiagonalForm(A, Q, w, e);

        // Calculate eigensystem of the remaining real symmetric tridiagonal matrix
        // with the QL method
        //
        // Loop over all off-diagonal elements
        for (int l = 0; l < n - 1; l++) {
            nIter = 0;
            while (1) {
                // Check for convergence and exit iteration loop if off-diagonal
                // element e(l) is zero
                for (m = l; m <= n - 2; m++) {
                    g = Math<Real>::abs(w.get(m)) + Math<Real>::abs(w.get(m + 1));

                    if (Math<Real>::abs(e.get(m)) + g == g)
                        break;
                }
                if (m == l)
                    break;

                if (nIter++ >= 30)
                    return false;

                // Calculate g = d_m - k
                g = (w.get(l + 1) - w.get(l)) / (e.get(l) + e.get(l));
                r = Math<Real>::sqrt(Math<Real>::sqr(g) + 1.0);
                if (g > 0)
                    g = w.get(m) - w.get(l) + e.get(l) / (g + r);
                else
                    g = w.get(m) - w.get(l) + e.get(l) / (g - r);

                s = c = 1.0;
                p = 0.0;

                for (int i = m - 1; i >= l; i--) {
                    f = s * e.get(i);
                    b = c * e.get(i);
                    if (Math<Real>::abs(f) > Math<Real>::abs(g)) {
                        c = g / f;
                        r = Math<Real>::sqrt(Math<Real>::sqr(c) + 1.0);
                        e.set(i + 1, f * r);
                        c *= (s = 1.0 / r);
                    } else {
                        s = f / g;
                        r = Math<Real>::sqrt(Math<Real>::sqr(s) + 1.0);
                        e.set(i + 1, g * r);
                        s *= (c = 1.0 / r);
                    }

                    g = w.get(i + 1) - p;
                    r = (w.get(i) - g) * s + 2.0 * c * b;
                    p = s * r;
                    w.set(i + 1, g + p);
                    g = c * r - b;

                    // Form eigenvectors
                    #ifndef EVALS_ONLY
                    for (int k = 0; k < n; k++) {
                        t = Q.get(k, i + 1);
                        Q.set(k, i + 1, s * Q.get(k, i) + c * t);
                        Q.set(k, i, c * Q.get(k, i) - s * t);
                    }
                    #endif
                }
                w.set(l, w.get(l) - p);
                e.set(l, g);
                e.set(m, (Real) 0.0);
            }
        }

        return true;
    }

    bool eigen(Real A[3][3], Real Q[3][3], Real w[3]) {
        const int n = 3;
        Real e[3]; // The third element is used only as temporary workspace
        Real g, r, p, f, b, s, c, t; // Intermediate storage
        int nIter;
        int m;

        // Transform A to real tridiagonal form by the Householder method
        tridiagonalForm(A, Q, w, e);

        // Calculate eigensystem of the remaining real symmetric tridiagonal matrix
        // with the QL method
        //
        // Loop over all off-diagonal elements
        for (int l = 0; l < n - 1; l++) {
            nIter = 0;
            while (1) {
                // Check for convergence and exit iteration loop if off-diagonal
                // element e(l) is zero
                for (m = l; m <= n - 2; m++) {
                    g = Math<Real>::abs(w[m]) + Math<Real>::abs(w[m + 1]);
                    if (Math<Real>::abs(e[m]) + g == g)
                        break;
                }
                if (m == l)
                    break;

                if (nIter++ >= 30)
                    return false;

                // Calculate g = d_m - k
                g = (w[l + 1] - w[l]) / (e[l] + e[l]);
                r = Math<Real>::sqrt(Math<Real>::sqr(g) + 1.0);
                if (g > 0)
                    g = w[m] - w[l] + e[l] / (g + r);
                else
                    g = w[m] - w[l] + e[l] / (g - r);

                s = c = 1.0;
                p = 0.0;
                for (int i = m - 1; i >= l; i--) {
                    f = s * e[i];
                    b = c * e[i];
                    if (Math<Real>::abs(f) > Math<Real>::abs(g)) {
                        c = g / f;
                        r = Math<Real>::sqrt(Math<Real>::sqr(c) + 1.0);
                        e[i + 1] = f * r;
                        c *= (s = 1.0 / r);
                    } else {
                        s = f / g;
                        r = Math<Real>::sqrt(Math<Real>::sqr(s) + 1.0);
                        e[i + 1] = g * r;
                        s *= (c = 1.0 / r);
                    }

                    g = w[i + 1] - p;
                    r = (w[i] - g) * s + 2.0 * c*b;
                    p = s * r;
                    w[i + 1] = g + p;
                    g = c * r - b;

                    // Form eigenvectors
                    #ifndef EVALS_ONLY
                    for (int k = 0; k < n; k++) {
                        t = Q[k][i + 1];
                        Q[k][i + 1] = s * Q[k][i] + c*t;
                        Q[k][i] = c * Q[k][i] - s*t;
                    }
                    #endif
                }
                w[l] -= p;
                e[l] = g;
                e[m] = 0.0;
            }
        }

        return true;
    }
}