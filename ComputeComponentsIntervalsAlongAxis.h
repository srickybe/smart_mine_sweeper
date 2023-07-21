#ifndef COMPUTE_COMPONENTS_INTERVALS_ALONG_AXIS_H
#define COMPUTE_COMPONENTS_INTERVALS_ALONG_AXIS_H

#include <vector>
#include "Real.h"
#include "Vector3D.h"

namespace ngn {
	
    /*void components_intervals_along_axes(
		std::vector<Vector3D> const &, 
		Vector3D const &, 
		Real &, 
		Real &
	);*/
	
	class ComputeComponentsIntervalsAlongAxis {
	public:
		class Result {
		public:
			Result() :
				min_(0.0),
				max_(0.0)
			{
				
			}
			
			Result(Real min, Real max) :
				min_(min),
				max_(max)
			{
				
			}
			
			Real getMin() const {
				return min_;
			}
			
			Real getMax() const {
				return max_;
			}
			
		private:
			Real min_;
			Real max_;
		};
		
		ComputeComponentsIntervalsAlongAxis();
		
		Result operator()(
			std::vector<Vector3D> const & vertices, 
			Vector3D const & axis
		);
	};
	
}

#endif // COMPUTE_COMPONENTS_INTERVALS_ALONG_AXIS_H