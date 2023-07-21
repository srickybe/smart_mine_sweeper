#include "OrientedBox3DTree.h"
#include "BoundingVolumeBuilder3D.h"
#include "ComputeVertexList.h"
#include "GaussPointsFit.h"
#include "GaussTrianglesFit.h"
#include "OrientedBox3D.h"
#include "PartitionTriangles.h"
#include "Triangle.h"
#include "Vector3D.h"

namespace ngn {
	

     OrientedBox3DTree::OrientedBox3DTree()
    : leftChild_(),
    rightChild_(),
    box_(),
    triple_indices_(new std::vector<int unsigned>()),
    vertex_indices_(new std::vector<int unsigned>()) {
    }

     OrientedBox3DTree::OrientedBox3DTree(
            GaussPointsFit const & gauss_points_fit,
            std::vector<Vector3D> const & vertices,
            std::vector<Triangle> const & triples, //triples
            std::vector<Vector3D> const & centers //triangle centers
            )
    : leftChild_(),
    rightChild_(),
    box_(),
    triple_indices_(new std::vector<int unsigned>(triples.size())),
    vertex_indices_(new std::vector<int unsigned>(vertices.size())) {
        this->initializeIndices(vertices.size(), triples.size());
        this->build(gauss_points_fit, vertices, triples, centers);
    }

     OrientedBox3DTree::OrientedBox3DTree
    (
            GaussTrianglesFit const & gauss_triangles_fit,
            std::vector<Vector3D> const & vertices,
            std::vector<Triangle> const & triples,
            std::vector<Vector3D> const & centers,
            std::vector<Real> const & areas
            )
    : leftChild_(),
    rightChild_(),
    box_(),
    triple_indices_(new std::vector<int unsigned>(triples.size())),
    vertex_indices_(new std::vector<int unsigned>(vertices.size())) {
        this->initializeIndices(vertices.size(), triples.size());
        this->build(gauss_triangles_fit, vertices, triples, centers, areas);
    }

     OrientedBox3DTree::~OrientedBox3DTree() {
    }

    
    bool OrientedBox3DTree::equals(OrientedBox3DTree const & rhs, Real tol) const {
        if (this->getBox() != 0) {
            if (rhs.getBox() != 0) {
                if (!this->getBox()->equals(*(rhs.getBox()), tol)) {
                    return false;
                }

                if (this->numberOfTripleIndices() != rhs.numberOfTripleIndices()) {
                    return false;
                }

                for (int unsigned i = 0; i < this->numberOfTripleIndices(); ++i) {
                    if (this->getTripleIndex(i) != rhs.getTripleIndex(i)) {
                        return false;
                    }
                }
            } else {
                return false;
            }
        } else {
            if (rhs.getBox() != 0) {
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
    
    
    std::shared_ptr<OrientedBox3DTree> const &
    OrientedBox3DTree::getLeftChild()const {
        return leftChild_;
    }

    
    std::shared_ptr<OrientedBox3DTree>
    OrientedBox3DTree::getLeftChild() {
        return leftChild_;
    }

    void
    OrientedBox3DTree::setLeftChild(std::shared_ptr<OrientedBox3DTree> const & leftChild) {
        leftChild_ = leftChild;
    }
	
    std::shared_ptr<OrientedBox3DTree> const &
    OrientedBox3DTree::getRightChild()const {
        return rightChild_;
    }

    
    std::shared_ptr<OrientedBox3DTree>
    OrientedBox3DTree::getRightChild() {
        return rightChild_;
    }

    
    void
    OrientedBox3DTree::setRightChild(std::shared_ptr<OrientedBox3DTree> const & rightChild) {
        rightChild_ = rightChild;
    }
	
    std::shared_ptr<OrientedBox3D> const &
    OrientedBox3DTree::getBox()const {
        return box_;
    }

    void OrientedBox3DTree::setBox(std::shared_ptr<OrientedBox3D> const & box) {
		box_ = box;
	}
	
    int unsigned OrientedBox3DTree::getTripleIndex(int unsigned i)const {
        assert(i < numberOfTripleIndices());

        return getTripleIndices()->operator [](i);
    }

    std::shared_ptr<std::vector<int unsigned>> const & OrientedBox3DTree::getTripleIndices() const {
		return triple_indices_;
	}
	
    int unsigned OrientedBox3DTree::getVertexIndex(int unsigned i)const {
        assert(i < numberOfVertexIndices());

        return getVertexIndices()->operator [](i);
    }

    std::shared_ptr<std::vector<int unsigned>> const & OrientedBox3DTree::getVertexIndices() const {
		return vertex_indices_;
	}
	
    int unsigned OrientedBox3DTree::numberOfTripleIndices()const {
        return getTripleIndices()->size();
    }

    
    int unsigned OrientedBox3DTree::numberOfVertexIndices()const {
        return getVertexIndices()->size();
    }

    void OrientedBox3DTree::setTripleIndices(std::shared_ptr<std::vector< int unsigned >> const & tripleIndices) {
		triple_indices_ = tripleIndices;
	}
	
    void OrientedBox3DTree::setVertexIndices(std::shared_ptr<std::vector< int unsigned >> const & vertexIndices) {
		vertex_indices_ = vertexIndices;
	}
	
	void OrientedBox3DTree::setTripleIndex(int unsigned index, int unsigned value) {
		triple_indices_->operator [](index) = value;
	}
	
	void OrientedBox3DTree::setVertexIndex(int unsigned index, int unsigned value) {
		getVertexIndices()->operator [](index) = value;
	}
		
    void OrientedBox3DTree::build
    (
            GaussPointsFit const & gauss_points_fit,
            std::vector<Vector3D> const & vertices,
            std::vector<Triangle> const & triples,
            std::vector<Vector3D> const & centers
            ) {
        if (numberOfTripleIndices() > 1) {
            BoundingVolumeBuilder3D compute_bounding_volume;
            setBox(
				std::shared_ptr<OrientedBox3D>(
					new OrientedBox3D(
						compute_bounding_volume.computeBoundingOrientedBox3D(
							gauss_points_fit, 
							vertices, 
							*getVertexIndices()
						)
					)
				)
			);

            setLeftChild(std::shared_ptr<OrientedBox3DTree>(new OrientedBox3DTree()));
            setRightChild(std::shared_ptr<OrientedBox3DTree>(new OrientedBox3DTree()));

            PartitionTriangles partition_triangles;
            PartitionTriangles::Result result = 
                    partition_triangles.operator()(*(getBox()), centers, *getTripleIndices());

            if (result.partitioned()) {
                getLeftChild()->setTripleIndices(result.getLeftSideTriples());
                ComputeVertexList compute_vertex_list;
                getLeftChild()->setVertexIndices(compute_vertex_list.operator()(triples, *getLeftChild()->getTripleIndices()));
                getLeftChild()->build(gauss_points_fit, vertices, triples, centers);
                
                getRightChild()->setTripleIndices(result.getRightSideTriples());
                getRightChild()->setVertexIndices(compute_vertex_list.operator ()(triples, *getRightChild()->getTripleIndices()));
                getRightChild()->build(gauss_points_fit, vertices, triples, centers);
            } else {
                /*delete leftChild_;
                setLeftChild(0;

                delete rightChild_;
                setRightChild(0;*/
            }
        }
    }

     void OrientedBox3DTree::build
    (
            GaussTrianglesFit const & gauss_triangles_fit,
            std::vector<Vector3D> const & vertices,
            std::vector<Triangle> const & triples,
            std::vector<Vector3D> const & centers,
            std::vector<Real> const & areas
            ) {
        if (numberOfTripleIndices() > 1) {
            BoundingVolumeBuilder3D compute_bounding_volume;
            setBox(
				std::shared_ptr<OrientedBox3D>(
					new OrientedBox3D(
						compute_bounding_volume.computeBoundingOrientedBox3D(
							gauss_triangles_fit, 
							vertices, 
							*getVertexIndices(), 
							triples, 
							*getTripleIndices(), 
							centers, 
							areas
						)
					)
				)
			);

            setLeftChild(std::shared_ptr<OrientedBox3DTree>(new OrientedBox3DTree()));
            setRightChild(std::shared_ptr<OrientedBox3DTree>(new OrientedBox3DTree()));

            PartitionTriangles partition_triangles;
            PartitionTriangles::Result result = 
                    partition_triangles.operator()(*(getBox()), centers, *getTripleIndices());

            if (result.partitioned()) {
                getLeftChild()->setTripleIndices(result.getLeftSideTriples());
                ComputeVertexList compute_vertex_list;
                getLeftChild()->setVertexIndices(compute_vertex_list.operator ()(triples, *getLeftChild()->getTripleIndices()));
                getLeftChild()->build(gauss_triangles_fit, vertices, triples, centers, areas);

                getRightChild()->setTripleIndices(result.getRightSideTriples());
                getRightChild()->setVertexIndices(compute_vertex_list.operator ()(triples, *getRightChild()->getTripleIndices()));
                getRightChild()->build(gauss_triangles_fit, vertices, triples, centers, areas);
            } else {
                /*delete leftChild_;
                setLeftChild(0;

                delete rightChild_;
                setRightChild(0;*/
            }
        }
    }

    
    void OrientedBox3DTree::initializeIndices(int unsigned n_vertex_indices, int unsigned n_triple_indices) {
        if (n_vertex_indices < n_triple_indices) {
            for (int unsigned i = 0; i < n_vertex_indices; ++i) {
                setVertexIndex(i, i);
				setTripleIndex(i, i);
            }

            for (int unsigned i = n_vertex_indices; i < n_triple_indices; ++i) {
                setTripleIndex(i, i);
            }
        } else {
            for (int unsigned i = 0; i < n_triple_indices; ++i) {
                setVertexIndex(i, i);
				setTripleIndex(i, i);
            }

            for
                (int unsigned i = n_triple_indices; i < n_vertex_indices; ++i) {
                setVertexIndex(i, i);
            }
        }
    }

    
    void OrientedBox3DTree::writeToBinaryFile(std::ofstream & out) const {
        assert(out);
        this->writeToBinaryFileAux(out);
    }

    
    int unsigned OrientedBox3DTree::number0fTrees()const {
        if (leftChild_ != 0 && rightChild_ != 0) {
            return 1 + getLeftChild()->number0fTrees() + getRightChild()->number0fTrees();
        }

        return 1;
    }

    
    void OrientedBox3DTree::writeToBinaryFileAux(std::ofstream & output) const {
        bool box_not_null = (getBox() != 0);
        output.write(reinterpret_cast<const char*>(&box_not_null), sizeof ( bool));

        if (box_not_null) {
            output.write(reinterpret_cast<const char*>(&*getBox()), sizeof (OrientedBox3D));
        } else {
            assert(numberOfTripleIndices() == 1);

            output.write(reinterpret_cast<const char*>(&(getTripleIndices()->operator [](0))), sizeof ( size_t));
        }

        bool left_not_null = (leftChild_ != 0);
        output.write(reinterpret_cast<const char*>(&left_not_null), sizeof ( bool));

        if (left_not_null) {
            getLeftChild()->writeToBinaryFileAux(output);
        }

        bool right_not_null = (rightChild_ != 0);
        output.write(reinterpret_cast<const char*>(&right_not_null), sizeof ( bool));

        if (right_not_null) {
            getRightChild()->writeToBinaryFileAux(output);
        }
    }

     OrientedBox3DTree::OrientedBox3DTree(std::ifstream & read) {
        assert(read);

        this->fromBinaryFileAux(read);
    }

    
    void OrientedBox3DTree::fromBinaryFileAux(std::ifstream & read) {
        bool box_not_null;
        read.read(reinterpret_cast<char*>(&box_not_null), sizeof ( bool));

        if (box_not_null) {
            setBox(std::shared_ptr<OrientedBox3D>(new OrientedBox3D()));
            read.read(reinterpret_cast<char*>(&*getBox()), sizeof (OrientedBox3D));
        } else {
            getTripleIndices()->resize(1);
            read.read(reinterpret_cast<char*>(&getTripleIndices()->operator [](0)), sizeof ( size_t));
        }

        bool left_not_null;
        read.read(reinterpret_cast<char*>(&left_not_null), sizeof ( bool));

        if (left_not_null) {
            setLeftChild(std::shared_ptr<OrientedBox3DTree>(new OrientedBox3DTree()));
            getLeftChild()->fromBinaryFileAux(read);
        }

        bool right_not_null;
        read.read(reinterpret_cast<char*>(&right_not_null), sizeof ( bool));

        if (right_not_null) {
            setRightChild(std::shared_ptr<OrientedBox3DTree>(new OrientedBox3DTree()));
            getRightChild()->fromBinaryFileAux(read);
        }
    }

    
    std::ostream & operator<<(std::ostream & out, OrientedBox3DTree const & obbt) {
        out << "###\n";

        if (obbt.getBox() != 0) {
            out << "box:\n" << *obbt.getBox() << "\n\n";
        }

        if (obbt.numberOfTripleIndices() != 0) {
            out << "***number of triple indices: ";
            out << obbt.numberOfTripleIndices() << "\n\n";
        }

        if (obbt.getLeftChild() != 0) {
            out << "***leftChild_ =\n" << *obbt.getLeftChild() << "\n\n";
        } else {
            out << "***leftChild_ is null\n\n";
        }

        if (obbt.getRightChild() != 0) {
            out << "***right_child =\n" << *obbt.getRightChild() << "\n\n";
        } else {
            out << "***right_child is null\n\n";
        }

        out << "\n";

        return out;
    }

    
    Real OrientedBox3DTree::volume() const{
        if (getBox() != 0) {
            Real res = getBox()->volume();

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