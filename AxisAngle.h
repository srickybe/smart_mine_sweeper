#ifndef AXIS_ANGLE_H
#define AXIS_ANGLE_H

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author ricky
 */

#include <iosfwd>
#include "Real.h"
#include "Vector3D.h"

namespace ngn {

    class AxisAngle {
    public:
        AxisAngle(Vector3D const & axis, Real angle);

        Vector3D const & getAxis() const;
        Real getAngle() const;

        void setAxis(Vector3D const & axis);
        void setAngle(Real angle);

        std::string toString() const;

    private:
        Vector3D axis;
        Real angle;
    };

    
    std::ostream & operator<<(std::ostream & out, AxisAngle const & aa);

    ////////////////////////////////////////////////////////////////////////
}

#endif // AXIS_ANGLE_H
