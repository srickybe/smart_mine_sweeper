#ifndef COMPUTE_TRIANGLES_AREAS_H
#define COMPUTE_TRIANGLES_AREAS_H

#include <memory>
#include <vector>
#include "Real.h"

namespace ngn {
	
	class Triangle;
    class Vector3D;

    class ComputeTrianglesAreas {
    public:
        ComputeTrianglesAreas();

        std::shared_ptr<std::vector<Real>>
        operator()(std::vector<Vector3D> const &, std::vector<Triangle> const &) const;

    private:
        Real computeTriangleArea(Vector3D const & v1, Vector3D const & v2, Vector3D const & v3) const;
    };

    ////////////////////////////////////////////////////////////////////////
}

#endif // COMPUTE_TRIANGLES_AREAS_H