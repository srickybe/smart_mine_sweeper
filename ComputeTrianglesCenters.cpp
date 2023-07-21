#include "ComputeTrianglesCenters.h"
#include <cassert>
#include "Triangle.h"
#include "Vector3D.h"


namespace ngn {
    
	
    ComputeTrianglesCenters::ComputeTrianglesCenters() {
    }

    
    std::shared_ptr<std::vector<Vector3D>>
    ComputeTrianglesCenters::operator()(std::vector<Vector3D> const & vertices, std::vector<Triangle> const & triangles)const {
        std::shared_ptr<std::vector<Vector3D>> centers(new std::vector<Vector3D> ());

        for (int unsigned i = 0; i < triangles.size(); ++i) {
            Vector3D center(Vector3D::zero());

            for (int unsigned j = 0; j < 3; ++j) {
                center.add(vertices.at(triangles.at(i).getVertexIndex(j)));
            }

            center.div((Real) 3.0);
            centers->push_back(center);
        }

        return centers;
    }
}
