#ifndef GAUSS_TRIANGLES_FIT_H
#define GAUSS_TRIANGLES_FIT_H

#include "Matrix3D.h"
#include "Vector3D.h"
#include "Triangle.h"

#include <cassert>
#include <iostream>
#include <vector>

namespace ngn {
    class Matrix3D;
    template <int unsigned> class VertexIndices;
    class Vector3D;

    class GaussTrianglesFit {
    public:

        class Result {
        public:

            Result();
            Result(Vector3D const & mean, Matrix3D const & naturalAxes, Vector3D const & halfExtents);
            Vector3D const & getMeanPoint() const;
            Matrix3D const & getNaturalAxes() const;
            Vector3D const & getHalfExtents() const; 
			
        private:
            Vector3D meanPoint_;
            Matrix3D naturalAxes_;
            Vector3D halfExtents_;
        };

        GaussTrianglesFit();

        Result operator()(
                std::vector<Vector3D> const & vertices,
                std::vector<Triangle> const & triples,
                std::vector<Vector3D> const & centers,
                std::vector<Real> const & areas
                )const;

        Result operator()(
                std::vector<Vector3D> const & vertices,
                std::vector<int unsigned> const & vertex_indices,
                std::vector<Triangle> const & triples,
                std::vector<int unsigned> const & triple_indices,
                std::vector<Vector3D> const & centers,
                std::vector<Real> const & areas
                )const;
    };

    ////////////////////////////////////////////////////////////////////////

}

#endif // GAUSS_TRIANGLES_FIT_H