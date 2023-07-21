#include "SphereTree.h"

namespace ngn {
	

    SphereTree::SphereTree()
    : left_child_(),
    right_child_(),
    sphere_(),
    triple_indices_(new std::vector<int unsigned>()),
    vertex_indices_(new std::vector<int unsigned>()) {
    }

    SphereTree::SphereTree(
		GaussPointsFit const & gauss_points_fit,
		std::vector<Vector3D> const & vertices,
		std::vector<Triangle> const & triples, //triples
		std::vector<Vector3D> const & centers //triangle centers
	)
    : left_child_(),
    right_child_(),
    sphere_(),
    triple_indices_(new std::vector<int unsigned>(triples.size())),
    vertex_indices_(new std::vector<int unsigned>(vertices.size())) {
        this->initializeIndices(vertices.size(), triples.size());
        this->build(gauss_points_fit, vertices, triples, centers);
    }

    SphereTree::SphereTree
    (
		GaussTrianglesFit const & gauss_triangles_fit,
		std::vector<Vector3D> const & vertices,
		std::vector<Triangle> const & triples,
		std::vector<Vector3D> const & centers,
		std::vector<Real> const & areas
	)
    : left_child_(),
    right_child_(),
    sphere_(),
    triple_indices_(new std::vector<int unsigned>(triples.size())),
    vertex_indices_(new std::vector<int unsigned>(vertices.size())) {
        this->initializeIndices(vertices.size(), triples.size());
        this->build(gauss_triangles_fit, vertices, triples, centers, areas);
    }

    
    bool SphereTree::equals(SphereTree const & rhs, Real tol) const {
        if (this->getSphere() != 0) {
            if (rhs.getSphere() != 0) {
                if (!this->getSphere()->equalsWithTol(*(rhs.getSphere()), tol)) {
                    return false;
                }

                if (this->numberOfTripleIndices() != rhs.numberOfTripleIndices()) {
                    return false;
                }

                for (int unsigned i = 0; i < this->numberOfTripleIndices(); ++i) {
                    if (this->tripleIndex(i) != rhs.tripleIndex(i)) {
                        return false;
                    }
                }
            } else {
                return false;
            }
        } else {
            if (rhs.getSphere() != 0) {
                return false;
            }
        }

        if (this->getLeftChild() != 0) {
            if (rhs.getLeftChild() != 0) {
                if (!this->getLeftChild()->equals(*(rhs.getLeftChild()), tol)) {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            if (rhs.getLeftChild() != 0) {
                return false;
            }
        }

        if (this->getRightChild() != 0) {
            if (rhs.getRightChild() != 0) {
                if (!this->getRightChild()->equals(*(rhs.getRightChild()), tol)) {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            if (rhs.getRightChild() != 0) {
                return false;
            }
        }

        return true;
    }

    
    std::shared_ptr<SphereTree> const &
    SphereTree::getLeftChild()const {
        return left_child_;
    }

    
    std::shared_ptr<SphereTree>
    SphereTree::getLeftChild() {
        return left_child_;
    }

    
    std::shared_ptr<SphereTree> const &
    SphereTree::getRightChild()const {
        return right_child_;
    }

    
    std::shared_ptr<SphereTree>
    SphereTree::getRightChild() {
        return right_child_;
    }

    
    std::shared_ptr<Sphere> const &
    SphereTree::getSphere()const {
        return sphere_;
    }

    
    std::shared_ptr<std::vector<int unsigned>> SphereTree::getTripleIndices()const {
        return triple_indices_;
    }

    
    std::shared_ptr<std::vector<int unsigned>> SphereTree::getVertexIndices()const {
        return vertex_indices_;
    }

    
    int unsigned SphereTree::tripleIndex(int unsigned i)const {
        assert(i < triple_indices_->size());

        return triple_indices_->operator[](i);
    }

    
    int unsigned SphereTree::vertexIndex(int unsigned i)const {
        assert(i < vertex_indices_->size());

        return vertex_indices_->operator[](i);
    }

    
    void SphereTree::setTripleIndices(std::shared_ptr<std::vector<int unsigned>> const & tripleIndices) {
        triple_indices_ = tripleIndices;
    }

    
    void SphereTree::setVertexIndices(std::shared_ptr<std::vector<int unsigned>> const & vertexIndices) {
        vertex_indices_ = vertexIndices;
    }

    
    int unsigned SphereTree::numberOfTripleIndices()const {
        return triple_indices_->size();
    }

    
    int unsigned SphereTree::numberOfVertexIndices()const {
        return vertex_indices_->size();
    }

    
    void SphereTree::build
    (
		GaussPointsFit const & gauss_points_fit,
		std::vector<Vector3D> const & vertices,
		std::vector<Triangle> const & triples,
		std::vector<Vector3D> const & centers
	) {
        if (triple_indices_->size() > 1) {
            BoundingVolumeBuilder3D cbv;
            sphere_ = std::shared_ptr<Sphere> (new Sphere(cbv.computeBoundingSphere(vertices, *vertex_indices_)));
            OrientedBox3D box = cbv.computeBoundingOrientedBox3D(gauss_points_fit, vertices, *vertex_indices_);

            left_child_ = std::shared_ptr<SphereTree> (new SphereTree());
            right_child_ = std::shared_ptr<SphereTree> (new SphereTree());

            PartitionTriangles partition_triangles;
            PartitionTriangles::Result result =
                    partition_triangles.operator()(box, centers, *triple_indices_);

            if (result.partitioned()) {
                left_child_->setTripleIndices(result.getLeftSideTriples());
                ComputeVertexList compute_vertex_list;
                std::shared_ptr<std::vector<int unsigned>> leftVertexIndices =
                        compute_vertex_list.operator()(triples, *left_child_->getTripleIndices());
                left_child_->setVertexIndices(leftVertexIndices);
                left_child_->build(gauss_points_fit, vertices, triples, centers);

                right_child_->setTripleIndices(result.getRightSideTriples());
                std::shared_ptr<std::vector<int unsigned>> rightVertexIndices =
                        compute_vertex_list.operator()(triples, *right_child_->getTripleIndices());
                right_child_->setVertexIndices(rightVertexIndices);
                right_child_->build(gauss_points_fit, vertices, triples, centers);
            } else {
                /*delete left_child_;
                left_child_ = 0;

                delete right_child_;
                right_child_ = 0;*/
            }
        }
    }

    void SphereTree::build
    (
		GaussTrianglesFit const & gauss_triangles_fit,
		std::vector<Vector3D> const & vertices,
		std::vector<Triangle> const & triples,
		std::vector<Vector3D> const & centers,
		std::vector<Real> const & areas
	) {
        if (triple_indices_->size() > 1) {
            BoundingVolumeBuilder3D cbv;
            sphere_ = std::shared_ptr<Sphere> (new Sphere(cbv.computeBoundingSphere(vertices, *vertex_indices_)));
            OrientedBox3D box = cbv.computeBoundingOrientedBox3D(gauss_triangles_fit, vertices, *vertex_indices_, triples, *triple_indices_, centers, areas);

            left_child_ = std::shared_ptr<SphereTree> (new SphereTree());
            right_child_ = std::shared_ptr<SphereTree> (new SphereTree());

            PartitionTriangles partition_triangles;
            PartitionTriangles::Result result =
                    partition_triangles.operator()(box, centers, *triple_indices_);

            if (result.partitioned()) {
                left_child_->setTripleIndices(result.getLeftSideTriples());
                ComputeVertexList compute_vertex_list;
                std::shared_ptr<std::vector<int unsigned>> leftVertexIndices
                        = compute_vertex_list.operator()(triples, *left_child_->getTripleIndices());
                left_child_->setVertexIndices(leftVertexIndices);
                left_child_->build(gauss_triangles_fit, vertices, triples, centers, areas);

                right_child_->setTripleIndices(result.getRightSideTriples());
                std::shared_ptr<std::vector<int unsigned>> rightVertexIndices
                        = compute_vertex_list.operator()(triples, *right_child_->getTripleIndices());
                right_child_->setVertexIndices(rightVertexIndices);
                right_child_->build(gauss_triangles_fit, vertices, triples, centers, areas);
            } else {
                /*delete left_child_;
                left_child_ = 0;

                delete right_child_;
                right_child_ = 0;*/
            }
        }
    }

    
    void SphereTree::initializeIndices(int unsigned n_vertex_indices, int unsigned n_triple_indices) {
        if (n_vertex_indices < n_triple_indices) {
            for (int unsigned i = 0; i < n_vertex_indices; ++i) {
                vertex_indices_->operator[](i) = triple_indices_->operator[](i) = i;
            }

            for (int unsigned i = n_vertex_indices; i < n_triple_indices; ++i) {
                triple_indices_->operator[](i) = i;
            }
        } else {
            for (int unsigned i = 0; i < n_triple_indices; ++i) {
                vertex_indices_->operator[](i) = triple_indices_->operator[](i) = i;
            }

            for
                (int unsigned i = n_triple_indices; i < n_vertex_indices; ++i) {
                vertex_indices_->operator[](i) = i;
            }
        }
    }

    
    void SphereTree::writeToBinaryFile(std::ofstream & out) const {
        assert(out);
        this->writeToBinaryFileAux(out);
    }

    
    int unsigned SphereTree::numberOfTrees()const {
        if (left_child_ != 0 && right_child_ != 0) {
            return 1 + left_child_->numberOfTrees() + right_child_->numberOfTrees();
        }

        return 1;
    }

    
    int unsigned SphereTree::numberOfTreesAtDepth(int unsigned depth)const {
        if (depth != 0) {
            int currentDepth = 0;
            int unsigned res = 0;

            if (getLeftChild() != 0) {
                res += getLeftChild()->numberOfTreesAtDepthAux(depth, currentDepth + 1);
            }

            if (getRightChild() != 0) {
                res += getRightChild()->numberOfTreesAtDepthAux(depth, currentDepth + 1);
            }

            return res;
        } else {
            return 1;
        }
    }

    
    int unsigned SphereTree::numberOfTreesAtDepthAux(int unsigned depth, int unsigned currentDepth)const {
        if (depth == currentDepth) {
            return 1;
        } else {
            int unsigned res = 0;

            if (getLeftChild() != 0) {
                res += getLeftChild()->numberOfTreesAtDepthAux(depth, currentDepth + 1);
            }

            if (getRightChild() != 0) {
                res += getRightChild()->numberOfTreesAtDepthAux(depth, currentDepth + 1);
            }

            return res;
        }
    }

    
    void SphereTree::writeToBinaryFileAux(std::ofstream & output) const {
        bool box_not_null = (sphere_ != 0);
        output.write(reinterpret_cast<const char*> (&box_not_null), sizeof ( bool));

        if (box_not_null) {
            output.write(reinterpret_cast<const char*> (&*sphere_), sizeof ( Sphere));
        } else {
            assert(triple_indices_->size() == 1);

            output.write(reinterpret_cast<const char*> (&(triple_indices_->operator[](0))), sizeof ( size_t));
        }

        bool left_not_null = (left_child_ != 0);
        output.write(reinterpret_cast<const char*> (&left_not_null), sizeof ( bool));

        if (left_not_null) {
            left_child_->writeToBinaryFileAux(output);
        }

        bool right_not_null = (right_child_ != 0);
        output.write(reinterpret_cast<const char*> (&right_not_null), sizeof ( bool));

        if (right_not_null) {
            right_child_->writeToBinaryFileAux(output);
        }
    }

    SphereTree::SphereTree(std::ifstream & read) {
        assert(read);

        this->fromBinaryFileAux(read);
    }

    
    void SphereTree::fromBinaryFileAux(std::ifstream & read) {
        bool box_not_null;
        read.read(reinterpret_cast<char*> (&box_not_null), sizeof ( bool));

        if (box_not_null) {
            sphere_ = std::shared_ptr<Sphere>(new Sphere());
            read.read(reinterpret_cast<char*> (&*sphere_), sizeof ( Sphere));
        } else {
            triple_indices_->resize(1);
            read.read(reinterpret_cast<char*> (&triple_indices_->operator[](0)), sizeof ( size_t));
        }

        bool left_not_null;
        read.read(reinterpret_cast<char*> (&left_not_null), sizeof ( bool));

        if (left_not_null) {
            left_child_ = std::shared_ptr<SphereTree>(new SphereTree());
            left_child_->fromBinaryFileAux(read);
        }

        bool right_not_null;
        read.read(reinterpret_cast<char*> (&right_not_null), sizeof ( bool));

        if (right_not_null) {
            right_child_ = std::shared_ptr<SphereTree>(new SphereTree());
            right_child_->fromBinaryFileAux(read);
        }
    }

    
    std::ostream & operator<<(std::ostream & out, SphereTree const & obbt) {
        out << "###\n";

        if (obbt.getSphere() != 0) {
            out << "box:\n" << *obbt.getSphere() << "\n\n";
        }

        if (obbt.numberOfTripleIndices() != 0) {
            out << "***number of triple indices: ";
            out << obbt.numberOfTripleIndices() << "\n\n";
        }

        if (obbt.getLeftChild() != 0) {
            out << "***left_child_ =\n" << *obbt.getLeftChild() << "\n\n";
        } else {
            out << "***left_child_ is null\n\n";
        }

        if (obbt.getRightChild() != 0) {
            out << "***right_child =\n" << *obbt.getRightChild() << "\n\n";
        } else {
            out << "***right_child is null\n\n";
        }

        out << "\n";

        return out;
    }

    
    Real SphereTree::volume() const {
        if (getSphere() != 0) {
            Real res = getSphere()->volume();

            if (getLeftChild()) {
                res += getLeftChild()->volume();
            }

            if (getRightChild()) {
                res += getRightChild()->volume();
            }

            return res;
        }

        return (Real) 0.0;
    }
}