#ifndef COMPUTE_VERTEX_LIST_H
#define COMPUTE_VERTEX_LIST_H

#include <memory>
#include <vector>
#include "Triangle.h"

namespace ngn {
    
    class ComputeVertexList {
    public:
        ComputeVertexList();

        std::shared_ptr<std::vector<int unsigned>> operator()
        (
            std::vector<Triangle> const & triples,
            std::vector<int unsigned> const & triple_indices
        ) const;
    };
}

#endif // COMPUTE_VERTEX_LIST_H