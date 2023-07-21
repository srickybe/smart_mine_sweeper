#ifndef DYNAMIC_INTERSECTION_H
#define DYNAMIC_INTERSECTION_H

#include <iosfwd>
#include "Real.h"

namespace ngn {
	
	class DynamicPlane;
	class DynamicSphere;
	
	class DynamicIntersection {
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
		
		static
		DynamicIntersection::Result
		planeIntersectSphere(
			DynamicPlane const & plane,
			DynamicSphere const & sphere
		);
		
		static 
		DynamicIntersection::Result 
		sphereIntersectSphere(
			DynamicSphere const & sphere1, 
			DynamicSphere const & sphere2
		);
	};
	
	std::ostream & operator << (std::ostream & out, DynamicIntersection::Result const & ir);
}

#endif // DYNAMIC_INTERSECTION_H