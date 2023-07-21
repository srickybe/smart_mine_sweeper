#include "GaussPointsFit.h"
#include "ComputeComponentsIntervalsAlongAxes.h"
#include "Covariance.h"
#include "Eigen.h"
#include "Mean.h"
#include "order_eigen_values.h"

namespace ngn {
	
	GaussPointsFit::Result::Result() {
		meanPoint_ = Vector3D::zero();
		naturalAxes_ = Matrix3D::zero();
		halfExtents_ = Vector3D::zero();
	}
	
	GaussPointsFit::Result::Result(Vector3D const & mean, Matrix3D const & naturalAxes, Vector3D const & halfExtents) {
		meanPoint_ = mean;
		naturalAxes_ = naturalAxes;
		halfExtents_ = halfExtents;
	}

	Vector3D const & GaussPointsFit::Result::getMeanPoint() const {
		return meanPoint_;
	}

	Matrix3D const & GaussPointsFit::Result::getNaturalAxes() const {
		return naturalAxes_;
	}

	Vector3D const & GaussPointsFit::Result::getHalfExtents() const {
		return halfExtents_;
	}
			
    GaussPointsFit::GaussPointsFit() {
    }

    
    typename GaussPointsFit::Result
    GaussPointsFit::operator()(std::vector<Vector3D> const & vertices)const {
        assert(!vertices.empty());

        Mean mean;
        Vector3D center = mean.operator()(vertices);

        int unsigned n_vertices = vertices.size();
        std::vector< Vector3D > deltas(n_vertices);
        Covariance covariance;
        Matrix3D cov = covariance.operator()(vertices, center, deltas);

        Vector3D eigenvalues;
        Matrix3D naturalAxes;
        eigen(cov, naturalAxes, eigenvalues);
        order_eigen_values(naturalAxes, eigenvalues);

        ComputeComponentsIntervalsAlongAxes ccia;
		ComputeComponentsIntervalsAlongAxes::Result intervals;
		intervals = ccia(deltas, naturalAxes);//, min, max);
        Vector3D min = intervals.getMin();
        Vector3D max = intervals.getMax();
		
        Vector3D halfExtents = max;
        halfExtents.sub(min);
        halfExtents.mult((Real) 0.5);

        Vector3D tmp(min);
        tmp.add(max);
        tmp.mult((Real) 0.5);
        center.add(naturalAxes.mult(tmp));

        return Result(center, naturalAxes, halfExtents);
    }

    
    typename GaussPointsFit::Result
    GaussPointsFit::operator()(std::vector<Vector3D> const & vertices, std::vector<int unsigned> const & vertex_indices)const {
        assert(!vertices.empty());
        assert(!vertex_indices.empty());

        Mean mean;
        Vector3D center = mean.operator()(vertices, vertex_indices);

        int unsigned n_vertices = vertex_indices.size();
        std::vector< Vector3D > deltas(n_vertices);
        Covariance covariance;
        Matrix3D cov = covariance.operator()(vertices, vertex_indices, center, deltas);

        Vector3D eigenvalues;
        Matrix3D naturalAxes;
        eigen(cov, naturalAxes, eigenvalues);
        order_eigen_values(naturalAxes, eigenvalues);

        ComputeComponentsIntervalsAlongAxes func;
		ComputeComponentsIntervalsAlongAxes::Result intervals;
		intervals = func(deltas, naturalAxes);//, min, max);
        Vector3D min = intervals.getMin();
        Vector3D max = intervals.getMax();

        Vector3D halfExtents = max;
        halfExtents.sub(min);
        halfExtents.mult((Real) 0.5);

        Vector3D tmp(min);
        tmp.add(max);
        tmp.mult((Real) 0.5);
        center.add(naturalAxes.mult(tmp));

        return Result(center, naturalAxes, halfExtents);
    }
}