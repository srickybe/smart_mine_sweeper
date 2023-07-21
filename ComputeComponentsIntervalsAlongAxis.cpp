#include "ComputeComponentsIntervalsAlongAxis.h"
#include <cassert>

namespace ngn {
	
    /*void components_intervals_along_axes(
		std::vector<Vector3D> const & vertices, 
		Vector3D const & axis, 
		Real & min, 
		Real & max
	) {
        assert(!vertices.empty());

        Real adot = min = max = 0;

        for (int unsigned i = 0; i < vertices.size(); ++i) {
            adot = vertices.at(i).dot(axis);

            if (adot > max) {
                max = adot;
            } else {
                if (adot < min) {
                    min = adot;
                }
            }
        }
    }*/
	
	ComputeComponentsIntervalsAlongAxis::ComputeComponentsIntervalsAlongAxis() {
		
	}
	
	ComputeComponentsIntervalsAlongAxis::Result
	ComputeComponentsIntervalsAlongAxis::operator()(
		std::vector<Vector3D> const & vertices, 
		Vector3D const & axis
	) {
        assert(!vertices.empty());

        Real min = vertices.at(0).dot(axis);
		Real max = min;

        for (int unsigned i = 1; i < vertices.size(); ++i) {
            Real adot = vertices.at(i).dot(axis);

            if (adot > max) {
                max = adot;
            } else {
                if (adot < min) {
                    min = adot;
                }
            }
        }
		
		return Result(min, max);
	}
}