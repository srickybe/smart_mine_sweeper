#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <iostream>
#include "Real.h"

namespace ngn {

	class Vector2D;
	
    class Matrix2D {        
    public:
        class Matrix2DNullDeterminantException {
        public:

            Matrix2DNullDeterminantException(std::string const & message) {
                message_ = message;
            }

        private:
            std::string message_;
        };

        class Matrix2DNullColumnException {
        public:

            Matrix2DNullColumnException(std::string const & message) {
                message_ = message;
            }

        private:
            std::string message_;
        };
        
        class Matrix2DNotRotationException {
        public:

            Matrix2DNotRotationException(std::string const & message) {
                message_ = message;
            }

        private:
            std::string message_;
        };
        
        ////////////////////////////////////////////////////////////////////////
        
        static Matrix2D add(Matrix2D const & lhs, Matrix2D const & rhs);
        static Matrix2D fromAngle(Real angle);
        static Matrix2D identity();
        static Matrix2D inv(Matrix2D const & rhs);
        static Matrix2D mult(Matrix2D const & lhs, Real rhs);
        static Matrix2D orthonorm(Matrix2D const & rhs);
        static Matrix2D star(Real angularVelocity, Matrix2D const & orient);
        static Matrix2D sub(Matrix2D const & lhs, Matrix2D const & rhs);
        static Matrix2D transp(Matrix2D const & rhs);
        static Matrix2D zero();

        Matrix2D();
        Matrix2D(Matrix2D const & m);
        Matrix2D(Real m00, Real m01, Real m10, Real m11);
        bool equals(Matrix2D const & rhs, Real tol)const;
        Vector2D getColumn(int j)const;
        Vector2D getRow(int i)const;
        Matrix2D & add(Matrix2D const & rhs);
        Real det()const;
        Real get(int i, int j)const;
        Matrix2D & inv();
        Matrix2D & mult(Real rhs);
        Matrix2D mult(Matrix2D const & rhs)const;
        Vector2D mult(Vector2D const & rhs)const;
        Matrix2D & orthonorm();
        void set(int i, int j, Real val);
        Matrix2D & sub(Matrix2D const & rhs);
        Real toAngle()const;
        Matrix2D & transp();
        bool isRotation(Real tol)const;

    private:
        static int const DIM = 2;
        Real elems[DIM][DIM];
    };

    
    std::ostream & operator<<(std::ostream & out, Matrix2D const & mat);
    
    ////////////////////////////////////////////////////////////////////////////////
}

#endif /* MATRIX2D_H */

