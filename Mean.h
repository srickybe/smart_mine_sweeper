#ifndef MEAN_H
#define MEAN_H

#include <vector>

namespace ngn {
    
    class Vector3D;

    class Mean {
    public:
        Mean();
        
        Vector3D operator() (std::vector<Vector3D> const & vertices) const;
        Vector3D operator() (std::vector<Vector3D> const & vertices, std::vector<int unsigned> const & vertexIndices) const;
    };
}

#endif // MEAN_H