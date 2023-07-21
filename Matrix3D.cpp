#include "Matrix3D.h"
#include <cassert>
#include <iomanip>
#include <iostream>
#include "AxisAngle.h"
#include "Math.h"
#include "Matrix2D.h"
#include "Quaternion.h"
#include "Rand.h"
#include "Vector3D.h"

namespace ngn {

	Matrix3DNullDeterminantException::Matrix3DNullDeterminantException(std::string const & message) {
		message_ = message;
	}
		
	Matrix3DNullColumnException::Matrix3DNullColumnException(std::string const & message) {
		message_ = message;
	}
	
	////////////////////////////////////////////////////////////////////////
        
    const Real Matrix3D::EPS = 1.0e-6;
    const int Matrix3D::N_ROWS = 3;
    const int Matrix3D::N_COLS = 3;

    Matrix3D Matrix3D::identity() {
        return Matrix3D(
                1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0);
    }

    Matrix3D Matrix3D::zero() {
        return Matrix3D(
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0);
    }

    
    Matrix3D::Matrix3D()
    : Matrix3D(
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0
    ) {

    }

    Matrix3D::Matrix3D(Matrix3D const & m)
    : Matrix3D(
    m.get(0, 0), m.get(0, 1), m.get(0, 2),
    m.get(1, 0), m.get(1, 1), m.get(1, 2),
    m.get(2, 0), m.get(2, 1), m.get(2, 2)
    ) {
    }

    Matrix3D::Matrix3D(
            Real m00, Real m01, Real m02,
            Real m10, Real m11, Real m12,
            Real m20, Real m21, Real m22
            ) {
        elems[0][0] = m00;
        elems[0][1] = m01;
        elems[0][2] = m02;
        elems[1][0] = m10;
        elems[1][1] = m11;
        elems[1][2] = m12;
        elems[2][0] = m20;
        elems[2][1] = m21;
        elems[2][2] = m22;
    }

    
	Matrix3D::Matrix3D(Matrix2D const & m) :
		Matrix3D(
			m.get(0, 0)	, m.get(0, 1)	, 0.0,
			m.get(1, 0)	, m.get(1, 1)	, 0.0,
			0.0			, 0.0 			, 1.0
		)
	{
		
	}
	
    bool Matrix3D::equalsWithTol(Matrix3D const & rhs, Real tol) const {
        if (this != &rhs) {
            for (int i = 0; i < N_ROWS; ++i) {
                for (int j = 0; j < N_COLS; ++j) {
                    if (Math<Real>::abs(get(i, j) - rhs.get(i, j)) >= tol) {
                        return false;
                    }
                }
            }

            return true;
        }

        return true;
    }

    
    Vector3D Matrix3D::getCol(int j) const {
        return Vector3D(get(0, j), get(1, j), get(2, j));
    }

    
    Vector3D Matrix3D::getRow(int i) const {
        return Vector3D(get(i, 0), get(i, 1), get(i, 2));
    }

    
	Matrix3D Matrix3D::abs(Matrix3D const & rhs) {
		return Matrix3D(
			Math<Real>::abs(rhs.get(0,0)),
			Math<Real>::abs(rhs.get(0,1)),
			Math<Real>::abs(rhs.get(0,2)),
			Math<Real>::abs(rhs.get(1,0)),
			Math<Real>::abs(rhs.get(1,1)),
			Math<Real>::abs(rhs.get(1,2)),
			Math<Real>::abs(rhs.get(2,0)),
			Math<Real>::abs(rhs.get(2,1)),
			Math<Real>::abs(rhs.get(2,2))
		);
	}
	
	Matrix3D & Matrix3D::abs() {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				set(i, j, Math<Real>::abs(get(i, j)));
			}
		}
		
		return *this;
	}
	
    Matrix3D & Matrix3D::add(Matrix3D const & rhs) {
        for (int i = 0; i < N_ROWS; ++i) {
            for (int j = 0; j < N_COLS; ++j) {
                set(i, j, get(i, j) + rhs.get(i, j));
            }
        }

        return *this;
    }

    
    Matrix3D Matrix3D::add(
            Matrix3D const & lhs,
            Matrix3D const & rhs
            ) {
        Matrix3D res(Matrix3D::zero());

        for (int i = 0; i < N_ROWS; ++i) {
            for (int j = 0; j < N_COLS; ++j) {
                res.set(i, j, lhs.get(i, j) + rhs.get(i, j));
            }
        }

        return res;
    }

    
    Real Matrix3D::det() const {
        Real tmp1 = (get(1, 1) * get(2, 2) - get(1, 2) * get(2, 1)) * get(0, 0);
        Real tmp2 = (get(1, 2) * get(2, 0) - get(1, 0) * get(2, 2)) * get(0, 1);
        Real tmp3 = (get(1, 0) * get(2, 1) - get(1, 1) * get(2, 0)) * get(0, 2);

        return tmp1 + tmp2 + tmp3;
    }

    
    Real Matrix3D::get(int i, int j) const {
        return elems[i][j];
    }

    
    Matrix3D & Matrix3D::inv() {
        Matrix3D res(Matrix3D::inv(*this));
        *this = res;

        return *this;
    }

    
    Matrix3D Matrix3D::inv(Matrix3D const & rhs) {
        Real determinant = rhs.det();

        if (determinant == 0.0) {
            throw Matrix3DNullDeterminantException("Determinant equal to zero. Inversion of matrix impossible");
        }

        Real invDet = 1.0 / determinant;
        Matrix3D res;
        res.set(0, 0, (rhs.get(1, 1) * rhs.get(2, 2) - rhs.get(1, 2) * rhs.get(2, 1)) * invDet);
        res.set(0, 1, (rhs.get(0, 2) * rhs.get(2, 1) - rhs.get(0, 1) * rhs.get(2, 2)) * invDet);
        res.set(0, 2, (rhs.get(0, 1) * rhs.get(1, 2) - rhs.get(0, 2) * rhs.get(1, 1)) * invDet);
        res.set(1, 0, (rhs.get(1, 2) * rhs.get(2, 0) - rhs.get(1, 0) * rhs.get(2, 2)) * invDet);
        res.set(1, 1, (rhs.get(0, 0) * rhs.get(2, 2) - rhs.get(0, 2) * rhs.get(2, 0)) * invDet);
        res.set(1, 2, (rhs.get(0, 2) * rhs.get(1, 0) - rhs.get(0, 0) * rhs.get(1, 2)) * invDet);
        res.set(2, 0, (rhs.get(1, 0) * rhs.get(2, 1) - rhs.get(1, 1) * rhs.get(2, 0)) * invDet);
        res.set(2, 1, (rhs.get(0, 1) * rhs.get(2, 0) - rhs.get(0, 0) * rhs.get(2, 1)) * invDet);
        res.set(2, 2, (rhs.get(0, 0) * rhs.get(1, 1) - rhs.get(0, 1) * rhs.get(1, 0)) * invDet);

        return res;
    }

    
    Matrix3D & Matrix3D::mult(Real rhs) {
        for (int i = 0; i < N_ROWS; ++i) {
            for (int j = 0; j < N_COLS; ++j) {
                set(i, j, get(i, j) * rhs);
            }
        }

        return *this;
    }

    
    Matrix3D Matrix3D::mult(
            Matrix3D const & lhs,
            Real rhs
            ) {
        Matrix3D res(lhs);
        res.mult(rhs);

        return res;
    }

    
    Matrix3D Matrix3D::mult(Matrix3D const & rhs) const {
        Matrix3D res;

        for (int i = 0; i < N_ROWS; ++i) {
            for (int j = 0; j < N_COLS; ++j) {
                res.set(i, j, 0);

                for (int k = 0; k < N_COLS; ++k) {
                    res.set(i, j, res.get(i, j) + get(i, k) * rhs.get(k, j));
                }
            }
        }

        return res;
    }

    
    Vector3D Matrix3D::mult(Vector3D const & rhs) const {
        return Vector3D(
                get(0, 0) * rhs.get(0) + get(0, 1) * rhs.get(1) + get(0, 2) * rhs.get(2),
                get(1, 0) * rhs.get(0) + get(1, 1) * rhs.get(1) + get(1, 2) * rhs.get(2),
                get(2, 0) * rhs.get(0) + get(2, 1) * rhs.get(1) + get(2, 2) * rhs.get(2)
                );
    }

    
    Vector3D Matrix3D::mult(Matrix3D const & lhs, Vector3D const & rhs) {
        return lhs.mult(rhs);
    }

    
    Matrix3D & Matrix3D::orthonorm() {
        Real lengthX = Math<Real>::sqrt(
                get(0, 0) * get(0, 0)
                + get(1, 0) * get(1, 0)
                + get(2, 0) * get(2, 0)
                );

        assert(lengthX != 0.0);

        if (lengthX == 0.0) {
            throw Matrix3DNullColumnException("x_axis is equal to zero");
        }

        Real invLengthX = 1.0 / lengthX;
        set(0, 0, get(0, 0) * invLengthX);
        set(1, 0, get(1, 0) * invLengthX);
        set(2, 0, get(2, 0) * invLengthX);

        Real proj
                = get(0, 0) * get(0, 1)
                + get(1, 0) * get(1, 1)
                + get(2, 0) * get(2, 1);
        set(0, 1, get(0, 1) - get(0, 0) * proj);
        set(1, 1, get(1, 1) - get(1, 0) * proj);
        set(2, 1, get(2, 1) - get(2, 0) * proj);

        Real lengthY = Math<Real>::sqrt(
                get(0, 1) * get(0, 1)
                + get(1, 1) * get(1, 1)
                + get(2, 1) * get(2, 1)
                );

        assert(lengthY != 0);

        if (lengthY == 0.0) {
            throw Matrix3DNullColumnException("y_axis is equal to zero");
        }

        Real invLengthY = (Real) 1.0 / lengthY;
        set(0, 1, get(0, 1) * invLengthY);
        set(1, 1, get(1, 1) * invLengthY);
        set(2, 1, get(2, 1) * invLengthY);

        set(0, 2, get(1, 0) * get(2, 1) - get(2, 0) * get(1, 1));
        set(1, 2, get(2, 0) * get(0, 1) - get(0, 0) * get(2, 1));
        set(2, 2, get(0, 0) * get(1, 1) - get(1, 0) * get(0, 1));

        return *this;
    }

    
    Matrix3D Matrix3D::orthonorm(Matrix3D const & rhs) {
        Matrix3D res(rhs);
        res.orthonorm();

        return res;
    }

    
    void Matrix3D::set(int i, int j, Real val) {
        elems[i][j] = val;
    }

    
    Matrix3D Matrix3D::fromAxisAngle(AxisAngle axisAngle) {
        Vector3D axis = axisAngle.getAxis();
        Real angle = axisAngle.getAngle();
        Real c = Math<Real>::cos(angle);
        Real s = Math<Real>::sin(angle);
        Real t = 1 - Math<Real>::cos(angle);

        Vector3D vec(axis);
        vec.norm();

        Real tXY = t * vec.get(0) * vec.get(1);
        Real tXZ = t * vec.get(0) * vec.get(2);
        Real tYZ = t * vec.get(1) * vec.get(2);
        Real sX = s * vec.get(0);
        Real sY = s * vec.get(1);
        Real sZ = s * vec.get(2);

        Matrix3D res;
        res.set(0, 0, t * vec.get(0) * vec.get(0) + c);
        res.set(0, 1, tXY - sZ);
        res.set(0, 2, tXZ + sY);
        res.set(1, 0, tXY + sZ);
        res.set(1, 1, t * vec.get(1) * vec.get(1) + c);
        res.set(1, 2, tYZ - sX);
        res.set(2, 0, tXZ - sY);
        res.set(2, 1, tYZ + sX);
        res.set(2, 2, t * vec.get(2) * vec.get(2) + c);

        return res;
    }

    
    Matrix3D & Matrix3D::sub(Matrix3D const & rhs) {
        for (int i = 0; i < N_ROWS; ++i) {
            for (int j = 0; j < N_COLS; ++j) {
                set(i, j, get(i, j) - rhs.get(i, j));
            }
        }

        return *this;
    }

    
    Matrix3D Matrix3D::sub(
            Matrix3D const & lhs,
            Matrix3D const & rhs
            ) {
        Matrix3D res;

        for (int i = 0; i < N_ROWS; ++i) {
            for (int j = 0; j < N_COLS; ++j) {
                res.set(i, j, lhs.get(i, j) - rhs.get(i, j));
            }
        }

        return res;
    }


    //Morgan Kaufmann - DIMD game engine design - a practical approach to 
    //real-time computer graphics (T)(586s)Eberly D.H.(2002)

    
    AxisAngle Matrix3D::toAxisAngle() const {
        Real angle = Math<Real>::acos((trace() - 1.0) / 2.0);

        if (angle != 0.0) {
            if (angle != Math<Real>::PI) {
                Vector3D axis(
                        get(2, 1) - get(1, 2),
                        get(0, 2) - get(2, 0),
                        get(1, 0) - get(0, 1)
                        );
                axis.norm();

                return AxisAngle(axis, angle);
            } else {
                Real max = Math<Real>::max(Math<Real>::max(get(0, 0), get(1, 1)), get(2, 2));

                if (get(0, 0) == max) {
                    Real x = Math<Real>::sqrt(get(0, 0) - get(1, 1) - get(2, 2) + 1.0) / 2.0;
                    Real y = get(0, 1) / (2.0 * x);
                    Real z = get(0, 2) / (2.0 * x);

                    return AxisAngle(Vector3D(x, y, z), angle);
                } else {
                    if (get(1, 1) == max) {
                        Real y = Math<Real>::sqrt(get(1, 1) - get(0, 0) - get(2, 2) + 1.0) / 2.0;
                        Real x = get(0, 1) / (2.0 * y);
                        Real z = get(1, 2) / (2.0 * x);

                        return AxisAngle(Vector3D(x, y, z), angle);
                    } else {
                        Real z = Math<Real>::sqrt(get(2, 2) - get(0, 0) - get(1, 1) + 1.0) / 2.0;
                        Real x = get(0, 2) / (2.0 * z);
                        Real y = get(1, 2) / (2.0 * z);

                        return AxisAngle(Vector3D(x, y, z), angle);
                    }
                }
            }

        } else {
            return AxisAngle(Vector3D(1.0, 0.0, 0.0), 0.0);
        }
    }

    Quaternion Matrix3D::toQuaternion() const {
        Quaternion res(0.0, 0.0, 0.0, 0.0);
        Real tr;
        Real s;
        tr = trace();

        if (tr >= 1.0) {
            s = Math<Real>::sqrt(tr + (Real) 1.0);
            res.setW(0.5 * s);
            s = 0.5 / s;
            res.setX((get(2, 1) - get(1, 2)) * s);
            res.setY((get(0, 2) - get(2, 0)) * s);
            res.setZ((get(1, 0) - get(0, 1)) * s);
        } else {
            int i = 0;

            if (get(1, 1) > get(0, 0)) {
                i = 1;

                if (get(2, 2) > get(1, 1)) {
                    i = 2;
                }
            } else {
                if (get(2, 2) > get(0, 0)) {
                    i = 2;
                }
            }

            switch (i) {
                case 0:
                    s = Math<Real>::sqrt((get(0, 0) - (get(1, 1) + get(2, 2))) + 1.0);
                    res.setX(0.5 * s);
                    s = 0.5 / s;
                    res.setY((get(0, 1) + get(1, 0)) * s);
                    res.setZ((get(2, 0) + get(0, 2)) * s);
                    res.setW((get(2, 1) - get(1, 2)) * s);
                    break;

                case 1:
                    s = Math<Real>::sqrt((get(1, 1) - (get(2, 2) + get(0, 0))) + 1.0);
                    res.setY(0.5 * s);
                    s = 0.5 / s;
                    res.setZ((get(1, 2) + get(2, 1)) * s);
                    res.setX((get(0, 1) + get(1, 0)) * s);
                    res.setW((get(0, 2) - get(2, 0)) * s);
                    break;

                case 2:
                    s = Math<Real>::sqrt((get(2, 2) - (get(0, 0) + get(1, 1))) + 1.0);
                    res.setZ(0.5 * s);
                    s = 0.5 / s;
                    res.setX((get(2, 0) + get(0, 2)) * s);
                    res.setY((get(1, 2) + get(2, 1)) * s);
                    res.setW((get(1, 0) - get(0, 1)) * s);
                    break;
            }
        }

        return res;
    }

    
    Real Matrix3D::trace() const {
        return get(0, 0) + get(1, 1) + get(2, 2);
    }

    
    Matrix3D & Matrix3D::transp() {
        Real tmp;

        for (int i = 0; i < N_ROWS; ++i) {
            for (int j = i + 1; j < N_COLS; ++j) {
                tmp = get(i, j);
                set(i, j, get(j, i));
                set(j, i, tmp);
            }
        }

        return *this;
    }

    
    Matrix3D Matrix3D::transp(Matrix3D const & rhs) {
        Matrix3D res(rhs);
        res.transp();

        return res;
    }

    /*if A is a rotation matrix then transp(A) * A = Identity
    The matrix which is the result of transp(A) * A has all its diagonal entries
    equal to 1.0 and all other entries equal to zero
    We compute the product of the transposed matrix of A by A and make the
    tests with a tolerance equal to 2EPS
     */
    
    bool Matrix3D::isRotation() const {
        for (int i = 0; i < Matrix3D::N_ROWS; ++i) {
            for (int j = 0; j < Matrix3D::N_COLS; ++j) {
                Real coef = 0.0;

                for (int k = 0; k < Matrix3D::N_COLS; ++k) {
                    coef += get(i, k) * get(j, k);
                }

                if (i != j) {
                    if (Math<Real>::abs(coef) >= 2.0 * Matrix3D::EPS) {
                        return false;
                    }
                } else {
                    if (Math<Real>::abs(coef - 1.0) >= 2.0 * Matrix3D::EPS) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    
    std::ostream & operator<<(std::ostream & out, Matrix3D const & mat) {
        for (int unsigned i = 0; i < 3; ++i) {
            for (int unsigned j = 0; j < 3; ++j) {
                out << std::right << std::setw(16)
                        << std::setprecision(6) << mat.get(i, j);
            }

            out << "\n";
        }

        return out;
    }

    /*static void main(String[] args) {
            Matrix3D mat;
            std::cout << "mat = " << mat);
            testAxisAngleConversion();
            Matrix3D inertia = Matrix3D::identity().mult(Double.MAX_VALUE);
            std::cout << "inertia = " << inertia);
            Matrix3D inertiaInv = Matrix3D::inv(inertia);
            std::cout << "inertiaInv = " << inertiaInv);
    }*/

    
    void Matrix3D::testAxisAngleConversion() {
        Vector3D axis(0.0, 0.0, 1.0);
        Real angle = Math<Real>::PI / 2.0;
        Matrix3D m1;
        AxisAngle aa(axis, angle);
        m1 = Matrix3D::fromAxisAngle(aa);
        std::cout << "m1 = " << m1 << std::endl;
        Vector3D rot1 = m1.mult(axis);
        std::cout << "rot1 = " << rot1 << std::endl;

        Vector3D normal(
                util::Rand<Real>::getInstance().next(),
                util::Rand<Real>::getInstance().next(),
                util::Rand<Real>::getInstance().next());
        normal.norm();
        std::cout << "normal = " << normal << std::endl;
        Real distance = util::Rand<int>::getInstance().next(100) * util::Rand<Real>::getInstance().next();
        std::cout << "distance = " << distance << std::endl;
        //equation of a plane: nx * x + ny * y + nz * z + d = 0
        // ==> (nx, ny, nz) dot (x, y, z) + d = 0
        // if x1 is known and y1 is known, then the z-coordinate of a point 
        // P (x1, y1, z) belonging to the plane is
        // z = -(nx * x1 + ny * y1 + d) / nz (nz != 0)
        Real x1 = util::Rand<int>::getInstance().next(100) * util::Rand<Real>::getInstance().next();
        Real y1 = util::Rand<int>::getInstance().next(100) * util::Rand<Real>::getInstance().next();
        Real z1 = (-normal.getX() * x1 - normal.getY() * y1 - distance) / normal.getZ();
        Vector3D p1(x1, y1, z1);
        std::cout << "p1 = " << p1 << std::endl;
        std::cout << "p1.dot(normal) + distance = " << (p1.dot(normal) + distance) << std::endl;
        Real x2 = util::Rand<int>::getInstance().next(100) * util::Rand<Real>::getInstance().next();
        Real y2 = util::Rand<int>::getInstance().next(100) * util::Rand<Real>::getInstance().next();
        Real z2 = (-normal.getX() * x2 - normal.getY() * y2 - distance) / normal.getZ();
        Vector3D p2(x2, y2, z2);
        std::cout << "p2 = " << p2 << std::endl;
        std::cout << "p2.dot(normal) + distance = " << (p2.dot(normal) + distance) << std::endl;
        Vector3D a1(p1);
        a1.sub(p2);
        a1.norm();
        std::cout << "a1 = p1 - p2" << std::endl;
        std::cout << "a1 = " << a1 << std::endl;
        std::cout << "a1.dot(normal) = " << a1.dot(normal) << std::endl;
        Vector3D a2(normal);
        std::cout << "a2 = Vector3(normal)" << std::endl;
        std::cout << "a2 = " << a2 << std::endl;
        Vector3D a3 = a1.cross(a2);
        std::cout << "a3 = a1.cross(a2)" << std::endl;
        std::cout << "a3 = " << a3 << std::endl;

        std::cout << "a1 = " << a1 << std::endl;
        ;
        std::cout << "a2 = " << a2 << std::endl;
        std::cout << "a3 = " << a3 << std::endl;

        std::cout << "a1.dot(a2) = " << a1.dot(a2) << std::endl;
        std::cout << "a1.dot(a3) = " << a1.dot(a3) << std::endl;
        std::cout << "a2.dot(a3) = " << a2.dot(a3) << std::endl;
        std::cout << "a1.cross(a2) = " << a1.cross(a2) << std::endl;
        std::cout << "a2.cross(a3) = " << a2.cross(a3) << std::endl;
        std::cout << "a3.cross(a1) = " << a3.cross(a1) << std::endl;

        std::cout << "a1 = " << a1 << std::endl;
        std::cout << "a1.length() = " << a1.length() << std::endl;
        std::cout << "a2 = " << a2 << std::endl;
        std::cout << "a2.length() = " << a2.length() << std::endl;
        std::cout << "a3 = " << a3 << std::endl;
        std::cout << "a3.length() = " << a3.length() << std::endl;
        Matrix3D mat(
                a1.getX(), a2.getX(), a3.getX(),
                a1.getY(), a2.getY(), a3.getY(),
                a1.getZ(), a2.getZ(), a3.getZ()
                );
        std::cout << "mat =\n" << mat << std::endl;
        std::cout << "mat * transp(mat) =\n" << mat.mult(Matrix3D::transp(mat)) << std::endl;
        std::cout << "mat.isRotation() ? " << mat.isRotation() << std::endl;
        AxisAngle axisAngle = mat.toAxisAngle();
        std::cout << "axisAngle = " << axisAngle << std::endl;
        Matrix3D m2;
        m2.fromAxisAngle(axisAngle);
        std::cout << "m2.fromAxisAngle(axisAngle.getAxis(), axisAngle.getAngle());" << std::endl;
        std::cout << "m2 = " << m2 << std::endl;

    }

    void Matrix3D::testInvert() {
		Matrix3D m4;

		for (int i = 0; i < N_ROWS; ++i) {
				for (int j = 0; j < N_COLS; ++j) {
						m4.set(i, j, util::Rand<int>::getInstance().next(100) * util::Rand<Real>::getInstance().next());
				}
		}

		std::cout << "m4 = " << m4;
		Matrix3D m5 = Matrix3D::inv(m4);
		std::cout << "Matrix33 m5 = Matrix33.invert(m4);" << "\n";
		std::cout << "m5 = " << m5 << "\n";
		std::cout << "m4.mult(m5) = " << m4.mult(m5) << "\n";
		Matrix3D res = Matrix3D::sub(Matrix3D::identity(), m4.mult(m5));
		std::cout << "Matrix33::sub(Matrix33::identity(), m4.mult(m5)) = "
						<< res << "\n";
		std::cout << "m4.mult(m5).equals(Matrix33.identity() ? "
						<< m4.mult(m5).equalsWithTol(Matrix3D::identity(), (Real)1.0e-6) << "\n";
    }

    void Matrix3D::testIsRotation() {
		Vector3D normal(
						util::Rand<Real>::getInstance().next(),
						util::Rand<Real>::getInstance().next(),
						util::Rand<Real>::getInstance().next());
		normal.norm();
		std::cout << "normal = " << normal << "\n";
		double distance = util::Rand<int>::getInstance().next(100) * util::Rand<Real>::getInstance().next();
		std::cout << "distance = " << distance << "\n";
		double x1 = util::Rand<int>::getInstance().next(100) * util::Rand<Real>::getInstance().next();
		double y1 = util::Rand<int>::getInstance().next(100) * util::Rand<Real>::getInstance().next();
		double z1 = (-normal.getX() * x1 - normal.getY() * y1 - distance) / normal.getZ();
		Vector3D p1(x1, y1, z1);
		std::cout << "p1 = " << p1 << "\n";
		std::cout << "p1.dot(normal) + distance = " << (p1.dot(normal) + distance) << "\n";
		double x2 = util::Rand<int>::getInstance().next(100) * util::Rand<Real>::getInstance().next();
		double y2 = util::Rand<int>::getInstance().next(100) * util::Rand<Real>::getInstance().next();
		double z2 = (-normal.getX() * x2 - normal.getY() * y2 - distance) / normal.getZ();
		Vector3D p2(x2, y2, z2);
		std::cout << "p2 = " << p2 << "\n";
		std::cout << "p2.dot(normal) + distance = " << (p2.dot(normal) + distance) << "\n";
		Vector3D a1(p1);
		a1.sub(p2);
		a1.norm();
		std::cout << "a1 = p1 - p2" << "\n";
		std::cout << "a1 = " << a1 << "\n";;
		std::cout << "a1.dot(normal) = " << a1.dot(normal) << "\n";
		Vector3D a2(normal);
		std::cout << "a2 = Vector3(normal)" << "\n";
		std::cout << "a2 = " << a2 << "\n";
		Vector3D a3 = a1.cross(a2);
		std::cout << "a3 = a1.cross(a2)" << "\n";
		std::cout << "a3 = " << a3 << "\n";

		std::cout << "a1 = " << a1 << "\n";
		std::cout << "a2 = " << a2 << "\n";
		std::cout << "a3 = " << a3 << "\n";

		std::cout << "a1.dot(a2) = " << a1.dot(a2) << "\n";
		std::cout << "a1.dot(a3) = " << a1.dot(a3) << "\n";
		std::cout << "a2.dot(a3) = " << a2.dot(a3) << "\n";
		std::cout << "a1.cross(a2) = " << a1.cross(a2) << "\n";
		std::cout << "a2.cross(a3) = " << a2.cross(a3) << "\n";
		std::cout << "a3.cross(a1) = " << a3.cross(a1) << "\n";

		std::cout << "a1 = " << a1 << "\n";
		std::cout << "a1.length() = " << a1.length() << "\n";
		std::cout << "a2 = " << a2 << "\n";
		std::cout << "a2.length() = " << a2.length() << "\n";
		std::cout << "a3 = " << a3 << "\n";
		std::cout << "a3.length() = " << a3.length() << "\n";
		Matrix3D mat(
			a1.getX(), a2.getX(), a3.getX(),
			a1.getY(), a2.getY(), a3.getY(),
			a1.getZ(), a2.getZ(), a3.getZ()
		);
		std::cout << "mat =\n" << mat << "\n";
		std::cout << "mat * transp(mat) =\n" << mat.mult(Matrix3D::transp(mat)) << "\n";
		std::cout << "mat.isRotation() ? " << mat.isRotation() << "\n";
    }

    void Matrix3D::testOrthonormalize() {
        Matrix3D m3;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                m3.set(i, j, util::Rand<Real>::getInstance().next());
            }
        }

        std::cout << "Random matrix m3 =\n" << m3 << std::endl;
        m3.orthonorm();
        std::cout << "m3.orthonormalize();" << std::endl;
        std::cout << "m3 =\n" << m3 << std::endl;
        std::cout << "m3.isRotation() ? " << m3.isRotation() << std::endl;
        std::cout << "Matrix33.invert(m3).mult(m3) =\n"
                << Matrix3D::inv(m3).mult(m3) << std::endl;
        std::cout << "m3.det() = " << m3.det() << std::endl;
        std::cout << "m3.equals(m3) ? " << m3.equalsWithTol(m3, 1.0e-6) << std::endl;
    }
}