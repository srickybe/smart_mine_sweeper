#include "Intersection.h"
#include <iostream>
#include "AxisAlignedBox3D.h"
#include "IllegalArgumentException.h"
#include "LineSegment.h"
#include "Math.h"
#include "Matrix3D.h"
#include "OrientedBox3D.h"
#include "Plane.h"
#include "Sphere.h"
#include "UnsupportedOperationException.h"

namespace ngn {

	Intersection::Result::Result(bool isPositive) {
	    positive_ = isPositive;
	    time_ = std::numeric_limits<Real>::max();
	}
	
	Intersection::Result::Result(bool isPositive, Real time) {
	    positive_ = isPositive;
	    time_ = time;
	}

	bool Intersection::Result::isPositive()const {
        return positive_;
	}

	Real Intersection::Result::getTime()const {
	    return time_;
	}
	
	std::ostream & operator << (std::ostream & out, Intersection::Result const & ir) {
        out << "positive ?" << (ir.isPositive() ? "true": "false") << "\n";

        return out;
	}
	
	Intersection::Result Intersection::lineSegmentIntersectSphere(LineSegment const & lineSegment, Sphere const & sphere) {
		Vector3D Q = Vector3D::sub(lineSegment.getOrigin(), sphere.getCenter());
		Real a0 = Q.dot(Q) - sphere.getRadius() * sphere.getRadius();
		
		if (a0 <= 0) {
			//The origin of the line segment is inside or on the surface of the sphere
			return Intersection::Result(true, 0.0);
		}
		// else the origin of the line segment is outside the sphere
		Real a1 = lineSegment.getDirection().dot(Q);
		
		if (a1 >= 0) {
			//the cente of the sphere is "behind" the line segment
			return Intersection::Result(false, 0.0);
		}
		
		Real val = a1 * a1 - a0;
		bool hasRealRoot = val >= 0;
		
		return Intersection::Result(hasRealRoot, 0.0);
	}
	
	/*
	 * Based on Morgan Kaufmann - 3D game engine design - a practical approach to real-time computer graphics (T)(586s)Eberly D.H.(2002)
	 * chap 6, page 208 
	*/
    Intersection::Result Intersection::orientedBox3DIntersectOrientedBox3D(OrientedBox3D const & box1, OrientedBox3D const & box2) {
		Matrix3D A = box1.getOrientation();
		Matrix3D B = box2.getOrientation();
		Matrix3D C;
		Vector3D D = Vector3D::sub(box2.getCenter(), box1.getCenter());
		Vector3D AiD;
		// Is Ai (0 <= i <= 2) a separating axis ?
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				C.set(i, j, A.getCol(i).dot(B.getCol(j)));
			}
			
			Real R0 = box1.getHalfExtents().get(i);
			Real R1 = box2.getHalfExtents().dot(Vector3D::abs(C.getRow(i)));
			AiD.set(i, A.getCol(i).dot(D));
			Real R = Math<Real>::abs(AiD.get(i));
			
			if (R > R0 + R1) {
				return Intersection::Result(true, 0.0);
			}
		}
		
		Vector3D BiD;
		// Is Bi (0 <= i <= 2) a separating axis ?
		for (int i = 0; i < 3; ++i) {
			Real R0 = box1.getHalfExtents().dot(Vector3D::abs(C.getCol(i)));
			Real R1 = box2.getHalfExtents().get(i);
			BiD.set(i, B.getCol(i).dot(D)); 
			Real R = Math<Real>::abs(BiD.get(i));
			
			if (R > R0 + R1) {
				return Intersection::Result(true, 0.0);
			}
		}
		
		Real a0 = box1.getHalfExtents().getX();
		Real a1 = box1.getHalfExtents().getY();
		Real a2 = box1.getHalfExtents().getZ();
		Real b0 = box2.getHalfExtents().getX();
		Real b1 = box2.getHalfExtents().getY();
		Real b2 = box2.getHalfExtents().getZ();
		Matrix3D Ca = Matrix3D::abs(C);
		//Is A0 x B0 a separating axis ?
		{
			Real R0 = a1 * Ca.get(2, 0) + a2 * Ca.get(1, 0);
			Real R1 = b1 * Ca.get(0, 2) + b2 * Ca.get(0, 1);
			Real R = Math<Real>::abs(C.get(1, 0) * AiD.get(2) - C.get(2, 0) * AiD.get(1));
			
			if (R > R0 + R1) {
				return Intersection::Result(true, 0.0);
			}
		}
		
		//Is A0 x B1 a separating axis ?
		{
			Real R0 = a1 * Ca.get(2, 1) + a2 * Ca.get(1, 1);
			Real R1 = b0 * Ca.get(0, 2) + b2 * Ca.get(0, 0);
			Real R = Math<Real>::abs(C.get(1, 1) * AiD.get(2) - C.get(2, 1) * AiD.get(1));
			
			if (R > R0 + R1) {
				return Intersection::Result(true, 0.0);
			}
		}
		
		//Is A0 x B2 a separating axis ?
		{
			Real R0 = a1 * Ca.get(2, 2) + a2 * Ca.get(1, 2);
			Real R1 = b0 * Ca.get(0, 1) + b1 * Ca.get(0, 0);
			Real R = Math<Real>::abs(C.get(1, 2) * AiD.get(2) - C.get(2, 2) * AiD.get(1));
			
			if (R > R0 + R1) {
				return Intersection::Result(true, 0.0);
			}
		}
		
		//Is A1 x B0 a separating axis ?
		{
			Real R0 = a0 * Ca.get(2, 0) + a2 * Ca.get(0, 0);
			Real R1 = b1 * Ca.get(1, 2) + b2 * Ca.get(1, 1);
			Real R = Math<Real>::abs(C.get(2, 0) * AiD.get(0) - C.get(0, 0) * AiD.get(2));
			
			if (R > R0 + R1) {
				return Intersection::Result(true, 0.0);
			}
		}
		
		//Is A1 x B1 a separating axis ?
		{
			Real R0 = a0 * Ca.get(2, 1) + a2 * Ca.get(0, 1);
			Real R1 = b0 * Ca.get(1, 2) + b2 * Ca.get(1, 0);
			Real R = Math<Real>::abs(C.get(2, 1) * AiD.get(0) - C.get(0, 1) * AiD.get(2));
			
			if (R > R0 + R1) {
				return Intersection::Result(true, 0.0);
			}
		}
		
		//Is A1 x B2 a separating axis ?
		{
			Real R0 = a0 * Ca.get(2, 2) + a2 * Ca.get(0, 2);
			Real R1 = b0 * Ca.get(1, 1) + b1 * Ca.get(1, 0);
			Real R = Math<Real>::abs(C.get(2, 2) * AiD.get(0) - C.get(0, 2) * AiD.get(2));
			
			if (R > R0 + R1) {
				return Intersection::Result(true, 0.0);
			}
		}
		
		//Is A2 x B0 a separating axis ?
		{
			Real R0 = a0 * Ca.get(1, 0) + a1 * Ca.get(0, 0);
			Real R1 = b1 * Ca.get(2, 2) + b2 * Ca.get(2, 1);
			Real R = Math<Real>::abs(C.get(0, 0) * AiD.get(1) - C.get(1, 0) * AiD.get(0));
			
			if (R > R0 + R1) {
				return Intersection::Result(true, 0.0);
			}
		}
		
		//Is A2 x B1 a separating axis ?
		{
			Real R0 = a0 * Ca.get(1, 1) + a1 * Ca.get(0, 1);
			Real R1 = b0 * Ca.get(2, 2) + b2 * Ca.get(2, 0);
			Real R = Math<Real>::abs(C.get(0, 1) * AiD.get(1) - C.get(1, 1) * AiD.get(0));
			
			if (R > R0 + R1) {
				return Intersection::Result(true, 0.0);
			}
		}
		
		//Is A2 x B2 a separating axis ?
		{
			Real R0 = a0 * Ca.get(1, 2) + a1 * Ca.get(0, 2);
			Real R1 = b0 * Ca.get(2, 1) + b1 * Ca.get(2, 0);
			Real R = Math<Real>::abs(C.get(0, 2) * AiD.get(1) - C.get(1, 2) * AiD.get(0));
			
			if (R > R0 + R1) {
				return Intersection::Result(true, 0.0);
			}
		}
		
        return Intersection::Result(false, std::numeric_limits<Real>::max());
    }

    
    Intersection::Result Intersection::orientedBox3DIntersectPlane(OrientedBox3D const & box1, Plane const & plane2) {
        throw UnsupportedOperationException("");
    }

    
    Intersection::Result Intersection::orientedBox3DIntersectSphere(OrientedBox3D const & box1, Sphere const & sphere2) {
        Vector3D dist = Vector3D::sub(sphere2.getCenter(), box1.getCenter());
        Vector3D localDist = Matrix3D::transp(box1.getOrientation()).mult(dist);

        for (int i = 0; i < 3; ++i) {
            if (Math<Real>::abs(localDist.get(i)) > box1.getHalfExtents().get(i) + sphere2.getRadius()) {
                return Intersection::Result(false);
            }
        }

        return Intersection::Result(true);
    }


    Intersection::Result Intersection::axisAlignedBox3DIntersectSphere(AxisAlignedBox3D const & box1, Sphere const & sphere2) {
		Vector3D dist = Vector3D::sub(sphere2.getCenter(), box1.getCenter());
		
		for (int i = 0; i < 3; ++i) {
			Real delta = Math<Real>::abs(dist.get(i));
			Real sum = sphere2.getRadius() + box1.getHalfExtents().get(i);
				
			if (delta > sum) {
				return Intersection::Result(false);
			}
		}
		
		return Intersection::Result(true);
	}
	
    Intersection::Result Intersection::planeIntersectPlane(Plane const & plane1, Plane const & plane2) {
        throw UnsupportedOperationException("");
    }

    
    Intersection::Result Intersection::planeIntersectSphere(Plane const & plane, Sphere const & sphere) {
        Real distance = plane.distanceFromPoint(sphere.getCenter());

        return Intersection::Result(distance <= sphere.getRadius());
    }

    
    Intersection::Result Intersection::sphereIntersectSphere(Sphere const & sphere1, Sphere const & sphere2) {
        Vector3D distance(sphere1.getCenter());
        distance.sub(sphere2.getCenter());

        return Intersection::Result(distance.length() <= sphere2.getRadius() + sphere1.getRadius());
    }
}