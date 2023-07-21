#include "Mean.h"
#include "Vector3D.h"
#include <cassert>

namespace ngn {

    Mean::Mean() {
        
    }
    
    Vector3D Mean::operator () (std::vector<Vector3D> const & vertices) const {
        assert(!vertices.empty());

        Vector3D mean = Vector3D::zero();

        for (int unsigned i = 0; i < vertices.size(); ++i) {
            mean.add(vertices.operator [](i));
        }

        mean.div((Real) (vertices.size()));

        return mean;
    }

    Vector3D Mean::operator () (std::vector<Vector3D> const & vertices, std::vector<int unsigned> const & vertexIndices) const {
        assert(!vertices.empty());
        assert(!vertexIndices.empty());
        assert(vertexIndices.size() <= vertexIndices.size());

        Vector3D mean = Vector3D::zero();

        for (int unsigned i = 0; i < vertexIndices.size(); ++i) {
            mean.add(vertices.operator [](vertexIndices.operator [](i)));
        }

        mean.div((Real) (vertexIndices.size()));

        return mean;
    }
}