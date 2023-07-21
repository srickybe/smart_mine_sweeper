#include "AxisAngle.h"
#include <iostream>
#include "IllegalArgumentException.h"

namespace ngn {
	
	AxisAngle::AxisAngle(Vector3D const & vec, Real ang) {
        setAxis(vec);
        setAngle(ang);
    }

    
    Vector3D const & AxisAngle::getAxis() const {
        return axis;
    }

    
    Real AxisAngle::getAngle() const {
        return angle;
    }

    
    void AxisAngle::setAxis(Vector3D const & vec) {
		Real tol = 1.0e-6;
		
        if (vec.isUnit(tol)) {
            axis = vec;
        } else {
            std::cout << "axis(" << vec << ") is not unit long\n";
            std::cout << "axis.length() = " << axis.length() << "\n";
			std::string message = "void AxisAngle::setAxis(Vector3D const & vec)";
			message += ": vec is not unit long\n";
            throw IllegalArgumentException(message);
        }
    }

    
    void AxisAngle::setAngle(Real ang) {
        angle = ang;
    }

    
    std::ostream & operator<<(std::ostream & out, AxisAngle const & aa) {
        out << "axis =\t" << aa.getAxis() << std::endl;
        out << "angle=\t" << aa.getAngle() << std::endl;

        return out;
    }
}