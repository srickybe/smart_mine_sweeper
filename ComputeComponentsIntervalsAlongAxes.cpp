#include "ComputeComponentsIntervalsAlongAxes.h"
#include "Matrix3D.h"
#include <cassert>

namespace ngn {

    /*void components_intervals_along_axes(
		std::vector<Vector3D> const & vertices, 
		Matrix3D const & axes, 
		Vector3D & min, 
		Vector3D & max
	) {
        assert(!vertices.empty());

        max = min = Vector3D::zero();
        Matrix3D transp = Matrix3D::transp(axes);
        Vector3D dots;

        for (int unsigned i = 0; i < vertices.size(); ++i) {
            dots = Matrix3D::mult(transp, vertices.at(i));

            for (int unsigned j = 0; j < 3; ++j) {
                if (dots.get(j) > max.get(j)) {
                    max.set(j, dots.get(j));
                } else {
                    if (dots.get(j) < min.get(j)) {
                        min.set(j, dots.get(j));
                    }
                }
            }
        }
    }*/
	
	ComputeComponentsIntervalsAlongAxes::ComputeComponentsIntervalsAlongAxes() {
		
	}
	
	ComputeComponentsIntervalsAlongAxes::Result
	ComputeComponentsIntervalsAlongAxes::operator()(
		std::vector<Vector3D> const & vertices, 
		Matrix3D const & axes
	) {
        assert(!vertices.empty());

		Matrix3D transp = Matrix3D::transp(axes);
        Vector3D min = Matrix3D::mult(transp, vertices.at(0));
		Vector3D max = min;

        for (int unsigned i = 1; i < vertices.size(); ++i) {
            Vector3D dots = Matrix3D::mult(transp, vertices.at(i));

            for (int unsigned j = 0; j < 3; ++j) {
                if (dots.get(j) > max.get(j)) {
                    max.set(j, dots.get(j));
                } else {
                    if (dots.get(j) < min.get(j)) {
                        min.set(j, dots.get(j));
                    }
                }
            }
        }
		
		return Result(min, max);
	}
}