#ifndef BOUNDING_VOLUME_BUILDER_H
#define BOUNDING_VOLUME_BUILDER_H

#include "AxisAlignedBox3D.h"
#include "Sphere.h"
#include "Covariance.h"
#include "Eigen.h"
#include "GaussPointsFit.h"
#include "GaussTrianglesFit.h"
#include "Mean.h"
#include "order_eigen_values.h"
#include "OrientedBox3D.h"
#include "OrientedEllipsoid.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vector3D.h"
#include "Support.h"
#include <cassert>
#include <cmath>

namespace ngn {
    class AxisAlignedBox3D;
    class GaussPointsFit;
    class GaussTrianglesFit;
    class OrientedBox3D;
    class OrientedEllipsoid;
    class Sphere;
    class Vector3D;

    
    class BoundingVolumeBuilder3D {
    public:
        BoundingVolumeBuilder3D();

        AxisAlignedBox3D computeBoundingAxisAlignedBox3D(std::vector<Vector3D> const & vertices) const;

        AxisAlignedBox3D computeBoundingAxisAlignedBox3D(std::vector<Vector3D> const & vertices, std::vector<int unsigned> const & triple_indexes) const;

        Sphere computeBoundingSphere(std::vector<Vector3D> const & vertices) const;

        Sphere computeBoundingSphere(std::vector<Vector3D> const & vertices, std::vector<int unsigned> const & vertex_indexes) const;

        Sphere computeSmallestBoundingSphere(std::vector<Vector3D> const & vertices, Real tol) const;

        Sphere computeSmallestBoundingSphere(std::vector<Vector3D> const & vertices, std::vector<int unsigned> const & vertex_indexes, Real tol) const;

        OrientedBox3D computeBoundingOrientedBox3D(GaussPointsFit gauss_points_fit, std::vector<Vector3D> const & vertices) const;

        OrientedBox3D computeBoundingOrientedBox3D
        (
                GaussPointsFit,
                std::vector<Vector3D> const & vertices,
                std::vector<int unsigned> const & vertexIndices

                )
        const;


        OrientedBox3D computeBoundingOrientedBox3D
        (
                GaussTrianglesFit gauss_triangles_fit,
                std::vector<Vector3D> const & vertices,
                std::vector<Triangle> const & triples,
                std::vector<Vector3D> const & centers,
                std::vector<Real> const & areas
                )
        const;

        OrientedBox3D computeBoundingOrientedBox3D
        (
                GaussTrianglesFit gauss_triangles_fit,
                std::vector<Vector3D> const & vertices,
                std::vector<int unsigned> const & vertex_indices,
                std::vector<Triangle> const & triples,
                std::vector<int unsigned> const & triple_indices,
                std::vector<Vector3D> const & centers,
                std::vector<Real> const & areas
                )
        const;

        OrientedEllipsoid computeBoundingOrientedEllipsoid
        (
                GaussPointsFit gauss_point_fit,
                std::vector<Vector3D> const &
                )
        const;

        OrientedEllipsoid computeBoundingOrientedEllipsoid
        (
                GaussPointsFit gauss_point_fit,
                std::vector<Vector3D> const &,
                std::vector<int unsigned> const &

                )
        const;

    private:
        void permutate(std::vector<Vector3D > & vertices) const;
    };

    ////////////////////////////////////////////////////////////////////////
}

#endif // BOUNDING_VOLUME_BUILDER_H
