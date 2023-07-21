#include "PartitionTriangles.h"

namespace ngn {
	
    PartitionTriangles::PartitionTriangles() {

    }

    PartitionTriangles::Result PartitionTriangles::operator()
    (
		OrientedBox3D const & box,
		std::vector<Vector3D> const & centers
	)
    const {
        assert(!centers.empty());

        Vector3D box_center(box.getCenter());
        int unsigned n_triples = centers.size();
        boost::scoped_array<Real> dots(new Real[n_triples]);
        int unsigned i = 0;
        bool partitioned = false;
        std::shared_ptr<std::vector<int unsigned>> left_triple_indices(new std::vector<int unsigned>());
        std::shared_ptr<std::vector<int unsigned>> right_triple_indices(new std::vector<int unsigned>());

        while (!partitioned && i < 3) {
            Vector3D axis = box.getOrientation().getCol(i);
            Real mean_dot = (Real) 0.0;

            for (int unsigned j = 0; j < n_triples; ++j) {
                dots[j] = Vector3D::sub(centers.at(j), box_center).dot(axis);
                mean_dot += dots[j];
            }

            mean_dot /= (Real) n_triples;

            left_triple_indices->clear();
            left_triple_indices->reserve(n_triples / 2);
            right_triple_indices->clear();
            right_triple_indices->reserve(n_triples / 2);

            for (int unsigned j = 0; j < n_triples; ++j) {
                if (dots[j] > mean_dot) {
                    right_triple_indices->push_back(j);
                } else {
                    left_triple_indices->push_back(j);
                }
            }

            if (!(right_triple_indices->empty()) && !(left_triple_indices->empty())) {
                partitioned = true;
                return Result(left_triple_indices, right_triple_indices, partitioned);
            }

            ++i;
        }

        return Result(left_triple_indices, right_triple_indices, partitioned);
    }

    
    PartitionTriangles::Result PartitionTriangles::operator()
    (
		OrientedBox3D const & box,
		std::vector<Vector3D> const & centers,
		std::vector<int unsigned> const & triple_indices
	)
    const {
        assert(!centers.empty());
        assert(!triple_indices.empty());

        Vector3D box_center(box.getCenter());
        int unsigned n_triple_indices = triple_indices.size();
        boost::scoped_array<Real> dots(new Real[n_triple_indices]);
        int unsigned i = 0;
        bool partitioned = false;
        std::shared_ptr<std::vector<int unsigned>> left_triple_indices(new std::vector<int unsigned>());
        std::shared_ptr<std::vector<int unsigned>> right_triple_indices(new std::vector<int unsigned>());

        while (!partitioned && i < 3) {
            Vector3D axis = box.getOrientation().getCol(i);
            Real mean_dot = (Real) 0;

            for (int unsigned j = 0; j < n_triple_indices; ++j) {
                dots[j] = Vector3D::sub(centers.at(triple_indices.at(j)), box_center).dot(axis);
                mean_dot += dots[j];
            }

            mean_dot /= (Real) n_triple_indices;

            left_triple_indices->clear();
            left_triple_indices->reserve(n_triple_indices / 2);
            right_triple_indices->clear();
            right_triple_indices->reserve(n_triple_indices / 2);

            for (int unsigned j = 0; j < n_triple_indices; ++j) {
                if (dots[j] > mean_dot) {
                    right_triple_indices->push_back(triple_indices.at(j));
                } else {
                    left_triple_indices->push_back(triple_indices.at(j));
                }
            }

            if (!(right_triple_indices->empty()) && !(left_triple_indices->empty())) {
                partitioned = true;
                return Result(left_triple_indices, right_triple_indices, partitioned);
            }

            ++i;
        }
        
        return Result(left_triple_indices, right_triple_indices, partitioned);
    }
}