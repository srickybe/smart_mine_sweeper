#ifndef SPHERE_TREE_H
#define SPHERE_TREE_H

#include "BoundingVolumeBuilder3D.h"
#include "ComputeVertexList.h"
#include "GaussPointsFit.h"
#include "GaussTrianglesFit.h"
#include "OrientedBox3D.h"
#include "PartitionTriangles.h"
#include "Triangle.h"
#include "Vector3D.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace ngn {
    class GaussPointsFit;
    class GaussTrianglesFit;
    class OrientedBox3D;
    //class VertexIndices;
    class Vector3D;

    
    class SphereTree {
    public:
        SphereTree();

        SphereTree
        (
			GaussPointsFit const & functor, //Functor to compute box
			std::vector<Vector3D> const & vertices, //vertices
			std::vector<Triangle> const & triples, //triples
			std::vector<Vector3D> const & centers//triangles centers
		);

        SphereTree
        (
			GaussTrianglesFit const &, //Functor to compute box
			std::vector<Vector3D> const & vertices, //vertices
			std::vector<Triangle> const & triples, //triples
			std::vector<Vector3D> const & centers, //triangles centers
			std::vector<Real> const & areas //triangle areas
		);

        SphereTree(std::ifstream & read);

        bool equals(SphereTree const & rhs, Real tol)const;
        std::shared_ptr<SphereTree> const & getLeftChild()const;
        std::shared_ptr<SphereTree> const & getRightChild()const;
        std::shared_ptr<Sphere> const & getSphere()const;
        std::shared_ptr<std::vector<int unsigned>> getTripleIndices()const;
        std::shared_ptr<std::vector<int unsigned>> getVertexIndices()const;
        int unsigned tripleIndex(int unsigned i)const;
        int unsigned vertexIndex(int unsigned i)const;

        void setTripleIndices(std::shared_ptr<std::vector<int unsigned>> const &);
        void setVertexIndices(std::shared_ptr<std::vector<int unsigned>> const &);

        int unsigned numberOfTrees()const;
        int unsigned numberOfTreesAtDepth(int unsigned depth)const;
        int unsigned numberOfTripleIndices()const;
        int unsigned numberOfVertexIndices()const;
        Real volume()const;
        void writeToBinaryFile(std::ofstream &)const;

    private:
        std::shared_ptr<SphereTree> left_child_;
        std::shared_ptr<SphereTree> right_child_;
        std::shared_ptr<Sphere> sphere_;
        std::shared_ptr<std::vector< int unsigned >> triple_indices_;
        std::shared_ptr<std::vector< int unsigned >> vertex_indices_;

        void build
        (
			GaussPointsFit const & functor, //Functor to compute box
			std::vector<Vector3D> const & vertices, //vertices
			std::vector<Triangle> const & triples, //triples
			std::vector<Vector3D> const & centers//triangles centers
		);

        void build
        (
			GaussTrianglesFit const &, //Functor to compute box
			std::vector<Vector3D> const & vertices, //vertices
			std::vector<Triangle> const & triples, //triples
			std::vector<Vector3D> const & centers, //triangles centers
			std::vector<Real> const & areas //triangle areas
		);

        void fromBinaryFile(std::ifstream &);
        void fromBinaryFileAux(std::ifstream &);
        std::shared_ptr<SphereTree> getLeftChild();
        std::shared_ptr<SphereTree> getRightChild();
        void initializeIndices(int unsigned n_vertex_indices, int unsigned n_triple_indices);
        int unsigned numberOfTreesAtDepthAux(int unsigned depth, int unsigned currentDepth)const;
        void writeToBinaryFileAux(std::ofstream &)const;
    };

    
    std::ostream & operator<<(std::ostream & out, SphereTree const & obbt);

    ////////////////////////////////////////////////////////////////////////
}

#endif /* SPHERE_TREE_H */
