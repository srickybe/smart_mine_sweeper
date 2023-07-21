#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "Real.h"
#include <string>

namespace ngn {
	class Vector3D;

    class AxisAngle;
	class Matrix2D;
	class Quaternion;
    class Vector3D;
    
	class Matrix3DNullDeterminantException{
	public:
		Matrix3DNullDeterminantException(std::string const & message);
		
	private:
		std::string message_;
	};
	
	class Matrix3DNullColumnException {
	public:
		Matrix3DNullColumnException(std::string const & message);
		
	private:
		std::string message_;
	};
	
    class Matrix3D {
    public:
		static Matrix3D abs(Matrix3D const & rhs);
        static Matrix3D add(Matrix3D const & lhs, Matrix3D const & rhs);
        static Matrix3D fromAxisAngle(AxisAngle axisAngle);
        static Matrix3D identity();
        static Matrix3D inv(Matrix3D const & rhs);
        static Matrix3D mult(Matrix3D const & lhs, Real rhs);
        static Vector3D mult(Matrix3D const &, Vector3D const &);
        static Matrix3D orthonorm(Matrix3D const & rhs);
        static Matrix3D sub(Matrix3D const & lhs, Matrix3D const & rhs);
        static Matrix3D transp(Matrix3D const & rhs);
        static Matrix3D zero();
		
		static void testAxisAngleConversion();
		static void testInvert();
		static void testIsRotation();
		static void testOrthonormalize();

        Matrix3D();
        Matrix3D(Matrix3D const & m);
        Matrix3D
        (
			Real m00, Real m01, Real m02,
			Real m10, Real m11, Real m12,
			Real m20, Real m21, Real m22
		);
		Matrix3D(Matrix2D const & m);

        Real get(int i, int j) const;
        Vector3D getCol(int j) const;
        Vector3D getRow(int i) const;

		Matrix3D & abs();
        Matrix3D & add(Matrix3D const & rhs);
        bool equalsWithTol(Matrix3D const & rhs, Real tol)const;
        bool isRotation() const;
        Real det() const;
        Matrix3D & inv();
        Matrix3D & mult(Real rhs);
        Matrix3D mult(Matrix3D const & rhs) const;
        Vector3D mult(Vector3D const & rhs)const;
        Matrix3D & orthonorm();
        void set(int i, int j, Real val);
        Matrix3D & sub(Matrix3D const & rhs);
        AxisAngle toAxisAngle()const;
        Quaternion toQuaternion() const;
        Real trace() const;
        Matrix3D & transp();

    private:
        Real elems[3][3];

        static const Real EPS;
        static const int N_ROWS;
        static const int N_COLS;
    };

    std::ostream & operator<<(std::ostream &, Matrix3D const &);
}

#endif // MATRIX3D_H