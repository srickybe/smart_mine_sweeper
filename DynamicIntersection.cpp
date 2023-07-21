#include "DynamicIntersection.h"
#include <iostream>
#include <limits>
#include "DynamicPlane.h"
#include "DynamicSphere.h"
#include "IllegalArgumentException.h"
#include "Math.h"

namespace ngn {
	
	DynamicIntersection::Result::Result(bool isPositive) {
	    positive_ = isPositive;
	    time_ = std::numeric_limits<Real>::max();
	}
	
	DynamicIntersection::Result::Result(bool isPositive, Real time) {
	    positive_ = isPositive;
	    time_ = time;
	}

	bool DynamicIntersection::Result::isPositive()const {
        return positive_;
	}

	Real DynamicIntersection::Result::getTime()const {
	    return time_;
	}
	
	std::ostream & operator << (std::ostream & out, DynamicIntersection::Result const & ir) {
        out << "positive ?" << (ir.isPositive() ? "true": "false") << "\n";

        return out;
	}
	
	DynamicIntersection::Result
	DynamicIntersection::planeIntersectSphere(
		DynamicPlane const & plane,
		DynamicSphere const & sphere
	)
	{
        Vector3D dv = Vector3D::sub(sphere.getLinearVelocity(), plane.getLinearVelocity());
        Real a = dv.dot(plane.getNormal());

        if (a > 0) {//sphere getting away from the plane
            return DynamicIntersection::Result(false, std::numeric_limits<Real>::max());

        } else if (a < 0) {//sphere getting closer to the plane
            Real b = plane.distanceFromPoint(sphere.getCenter()) - sphere.getRadius();

            if (b > 0) {//sphere above the plane at time t = 0
				return DynamicIntersection::Result(true, -b / a);

            } else {//sphere intersecting the plane or below the plane at time t = 0
				return DynamicIntersection::Result(true, (Real)0.0);

            }
        } else {//sphere immobile or moving in a direction parallel to the plane
            Real b = plane.distanceFromPoint(sphere.getCenter()) - sphere.getRadius();

            if (b >= 0) {//sphere above the plane or touching permanently
				return DynamicIntersection::Result(false, (Real)0.0);

            } else {//sphere intersecting the plane or below the plane at time t = 0
				std::string message = "sphere intersecting the plane ";
				message += "or below the plane at time t = 0\n";
                throw IllegalArgumentException(message);
                //return 0.0;
            }
        }
	}
	
	DynamicIntersection::Result 
	DynamicIntersection::sphereIntersectSphere(
		DynamicSphere const & sphere1, 
		DynamicSphere const & sphere2
	) 
	{
        Vector3D dv = Vector3D::sub(sphere2.getLinearVelocity(), sphere1.getLinearVelocity());
        Vector3D dx = Vector3D::sub(sphere2.getCenter(), sphere1.getCenter());
        Real a = dv.dot(dv);
        Real b = 2.0 * dx.dot(dv);
        Real radiusSumSquared = Math<Real>::pow((sphere1.getRadius() + sphere2.getRadius()), 2);
        Real c = dx.dot(dx) - radiusSumSquared;

        if (c > 0) {
            if (a == 0) {
                return DynamicIntersection::Result(false, std::numeric_limits<Real>::max());

            } else if (b >= 0) {
                return DynamicIntersection::Result(false, std::numeric_limits<Real>::max());

            } else {
                //b < 0
                Real delta = b * b - 4 * a * c;

                if (delta < 0) {
                    return DynamicIntersection::Result(false, std::numeric_limits<Real>::max());

                } else if (delta > 0) {
                    Real time = (-b - Math<Real>::sqrt(delta)) / (2 * a);

                    return DynamicIntersection::Result(true, time);
                } else {
                    Real time = -b / (2 * a);

                    return DynamicIntersection::Result(true, time);
                }
            }
        } else if (c == 0) {
            if (b >= 0) {
                return DynamicIntersection::Result(false, std::numeric_limits<Real>::max());

            } else {
                Real time = 0.0;

                return DynamicIntersection::Result(true, time);
            }
        } else {
            if (b >= 0) {
                return DynamicIntersection::Result(false, std::numeric_limits<Real>::max());

            } else {
                Real time = 0.0;

                return DynamicIntersection::Result(true, time);
            }
        }
	}
}