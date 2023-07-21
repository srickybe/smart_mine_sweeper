#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iosfwd>
#include "Real.h"

namespace ngn {

	class AxisAlignedBox3D;
	class LineSegment;
	class OrientedBox3D;
	class Plane;
    class Sphere;
	
    class Intersection {
    public:
		class Result {
		public:
			Result(bool isPositive);
			Result(bool isPositive, Real time);

			bool isPositive()const;
			Real getTime()const;

		private:
			bool positive_;
			Real time_;
		};
			
		
		static Result axisAlignedBox3DIntersectSphere(AxisAlignedBox3D const & box1, Sphere const & sphere2);
		static Result lineSegmentIntersectSphere(LineSegment const & lineSegment, Sphere const & sphere);
		static Result orientedBox3DIntersectOrientedBox3D(OrientedBox3D const & box1, OrientedBox3D const & box2);
        static Result orientedBox3DIntersectPlane(OrientedBox3D const & box1, Plane const & plane2);
        static Result orientedBox3DIntersectSphere(OrientedBox3D const & box1, Sphere const & sphere2);
        static Result planeIntersectPlane(Plane const & plane1, Plane const & plane2);
        static Result planeIntersectSphere(Plane const & plane, Sphere const & sphere);
        static Result sphereIntersectSphere(Sphere const & sphere1, Sphere const & sphere2);
    };

	std::ostream & operator << (std::ostream & out, Intersection::Result const & ir);
	
    ///////////////////////////////////////////////////////////////////////////////////////////////

}

#endif // INTERSECTION_H