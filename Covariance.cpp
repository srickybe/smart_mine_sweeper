#include "Covariance.h"

namespace ngn {
	
    Covariance::Covariance() {

    }

    
    Matrix3D Covariance::operator()(
            std::vector<Vector3D> const & vertices,
            Vector3D const & center
            ) const {
        assert(!vertices.empty());

        Matrix3D cov(Matrix3D::zero());

        for (int unsigned i = 0; i < vertices.size(); ++i) {
            Vector3D delta(vertices.at(i));
            delta.sub(center);
            cov.add(delta.tensorProduct(delta));
        }

        return cov;
    }

    
    Matrix3D Covariance::operator()(
            std::vector<Vector3D> const & vertices,
            Vector3D const & center,
            std::vector<Vector3D> &distances
            ) const {
        assert(!vertices.empty());

        distances.resize(vertices.size());
        Matrix3D cov(Matrix3D::zero());

        for (int unsigned i = 0; i < vertices.size(); ++i) {
            distances[i] = Vector3D::sub(vertices.at(i), center);
            cov.add(distances[i].tensorProduct(distances[i]));
        }

        return cov;
    }

    
    Matrix3D Covariance::operator()(
            std::vector<Vector3D> const & vertices,
            std::vector<int unsigned> const & indices,
            Vector3D const & center
            ) const {
        assert(!vertices.empty());
        assert(!indices.empty());
        assert(vertices.size() >= indices.size());

        Matrix3D cov(Matrix3D::zero());

        for (int unsigned i = 0; i < indices.size(); ++i) {
            assert(indices.at(i) < vertices.size());

            Vector3D delta(vertices.at(indices.at(i)));
            delta.sub(center);
            cov.add(delta.tensorProduct(delta));
        }

        return cov;
    }

    
    Matrix3D Covariance::operator()(
            std::vector<Vector3D> const & vertices,
            std::vector<int unsigned> const & indices,
            Vector3D const & center,
            std::vector<Vector3D> &distances
            ) const {
        assert(!vertices.empty());
        assert(!indices.empty());
        assert(vertices.size() >= indices.size());

        distances.resize(indices.size());
        Matrix3D cov(Matrix3D::zero());

        for (int unsigned i = 0; i < indices.size(); ++i) {
            distances[i] = Vector3D::sub(vertices.at(indices.at(i)), center);
            cov.add(distances[i].tensorProduct(distances[i]));
        }

        return cov;
    }
}