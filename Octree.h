#ifndef OCTREE_H
#define OCTREE_H

#include <boost/shared_array.hpp>
#include <memory>
#include "BoundingVolumeBuilder3D.h"
#include "GaussTrianglesFit.h"
#include "IllegalArgumentException.h"
#include "OrientedBox3D.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vector3D.h"
#include "ComputeVertexList.h"

namespace ngn {

    class GaussTrianglesFit;
    class Sphere;

    
    class Octree {
    public:
        typedef std::shared_ptr<Sphere> SpherePtr;
        typedef std::shared_ptr<OrientedBox3D> BoxPtr;
        typedef std::shared_ptr<Octree> OctreePtr;

        Octree();

        Octree(
                GaussTrianglesFit gaussTrianglesFit,
                std::vector<Vector3D> const & vertices,
                std::vector<Triangle> const & triangles,
                std::vector<Vector3D> const & centers,
                std::vector<Real> const & areas,
                int maxDepth);

        void addTripleIndex(int unsigned tripleIndex);
        BoxPtr const & getBox() const;
        OctreePtr const & getChild(int i) const;
        OctreePtr getChild(int i);
        SpherePtr const & getSphere() const;
        int unsigned numberOfChildren() const;
        int unsigned numberOfTrees()const;
        int unsigned numberOfTreesAtDepth(int unsigned depth)const;

        void setBox(BoxPtr const & box);
        void setChild(int i, OctreePtr child);
        void setSphere(SpherePtr const & sphere);
        void setVertexIndexes(std::shared_ptr<std::vector<int unsigned>> const & vertexIndexes);
        void setTripleIndexes(std::shared_ptr<std::vector<int unsigned>> const & tripleIndexes);

    private:
        static int unsigned const N_CHILDREN_;
        static int n_objects_;
        SpherePtr sphere_;
        BoxPtr box_;
        std::shared_ptr<std::vector<int unsigned>> vertexIndexes_;
        std::shared_ptr<std::vector<int unsigned>> tripleIndexes_;
        std::vector<OctreePtr> children_;

        void allocateChildren();

        void build
        (
                std::vector<Vector3D> const & vertices, //vertices
                std::vector<Triangle> const & triples, //triples
                std::vector<Vector3D> const & centers, //triangles centers
                int maxDepth,
                int currentDepth);

        void computeChildrenVertexIndexes(std::vector<Triangle> const & triples);
        void deallocateEmptyChildren();
        void divideCentersBetweenChildren(std::vector<Vector3D > const & centers);
        boost::shared_array<BoxPtr> divideInEightBoxes(BoxPtr const & box);
        void initializeChildren(std::vector<Vector3D> const & centers, std::vector<Triangle> const & triples);
        void initializeTripleIndices(int unsigned nTriples);
        void initializeVertexIndices(int unsigned nVertices);
        int unsigned numberOfTreesAtDepthAux(int unsigned depth, int unsigned currentDepth)const;
        void setChildrenBoxes(boost::shared_array<BoxPtr>& childrenBoxes);
    };

    ////////////////////////////////////////////////////////////////////////////////
}

#endif /* OCTREE_H */
