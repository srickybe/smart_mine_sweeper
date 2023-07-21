#ifndef COMPONENTS_INTERVALS_ALONG_AXES_H
#define COMPONENTS_INTERVALS_ALONG_AXES_H

#include "Real.h"
#include "Vector3D.h"
#include <vector>

namespace ngn {

    class Matrix3D;
    class Vector3D;

    /*void components_intervals_along_axes(
		std::vector<Vector3D> const &, 
		Matrix3D const &, 
		Vector3D &, 
		Vector3D &
	);*/
	
	class ComputeComponentsIntervalsAlongAxes {
	public:
		class Result {
		public:
			Result() :
				min_(Vector3D::zero()),
				max_(Vector3D::zero())
			{
				
			}
			
			Result(Vector3D const & min, Vector3D const & max) :
				min_(min),
				max_(max)
			{
				
			}
			
			Vector3D const & getMin() const {
				return min_;
			}
			
			Vector3D const & getMax() const {
				return max_;
			}
			
		private:
			Vector3D min_;
			Vector3D max_;
		};

		ComputeComponentsIntervalsAlongAxes();
		
		Result operator()(
			std::vector<Vector3D> const & vertices, 
			Matrix3D const & axes
		);
	};
    ////////////////////////////////////////////////////////////////////////

}

#endif // COMPONENTS_INTERVALS_ALONG_AXES_H