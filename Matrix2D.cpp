#include <iomanip>
#include <ios>
#include <iostream>
#include "Math.h"
#include "Matrix2D.h"
#include "UnsupportedOperationException.h"
#include "Vector2D.h"

namespace ngn {
	
    Matrix2D Matrix2D::identity() {
        return Matrix2D(
                1.0, 0.0,
                0.0, 1.0);
    }

    Matrix2D Matrix2D::zero() {
        return Matrix2D(
                0.0, 0.0,
                0.0, 0.0);
    }

     Matrix2D::Matrix2D()
    : Matrix2D(
    0.0, 0.0,
    0.0, 0.0
    ) {

    }

     Matrix2D::Matrix2D(Matrix2D const & m)
    : Matrix2D(
    m.get(0, 0), m.get(0, 1),
    m.get(1, 0), m.get(1, 1)
    ) {

    }

    Matrix2D Matrix2D::star(Real angularVelocity,Matrix2D const & orient) {
       Matrix2D lhs = Matrix2D(
                0.0, -angularVelocity,
                angularVelocity, 0.0
                );

        return lhs.mult(orient);
    }

     Matrix2D::Matrix2D(
            Real m00, Real m01,
            Real m10, Real m11) {
        elems[0][0] = m00;
        elems[0][1] = m01;
        elems[1][0] = m10;
        elems[1][1] = m11;
    }

     bool Matrix2D::equals(Matrix2D const & rhs, Real tol) const {
        if (this == &rhs) {
            for (int i = 0; i < DIM; ++i) {
                for (int j = 0; j < DIM; ++j) {
                    if (Math<Real>::abs(get(i, j) - rhs.get(i, j)) >= tol) {
                        return false;
                    }
                }
            }

            return true;
        }

        return true;
    }

     Vector2D Matrix2D::getColumn(int j) const {
        return Vector2D(get(0, j), get(1, j));
    }

     Vector2D Matrix2D::getRow(int i) const {
        return Vector2D(get(i, 0), get(i, 1));
    }

    Matrix2D & Matrix2D::add(Matrix2D const & rhs) {
        for (int i = 0; i < DIM; ++i) {
            for (int j = 0; j < DIM; ++j) {
                set(i, j, get(i, j) + rhs.get(i, j));
            }
        }

        return *this;
    }

    Matrix2D Matrix2D::add(Matrix2D const & lhs, Matrix2D const & rhs) {
       Matrix2D res;

        for (int i = 0; i < DIM; ++i) {
            for (int j = 0; j < DIM; ++j) {
                res.set(i, j, lhs.get(i, j) + rhs.get(i, j));
            }
        }

        return res;
    }

     Real Matrix2D::det() const {
        return (get(0, 0) * get(1, 1) - get(0, 1) * get(1, 0));
    }

     Real Matrix2D::get(int i, int j) const {
        return elems[i][j];
    }

    Matrix2D & Matrix2D::inv() {
       Matrix2D res(Matrix2D::inv(*this));
        *this = res;

        return *this;
    }

    Matrix2D Matrix2D::inv(Matrix2D const & rhs) {
        Real dt = rhs.det();

        if (dt == 0.0) {
            throw Matrix2DNullDeterminantException("");
        }

        Real invDt = 1.0 / dt;
        Matrix2D res;
        res.set(0, 0, rhs.get(1, 1) * invDt);
        res.set(0, 1, -rhs.get(0, 1) * invDt);
        res.set(1, 0, -rhs.get(1, 0) * invDt);
        res.set(1, 1, rhs.get(0, 0) * invDt);

        return res;
    }

     Matrix2D & Matrix2D::mult(Real rhs) {
        for (int i = 0; i < DIM; ++i) {
            for (int j = 0; j < DIM; ++j) {
                set(i, j, get(i, j) * rhs);
            }
        }

        return *this;
    }

     Matrix2D Matrix2D::mult(Matrix2D const & lhs, Real rhs) {
        Matrix2D res(lhs);
        res.mult(rhs);

        return res;
    }

     Matrix2D Matrix2D::mult(Matrix2D const & rhs) const {
        Matrix2D res;

        for (int i = 0; i < DIM; ++i) {
            for (int j = 0; j < DIM; ++j) {
                res.set(i, j, 0);

                for (int k = 0; k < DIM; ++k) {
                    res.set(i, j, res.get(i, j) + get(i, k) * rhs.get(k, j));
                }
            }
        }

        return res;
    }

     Vector2D Matrix2D::mult(Vector2D const & rhs) const {
        return Vector2D(
                get(0, 0) * rhs.get(0) + get(0, 1) * rhs.get(1),
                get(1, 0) * rhs.get(0) + get(1, 1) * rhs.get(1)
                );
    }

     Matrix2D & Matrix2D::orthonorm() {
        Real lengthX = Math<Real>::sqrt(
                get(0, 0) * get(0, 0)
                + get(1, 0) * get(1, 0)
                );

        if (lengthX == 0.0) {
            throw Matrix2DNullColumnException("x_axis is equal to zero");
        }

        Real invLengthX = 1.0 / lengthX;
        set(0, 0, get(0, 0) * invLengthX);
        set(1, 0, get(1, 0) * invLengthX);

        set(0, 1, -get(1, 0));
        set(1, 1, get(0, 0));

        return *this;
    }

     Matrix2D Matrix2D::orthonorm(Matrix2D const & rhs) {
        Matrix2D res(rhs);
        res.orthonorm();

        return res;
    }

     void Matrix2D::set(int i, int j, Real val) {
        elems[i][j] = val;
    }

     Matrix2D Matrix2D::fromAngle(Real angle) {
        Real c = Math<Real>::cos(angle);
        Real s = Math<Real>::sin(angle);

        return Matrix2D(c, s, -s, c);
    }

     Matrix2D & Matrix2D::sub(Matrix2D const & rhs) {
        for (int i = 0; i < DIM; ++i) {
            for (int j = 0; j < DIM; ++j) {
                set(i, j, get(i, j) - rhs.get(i, j));
            }
        }

        return *this;
    }

     Matrix2D Matrix2D::sub(Matrix2D const & lhs, Matrix2D const & rhs) {
        Matrix2D res;

        for (int i = 0; i < DIM; ++i) {
            for (int j = 0; j < DIM; ++j) {
                res.set(i, j, lhs.get(i, j) - rhs.get(i, j));
            }
        }

        return res;
    }

     Real Matrix2D::toAngle() const {
        if (isRotation((Real)1.0e-6)) {
            return Math<Real>::acos(get(0, 0));
        } else {
            throw Matrix2DNotRotationException("");
        }
    }

     Matrix2D & Matrix2D::transp() {
        Real tmp;

        for (int i = 0; i < DIM; ++i) {
            for (int j = i + 1; j < DIM; ++j) {
                tmp = get(i, j);
                set(i, j, get(j, i));
                set(j, i, tmp);
            }
        }

        return *this;
    }

     Matrix2D Matrix2D::transp(Matrix2D const & rhs) {
        Matrix2D res(rhs);
        res.transp();

        return res;
    }

     bool Matrix2D::isRotation(Real tol) const {
        for (int i = 0; i < DIM; ++i) {
            for (int j = 0; j < DIM; ++j) {
                Real coef = 0.0;

                for (int k = 0; k < DIM; ++k) {
                    coef += get(i, k) * get(j, k);
                }

                if (i != j) {
                    if (Math<Real>::abs(coef) >= 2.0 * tol) {
                        return false;
                    }
                } else {
                    if (Math<Real>::abs(coef - 1.0) >= 2.0 * tol) {
                        return false;
                    }
                }
            }
        }

        return true;
    }
    
    
    std::ostream & operator<<(std::ostream & out, Matrix2D const & mat) {
        for (int unsigned i = 0; i < 2; ++i) {
            for (int unsigned j = 0; j < 2; ++j) {
                out << std::right << std::setw(16)
                        << std::setprecision(6) << mat.get(i, j);
            }

            out << "\n";
        }

        return out;
    }	
}