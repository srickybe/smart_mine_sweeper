/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author ricky
 */

#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <iomanip>
#include "AxisAngle.h"
#include "Math.h"
#include "Matrix3D.h"
#include "Rand.h"
#include "Real.h"
#include "UnsupportedOperationException.h"

namespace ngn {

    class AxisAngle;
    class Matrix3D;
    class Vector3D;
    void testToRotationMatrix();
    void test();

    class Quaternion {
    public:
        static Quaternion add(Quaternion const & lhs, Quaternion const & rhs);
        static Quaternion conj(Quaternion const & rhs);
        static Quaternion fromAxisAngle(AxisAngle const & axisAngle);
        static Quaternion identity();
        static Quaternion invert(Quaternion const & rhs);
        static Quaternion mult(Quaternion const & lhs, Real rhs);
        static Quaternion negate(Quaternion const & rhs);
        static Quaternion norm(Quaternion const & rhs);
        static Quaternion zero();

        Quaternion();
        Quaternion(Quaternion const & rhs);
        Quaternion(Real fW, Real fX, Real fY, Real fZ);

        void setX(Real x);
        void setY(Real y);
        void setZ(Real z);
        void setW(Real w);
        void set(int i, Real val);

        Real getX() const;
        Real getY() const;
        Real getZ() const;
        Real getW() const;
        Real get(int i) const;

        Quaternion & add(Quaternion const & rhs);
        Quaternion & conj();
        Quaternion & invert();
        bool isUnit() const;
        Real length() const;
        Real lengthSquared() const;
        Quaternion & mult(Real rhs);
        Quaternion mult(Quaternion const & rhs) const;
        Quaternion & negate();
        Quaternion & norm();
        AxisAngle toAxisAngle() const;
        Matrix3D toRotationMatrix() const;

    private:
        Real cmp[4];
        static Real const EPS;
    };

    
    std::ostream & operator<<(
            std::ostream & out,
            Quaternion const & q
            );

    ////////////////////////////////////////////////////////////////////////
}

#endif // QUATERNION_H
