#ifndef COMPUTE_TRIANGLES_CENTERS_H
#define COMPUTE_TRIANGLES_CENTERS_H

#include <memory>
#include <vector>
#include "Real.h"

namespace ngn {
    
	class Triangle;
	class Vector3D;
    
	class ComputeTrianglesCenters {
    public:
        ComputeTrianglesCenters();

        std::shared_ptr<std::vector<Vector3D>>
        operator()(std::vector<Vector3D> const & vertices, std::vector<Triangle> const & triangles)const;
    };

    ////////////////////////////////////////////////////////////////////////
}

#endif // COMPUTE_TRIANGLES_CENTERS_H