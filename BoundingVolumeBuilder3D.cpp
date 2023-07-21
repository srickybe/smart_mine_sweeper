#include "BoundingVolumeBuilder3D.h"
#include "Rand.h"

namespace ngn {

    BoundingVolumeBuilder3D::BoundingVolumeBuilder3D() {
    }

    AxisAlignedBox3D BoundingVolumeBuilder3D::computeBoundingAxisAlignedBox3D(std::vector<Vector3D> const & vertices) const {
        assert(!vertices.empty());

        Vector3D min(Vector3D::zero());
        Vector3D max(Vector3D::zero());
        Real coord;

        for (int unsigned i = 0; i < vertices.size(); ++i) {
            for (int unsigned j = 0; j < 3; ++j) {
                coord = vertices[i].get(j);

                if (coord > max.get(j)) {
                    max.set(j, coord);
                } else {
                    if (coord < min.get(j)) {
                        min.set(j, coord);
                    }
                }
            }
        }

        return AxisAlignedBox3D::fromMinMax(min, max);
    }

    AxisAlignedBox3D BoundingVolumeBuilder3D::computeBoundingAxisAlignedBox3D(
            std::vector<Vector3D> const & vertices,
            std::vector<int unsigned> const & vertex_indexes
            )
    const {
        assert(!vertices.empty());
        assert(!vertex_indexes.empty());
        assert(vertices.size() >= vertex_indexes.size());

        Vector3D min(Vector3D::zero());
        Vector3D max(Vector3D::zero());

        for (int unsigned i = 0; i < vertex_indexes.size(); ++i) {
			int unsigned vertexIndex = vertex_indexes[i];
			Vector3D vertex = vertices[vertexIndex];
			
            for (int unsigned j = 0; j < 3; ++j) {
                Real coord = vertex.get(j);

                if (coord > max.get(j)) {
                    max.set(j, coord);
                } else {
                    if (coord < min.get(j)) {
                        min.set(j, coord);
                    }
                }
            }
        }

        return AxisAlignedBox3D::fromMinMax(min, max);
    }

    Sphere BoundingVolumeBuilder3D::computeBoundingSphere(
            std::vector<Vector3D> const & vertices
            ) const {
        assert(!vertices.empty());

        Mean mean;
        Vector3D center = mean.operator()(vertices);
        Covariance covariance;
        Matrix3D cov = covariance.operator()(vertices, center);

        Matrix3D naturalAxes;
        Vector3D eigenvalues;
        eigen(cov, naturalAxes, eigenvalues);
        order_eigen_values(naturalAxes, eigenvalues);

        Vector3D v_max = vertices.operator[](0);
        Vector3D v_min = v_max;
        Vector3D axis(naturalAxes.get(0, 0), naturalAxes.get(1, 0), naturalAxes.get(2, 0));
        Real min = v_min.dot(axis);
        Real max = min;
        Real adot;

        for (int unsigned i = 1; i < vertices.size(); ++i) {
            adot = vertices[i].dot(axis);

            if (adot > max) {
                max = adot;
                v_max = vertices[i];
            } else {
                if (adot < min) {
                    min = adot;
                    v_min = vertices[i];
                }
            }
        }

        center = v_min;
        center.add(v_max);
        center.mult((Real) 0.5);

        Real radius = Vector3D::sub(v_max, v_min).length() / (Real) 2.0;

        for (int unsigned i = 0; i < vertices.size(); ++i) {
            Vector3D delta = Vector3D::sub(vertices[i], center);

            if (delta.lengthSquared() > radius * radius) {
                center.sub(Vector3D::mult(Vector3D::norm(delta), radius));
                center.add(vertices[i]);
                center.mult((Real) 0.5);

                radius = Vector3D::sub(vertices[i], center).length();
            }
        }

        return Sphere(center, radius);
    }

    Sphere BoundingVolumeBuilder3D::computeBoundingSphere(
            std::vector<Vector3D> const & vertices,
            std::vector<int unsigned> const & vertex_indexes
            ) const {
        assert(!vertices.empty());
        assert(!vertex_indexes.empty());
        assert(vertices.size() >= vertex_indexes.size());

        Mean mean;
        Vector3D center = mean.operator()(vertices, vertex_indexes);
        Covariance covariance;
        Matrix3D cov = covariance.operator()(vertices, vertex_indexes, center);

        Matrix3D naturalAxes;
        Vector3D eigenvalues;
        eigen(cov, naturalAxes, eigenvalues);
        order_eigen_values(naturalAxes, eigenvalues);

        Vector3D v_max = vertices[vertex_indexes[0]];
        Vector3D v_min = v_max;
        Vector3D axis(naturalAxes.get(0, 0), naturalAxes.get(1, 0), naturalAxes.get(2, 0));
        Real min = v_min.dot(axis);
        Real max = min;
        Real adot;

        for (int unsigned i = 1; i < vertex_indexes.size(); ++i) {
            Vector3D vertex = vertices[vertex_indexes[i]];
            adot = vertex.dot(axis);

            if (adot > max) {
                max = adot;
                v_max = vertex;
            } else {
                if (adot < min) {
                    min = adot;
                    v_min = vertex;
                }
            }
        }

        center = v_min;
        center.add(v_max);
        center.mult((Real) 0.5);
        //Real radius = Vector3D::sub(v_min, v_max).length() / (Real) 2.0;
        Real radius = Vector3D::sub(v_max, center).length();

        for (int unsigned i = 0; i < vertex_indexes.size(); ++i) {
            Vector3D vertex = vertices[vertex_indexes[i]];
            Vector3D delta = Vector3D::sub(vertex, center);

            if (delta.lengthSquared() > radius * radius) {
                delta.norm();
                center.sub(Vector3D::mult(delta, radius));
                center.add(vertex);
                center.mult((Real) 0.5);

                radius = Vector3D::sub(vertex, center).length();
            }
        }

        return Sphere(center, radius);
    }

    
    void BoundingVolumeBuilder3D::permutate(std::vector<Vector3D > & vertices) const {
        
		for (int unsigned i = 0; i < vertices.size(); ++i) {
            int index = util::Rand<int>::getInstance().next(vertices.size());
            Vector3D tmp = vertices.operator[](index);
            vertices.operator[](index) = vertices.operator[](i);
            vertices.operator[](i) = tmp;
        }
    }

    
    Sphere BoundingVolumeBuilder3D::computeSmallestBoundingSphere(std::vector<Vector3D> const & vertices, Real tol) const {
        if (!vertices.empty()) {
            std::vector<Vector3D > points(vertices.size());

            for (int unsigned i = 0; i < points.size(); ++i) {
                points.operator[](i) = vertices.operator[](i);
            }

            this->permutate(points);
            Support support;
            support.addPoint(points.operator[](0));
            Sphere res(points.operator[](0), (Real) 0.0);

            for (int unsigned i = 1; i < points.size(); ++i) {
                if (support.containsPoint(points.operator[](i), tol)) {
                    continue;
                } else {
                    if (res.contains(points.operator[](i))) {
                        continue;
                    } else {
                        Sphere sphere = support.update(points.operator[](i));

                        if (sphere.getRadius() > res.getRadius()) {
                            res = sphere;
                            i = 0;
                            continue;
                        }
                    }
                }
            }

            return res;
        } else {
            return Sphere(Vector3D::zero(), (Real) 0.0);
        }
    }

    
    Sphere BoundingVolumeBuilder3D::computeSmallestBoundingSphere(
            std::vector<Vector3D> const & vertices,
            std::vector<int unsigned> const & vertex_indexes,
            Real tol
            ) const {
        std::vector<Vector3D> points(vertex_indexes.size());

        for (int unsigned i = 0; i < vertex_indexes.size(); ++i) {
            points.operator [](i) = (vertices.operator[](vertex_indexes.operator[](i)));
        }

        return computeSmallestBoundingSphere(points, tol);
    }

    OrientedBox3D BoundingVolumeBuilder3D::computeBoundingOrientedBox3D
    (
            GaussPointsFit gauss_points_fit,
            std::vector<Vector3D> const & vertices
            )
    const {
        assert(!vertices.empty());

        typename GaussPointsFit::Result result = gauss_points_fit.operator ()(vertices);

        return OrientedBox3D(result.getMeanPoint(), result.getNaturalAxes(), result.getHalfExtents());
    }

    OrientedBox3D BoundingVolumeBuilder3D::computeBoundingOrientedBox3D
    (
            GaussPointsFit gauss_points_fit,
            std::vector<Vector3D> const & vertices,
            std::vector<int unsigned> const & vertex_indexes
            )
    const {
        assert(!vertices.empty());
        assert(!vertex_indexes.empty());
        assert(vertices.size() >= vertex_indexes.size());

        typename GaussPointsFit::Result result =
                gauss_points_fit.operator()(vertices, vertex_indexes);

        return OrientedBox3D(result.getMeanPoint(), result.getNaturalAxes(), result.getHalfExtents());
    }

    OrientedBox3D BoundingVolumeBuilder3D::computeBoundingOrientedBox3D
    (
            GaussTrianglesFit gauss_triangles_fit,
            std::vector<Vector3D> const & vertices,
            std::vector<Triangle> const & triples,
            std::vector<Vector3D> const & centers,
            std::vector<Real> const & areas
            )
    const {
        assert(!vertices.empty());
        assert(!triples.empty());
        assert(!centers.empty());
        assert(!areas.empty());

        typename GaussTrianglesFit::Result result =
                gauss_triangles_fit.operator ()(vertices, triples, centers, areas);

        return OrientedBox3D(result.getMeanPoint(), result.getNaturalAxes(), result.getHalfExtents());
    }

    OrientedBox3D BoundingVolumeBuilder3D::computeBoundingOrientedBox3D
    (
            GaussTrianglesFit gauss_triangles_fit,
            std::vector<Vector3D> const & vertices,
            std::vector<int unsigned> const & vertex_indexes,
            std::vector<Triangle> const & triples,
            std::vector<int unsigned> const & triple_indexes,
            std::vector<Vector3D> const & centers,
            std::vector<Real> const & areas
            )
    const {
        assert(!vertices.empty());
        assert(!vertex_indexes.empty());
        assert(vertices.size() >= vertex_indexes.size());
        assert(!triples.empty());
        assert(!triple_indexes.empty());
        assert(triples.size() >= triple_indexes.size());
        assert(!centers.empty());
        assert(!areas.empty());

        typename GaussTrianglesFit::Result result
                = gauss_triangles_fit.operator()(vertices, vertex_indexes, triples, triple_indexes, centers, areas);

        return OrientedBox3D(result.getMeanPoint(), result.getNaturalAxes(), result.getHalfExtents());
    }

    //////////////////////////////////////////////////////////////////////////

    OrientedEllipsoid BoundingVolumeBuilder3D::computeBoundingOrientedEllipsoid(
		GaussPointsFit gauss_points_fit,
		std::vector<Vector3D> const & vertices
	)
    const {
        assert(!vertices.empty());


        typename GaussPointsFit::Result result = gauss_points_fit.operator ()(vertices);
        Vector3D center = result.getMeanPoint();
        Matrix3D orientation = result.getNaturalAxes();
        Vector3D extents = result.getHalfExtents();
        
        Matrix3D scale(
                (Real) 0.5 / extents.getX(), (Real) 0.0, (Real) 0.0,
                (Real) 0.0, (Real) 0.5 / extents.getY(), (Real) 0.0,
                (Real) 0.0, (Real) 0.0, (Real) 0.5 / extents.getZ()
                );

        Matrix3D transform(orientation.mult(scale.mult(Matrix3D::transp(orientation))));

        int n_vertices = vertices.size();
        std::vector<Vector3D> vertexes(n_vertices);

        for (int unsigned i = 0; i < vertices.size(); ++i) {
            vertexes[i] = transform.mult(vertices[i]);
        }

        Real tol = 1.0e-6;
        Sphere sphere = this->computeSmallestBoundingSphere(vertices, tol);
        center = Matrix3D::inv(transform).mult(sphere.getCenter());
        extents.mult(sphere.getRadius() * (Real) 2.0);

        return OrientedEllipsoid(center, orientation, extents);
    }

    OrientedEllipsoid BoundingVolumeBuilder3D::computeBoundingOrientedEllipsoid
    (
            GaussPointsFit gauss_points_fit,
            std::vector<Vector3D> const & vertices,
            std::vector<int unsigned> const & vertex_indexes
            )
    const {
        assert(!vertices.empty());
        assert(!vertex_indexes.empty());
        assert(vertices.size() >= vertex_indexes.size());

        typename GaussPointsFit::Result result = gauss_points_fit(vertices, vertex_indexes);
        Vector3D center = result.getMeanPoint();
        Matrix3D orientation = result.getNaturalAxes();
        Vector3D extents = result.getHalfExtents();
        
        Matrix3D scale(
                (Real) 0.5 / extents.getX(), (Real) 0.0, (Real) 0.0,
                (Real) 0.0, (Real) 0.5 / extents.getY(), (Real) 0.0,
                (Real) 0.0, (Real) 0.0, (Real) 0.5 / extents.getZ()
                );

        Matrix3D transform(orientation.mult(scale.mult(Matrix3D::transp(orientation))));

        int n_vertices = vertex_indexes.size();
        std::vector<Vector3D> vertexes(n_vertices);

        for (int unsigned i = 0; i < vertex_indexes.size(); ++i) {
            vertexes[i] = transform.mult(vertices[vertex_indexes[i]]);
        }

        Sphere sphere = computeBoundingSphere(vertexes);
        center = Matrix3D::inv(transform).mult(sphere.getCenter());
        extents.mult(sphere.getRadius()); //?????

        return OrientedEllipsoid(center, orientation, extents);
    }
}