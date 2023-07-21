#include "GaussTrianglesFit.h"
#include "Eigen.h"
#include "order_eigen_values.h"

namespace ngn {
	
	GaussTrianglesFit::Result::Result() {
		meanPoint_ = Vector3D::zero();
		naturalAxes_ = Matrix3D::zero();
		halfExtents_ = Vector3D::zero();
	}

	GaussTrianglesFit::Result::Result(Vector3D const & mean, Matrix3D const & naturalAxes, Vector3D const & halfExtents) {
		meanPoint_ = mean;
		naturalAxes_ = naturalAxes;
		halfExtents_ = halfExtents;
	}

	Vector3D const & GaussTrianglesFit::Result::getMeanPoint() const {
		return meanPoint_;
	}

	Matrix3D const & GaussTrianglesFit::Result::getNaturalAxes() const {
		return naturalAxes_;
	}
	
	Vector3D const & GaussTrianglesFit::Result::getHalfExtents() const {
		return halfExtents_;
	}
	
    GaussTrianglesFit::GaussTrianglesFit() {
    }

    typename GaussTrianglesFit::Result GaussTrianglesFit::operator()(
            std::vector<Vector3D> const & vertices,
            std::vector<Triangle> const & triples,
            std::vector<Vector3D> const & centers,
            std::vector<Real> const & areas
            )const {
        assert(!vertices.empty());
        assert(!triples.empty());
        assert(triples.size() == centers.size());
        assert(triples.size() == areas.size());

        Vector3D mean = Vector3D::zero();
        Real total_area = (Real) 0;

        for (int unsigned i = 0; i < triples.size(); ++i) {
            if (areas.at(i) != (Real) 0.0) {
                total_area += areas.at(i);
                mean.add(Vector3D::mult(centers.at(i), areas.at(i)));
            } else {
                std::cout << "triples[" << i << "] = " << triples[i] << "\n";
                std::cout << "triples[" << i << " has an area equal to zero\n";
            }
        }

        assert(total_area != (Real) 0.0);

        mean.div(total_area);

        Matrix3D covariance(Matrix3D::zero());
        Matrix3D temp;

        for (int unsigned i = 0; i < triples.size(); ++i) {
            if (areas.at(i) != (Real) 0.0) {
                temp = centers.at(i).tensorProduct(centers.at(i));
                temp.mult((Real) 9.0);

                Triangle const triple = triples.at(i);
                Vector3D vertex = vertices.at(triple.getVertexIndex(0));
                temp.add(vertex.tensorProduct(vertex));

                vertex = vertices.at(triple.getVertexIndex(1));
                temp.add(vertex.tensorProduct(vertex));

                vertex = vertices.at(triple.getVertexIndex(2));
                temp.add(vertex.tensorProduct(vertex));

                temp.mult(areas.at(i) / (Real) 12.0);
                covariance.add(temp);
            }
        }

        covariance.sub(mean.tensorProduct(mean).mult(total_area));

        Vector3D eigenvalues;
        Matrix3D naturalAxes;
        assert(eigen(covariance, naturalAxes, eigenvalues));

        order_eigen_values(naturalAxes, eigenvalues);

        Matrix3D transp(naturalAxes);
        transp.transp();
        Vector3D dots(Matrix3D::mult(transp, Vector3D::sub(vertices.at(0), mean)));
        Vector3D min;
        Vector3D max;
        min = max = dots;

        for (int unsigned i = 1; i < vertices.size(); ++i) {
            dots = Matrix3D::mult(transp, Vector3D::sub(vertices.at(i), mean));

            for (int j = 0; j < 3; ++j) {
                if (dots.get(j) > max.get(j)) {
                    max.set(j, dots.get(j));
                } else {
                    if (dots.get(j) < min.get(j)) {
                        min.set(j, dots.get(j));
                    }
                }
            }
        }

        Vector3D halfExtents = max;
        halfExtents.sub(min);
        halfExtents.mult((Real) 0.5);

        Vector3D tmp(max);
        tmp.add(min);
        tmp.mult((Real) 0.5);
        mean.add(naturalAxes.mult(tmp));

        order_eigen_values(naturalAxes, halfExtents);

        assert(halfExtents.getX() >= halfExtents.getY() && halfExtents.getY() >= halfExtents.getZ());

        return Result(mean, naturalAxes, halfExtents);
    }

    typename GaussTrianglesFit::Result GaussTrianglesFit::operator()(
            std::vector<Vector3D> const & vertices,
            std::vector<int unsigned> const & vertex_indices,
            std::vector<Triangle> const & triples,
            std::vector<int unsigned> const & triple_indices,
            std::vector<Vector3D> const & centers,
            std::vector<Real> const & areas
            )const {
        assert(!vertices.empty());

        assert(!vertex_indices.empty());
        assert(vertices.size() >= vertex_indices.size());

        assert(!triples.empty());

        assert(!triple_indices.empty());
        assert(triples.size() >= triple_indices.size());

        assert(!centers.empty());
        assert(!areas.empty());

        Vector3D mean = Vector3D::zero();
        //int unsigned n_triangles = triples.size();
        Real total_area = (Real) 0;
        int unsigned no;

        for (int unsigned i = 0; i < triple_indices.size(); ++i) {
            no = triple_indices.at(i);
            Real area = areas.at(no);

            //assert(no < n_triangles);
			assert(no < triples.size());

            //We don't include degenerated triangles in the computation 
            if (area != (Real) 0) {
                total_area += area;
                mean.add(Vector3D::mult(centers.at(no), area));
            }
        }

        //if we have no triangle, we fit points instead of triangles
        assert(total_area != (Real) 0);

        mean.div(total_area);

        Matrix3D covariance(Matrix3D::zero());
        Matrix3D temp;

        for (int unsigned i = 0; i < triple_indices.size(); ++i) {
            no = triple_indices.at(i);

            if (areas.at(no) != (Real) 0.0) {
                temp = Vector3D::tensorProduct(centers.at(no), centers.at(no));
                temp.mult((Real) 9.0);

                Vector3D vertex = vertices.at(triples.at(no).getVertexIndex(0));
                temp.add(Vector3D::tensorProduct(vertex, vertex));

                vertex = vertices.at(triples.at(no).getVertexIndex(1));
                temp.add(Vector3D::tensorProduct(vertex, vertex));

                vertex = vertices.at(triples.at(no).getVertexIndex(2));
                temp.add(Vector3D::tensorProduct(vertex, vertex));

                temp.mult(areas.at(no) / (Real) 12.0);
                covariance.add(temp);
            }
        }

        covariance.sub(mean.tensorProduct(mean).mult(total_area));

        Vector3D eigenvalues;
        //Matrix3D s_cov(covariance);
        Matrix3D naturalAxes;

        assert(eigen(covariance, naturalAxes, eigenvalues));

        order_eigen_values(naturalAxes, eigenvalues);

        Matrix3D transp(Matrix3D::transp(naturalAxes));
        Vector3D dots(transp.mult(Vector3D::sub(vertices.at(vertex_indices.at(0)), mean)));

        Vector3D min;
        Vector3D max;
        min = max = dots;

        for (int unsigned i = 1; i < vertex_indices.size(); ++i) {
            dots = transp.mult(Vector3D::sub(vertices.at(vertex_indices.at(i)), mean));

            for (int unsigned i = 0; i < 3; ++i) {
                if (dots.get(i) > max.get(i)) {
                    max.set(i, dots.get(i));
                } else {
                    if (dots.get(i) < min.get(i)) {
                        min.set(i, dots.get(i));
                    }
                }
            }
        }

        Vector3D halfExtents = max;
        halfExtents.sub(min);
        halfExtents.mult((Real) 0.5);

        Vector3D tmp(max);
        tmp.add(min);
        tmp.mult((Real) 0.5);
        mean.add(naturalAxes.mult(tmp));

        order_eigen_values(naturalAxes, halfExtents);

        assert(halfExtents.getX() >= halfExtents.getY() && halfExtents.getY() >= halfExtents.getZ());

        return Result(mean, naturalAxes, halfExtents);
    }
}