#include "Octree.h"

namespace ngn {
	
    int unsigned const Octree::N_CHILDREN_ = 8;

    int Octree::n_objects_ = 0;

    boost::shared_array<std::shared_ptr<OrientedBox3D>>
    Octree::divideInEightBoxes(std::shared_ptr<OrientedBox3D> const & box) {

        boost::shared_array<std::shared_ptr<OrientedBox3D>> boxes(new std::shared_ptr<OrientedBox3D>[8]);
        Vector3D newHalfExtents(Vector3D::div(box->getHalfExtents(), (Real) 2.0));
        int count = 0;

        for (int i = 0; i < 2; ++i) {
            Real x;
            Real y;
            Real z;

            if (i == 0) {
                x = newHalfExtents.getX();
            } else {
                x = -newHalfExtents.getX();
            }

            for (int j = 0; j < 2; ++j) {
                if (j == 0) {
                    y = newHalfExtents.getY();
                } else {
                    y = -newHalfExtents.getY();
                }

                for (int k = 0; k < 2; ++k) {
                    if (k == 0) {
                        z = newHalfExtents.getZ();
                    } else {
                        z = -newHalfExtents.getZ();
                    }

                    Vector3D distance(x, y, z);
                    Vector3D distanceInWorldCoordinates = box->getOrientation().mult(distance);
                    Vector3D center(Vector3D::add(box->getCenter(), distanceInWorldCoordinates));
                    boxes[count] = std::shared_ptr<OrientedBox3D> (
                            new OrientedBox3D(center, box->getOrientation(), newHalfExtents));
                    /*std::cout << "box_" << count << *(boxes[count]) << "\n";*/
                    ++count;
                }
            }
        }

        return boxes;
    }

    
    Octree::Octree()
    : vertexIndexes_(new std::vector<int unsigned>()),
    tripleIndexes_(new std::vector<int unsigned>()) {

    }

    
    void Octree::addTripleIndex(int unsigned tripleIndex) {
        this->tripleIndexes_->push_back(tripleIndex);
    }

    
    std::shared_ptr<OrientedBox3D> const & Octree::getBox()const {
        return box_;
    }

    
    std::shared_ptr<Octree> const & Octree::getChild(int i) const {
        return this->children_.at(i);
    }

    
    std::shared_ptr<Octree> Octree::getChild(int i) {
        return this->children_.at(i);
    }

    
    std::shared_ptr<Sphere> const & Octree::getSphere()const {
        return sphere_;
    }

    
    void Octree::setBox(std::shared_ptr<OrientedBox3D> const & box) {
        box_ = box;
    }

    
    void Octree::setChild(int i, std::shared_ptr<Octree> child) {
        this->children_.at(i) = child;
    }

    
    void Octree::setSphere(const std::shared_ptr<Sphere>&sphere) {
        sphere_ = sphere;
    }

    
    void Octree::setVertexIndexes(std::shared_ptr<std::vector<int unsigned>> const & vertexIndexes) {
        vertexIndexes_ = vertexIndexes;
    }

    
    void Octree::setTripleIndexes(std::shared_ptr<std::vector<int unsigned>> const & tripleIndexes) {
        tripleIndexes_ = tripleIndexes;
    }

    
    void Octree::initializeVertexIndices(int unsigned nVertices) {
        for (int unsigned i = 0; i < nVertices; ++i) {
            this->vertexIndexes_->push_back(i);
        }
    }

    
    void Octree::initializeTripleIndices(int unsigned nTriples) {
        for (int unsigned i = 0; i < nTriples; ++i) {
            this->tripleIndexes_->push_back(i);
        }
    }

    
    int unsigned Octree::numberOfChildren() const {
        return this->children_.size();
        //return N_CHILDREN_;
    }

    
    void Octree::setChildrenBoxes(boost::shared_array<std::shared_ptr<OrientedBox3D> >& childrenBoxes) {
        for (int unsigned i = 0; i < this->numberOfChildren(); ++i) {
            this->children_[i]->setBox(childrenBoxes[i]);
        }
    }

    
    void Octree::divideCentersBetweenChildren(
            const std::vector<Vector3D >& centers) {

        for (int unsigned i = 0; i < this->tripleIndexes_->size(); ++i) {
            int unsigned tripleIndex = this->tripleIndexes_->operator[](i);
            Vector3D center = centers.operator[](tripleIndex);

            assert(this->box_->contains(center));

            bool isAffected = false;

            for (int unsigned j = 0; j < numberOfChildren() && !isAffected; ++j) {
                std::shared_ptr<Octree> child = this->getChild(j);

                if (child->getBox()->contains(center)) {
                    child->addTripleIndex(tripleIndex);
                    isAffected = true;
                }
            }

            if (!isAffected) {
                std::cout << "i = " << i << "\n";
                std::cout << "tripleIndex = " << tripleIndex << "\n";
                std::cout << "centers[" << i << "] = " << centers.operator[](tripleIndex) << "\n";

                for (int unsigned j = 0; j < numberOfChildren() && !isAffected; ++j) {
                    std::shared_ptr<Octree> child = this->getChild(j);
                    std::cout << "box =\n" << *(child->getBox()) << "\n";
                    std::cout << "\ntest_" << j << " = " << (child->getBox()->contains(center)) << "\n";
                }

				std::string message = "Octree::divideCentersBetweenChildren(...)";
				message += "\n!isAffected\n";
                throw IllegalArgumentException(message);
            }
        }
    }

    
    void Octree::allocateChildren() {
        this->children_.resize(N_CHILDREN_);

        for (int unsigned i = 0; i < this->N_CHILDREN_; ++i) {
            this->children_[i] = std::shared_ptr<Octree> (new Octree());
        }
    }

    
    void Octree::deallocateEmptyChildren() {
        for (int unsigned i = 0; i < this->numberOfChildren(); ++i) {
            if (this->getChild(i)->tripleIndexes_->empty()) {
                this->setChild(i, std::shared_ptr<Octree> ());
            }
        }
    }

    
    void Octree::computeChildrenVertexIndexes(std::vector<Triangle> const & triples) {
        ComputeVertexList cvl;

        for (int unsigned i = 0; i < this->numberOfChildren(); ++i) {
            std::shared_ptr<Octree> child = this->getChild(i);

            if (child != 0) {
                child->vertexIndexes_ = cvl.operator()(triples, *child->tripleIndexes_);
            }
        }
    }

    
    void Octree::initializeChildren(
            std::vector<Vector3D> const & centers,
            std::vector<Triangle> const & triples) {

        boost::shared_array<std::shared_ptr<OrientedBox3D>> childrenBoxes
                = this->divideInEightBoxes(this->getBox());
        this->allocateChildren();
        this->setChildrenBoxes(childrenBoxes);
        this->divideCentersBetweenChildren(centers);
        this->deallocateEmptyChildren();
        this->computeChildrenVertexIndexes(triples);
    }

    
    Octree::Octree(
            GaussTrianglesFit gaussTrianglesFit,
            std::vector<Vector3D> const & vertices,
            std::vector<Triangle> const & triples,
            std::vector<Vector3D> const & centers,
            std::vector<Real> const & areas,
            int maxDepth)
    : vertexIndexes_(new std::vector<int unsigned>(vertices.size())),
    tripleIndexes_(new std::vector<int unsigned>(triples.size())) {

        assert(!vertices.empty());
        assert(!triples.empty());
        assert(!centers.empty());
        assert(!areas.empty());
        assert(centers.size() == triples.size());
        assert(areas.size() == triples.size());
        assert(maxDepth > 0);

        ++n_objects_;
        BoundingVolumeBuilder3D bvb;
        std::shared_ptr<Sphere> sphere(new Sphere(bvb.computeBoundingSphere(vertices)));
        this->setSphere(sphere);

        std::shared_ptr<OrientedBox3D> box(
			new OrientedBox3D(
				bvb.computeBoundingOrientedBox3D(
					gaussTrianglesFit,
					vertices,
					triples,
					centers,
					areas
                )
			)
		);

        this->setBox(box);
        this->initializeVertexIndices(vertices.size());
        this->initializeTripleIndices(triples.size());
        this->initializeChildren(centers, triples);

        int currentDepth = 0;

        for (int unsigned i = 0; i < numberOfChildren(); ++i) {
            if (this->children_[i] != 0) {
                this->children_[i]->build(vertices, triples, centers, maxDepth, currentDepth + 1);
            }
        }
    }

    
    void Octree::build(
            std::vector<Vector3D> const & vertices,
            std::vector<Triangle> const & triples,
            std::vector<Vector3D> const & centers,
            int maxDepth,
            int currentDepth) {

        ++n_objects_;

        if (!this->vertexIndexes_->empty() && currentDepth < maxDepth) {
            BoundingVolumeBuilder3D bvb;
            std::shared_ptr<Sphere> sphere(new Sphere(bvb.computeBoundingSphere(vertices, *this->vertexIndexes_)));
            this->setSphere(sphere);
            this->initializeChildren(centers, triples);

            for (int unsigned i = 0; i < numberOfChildren(); ++i) {
                if (this->children_[i] != 0) {
                    this->children_[i]->build(vertices, triples, centers, maxDepth, currentDepth + 1);
                }
            }
        } else {
            this->setSphere(std::shared_ptr<Sphere> ());
            this->setBox(std::shared_ptr<OrientedBox3D> ());
            this->setVertexIndexes(std::shared_ptr<std::vector<int unsigned>>());
            this->setTripleIndexes(std::shared_ptr<std::vector<int unsigned>>());
            children_.clear();
        }
    }

    
    int unsigned Octree::numberOfTrees()const {
        int unsigned res = 1;

        for (int unsigned i = 0; i < this->numberOfChildren(); ++i) {
            if (this->getChild(i) != 0) {
                res += this->getChild(i)->numberOfTrees();
            }
        }

        return res;
    }

    
    int unsigned Octree::numberOfTreesAtDepth(int unsigned depth)const {
        int unsigned currentDepth = 0;

        if (currentDepth == depth) {
            return 1;
        } else {
            int res = 0;

            for (int unsigned i = 0; i < numberOfChildren(); ++i) {
                if (getChild(i) != 0) {
                    res += getChild(i)->numberOfTreesAtDepthAux(depth, currentDepth + 1);
                }
            }

            return res;
        }
    }

    
    int unsigned Octree::numberOfTreesAtDepthAux(
            int unsigned depth,
            int unsigned currentDepth
            )const {
        if (currentDepth == depth) {
            return 1;
        } else {
            int res = 0;

            for (int unsigned i = 0; i < numberOfChildren(); ++i) {
                if (getChild(i) != 0) {
                    res += getChild(i)->numberOfTreesAtDepthAux(depth, currentDepth + 1);
                }
            }

            return res;
        }
    }
}