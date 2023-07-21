#ifndef ORIENTED_BOX_3D_TREE_H
#define ORIENTED_BOX_3D_TREE_H

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "Real.h"

namespace ngn {

	class GaussPointsFit;
	class GaussTrianglesFit;
	class OrientedBox3D;
	class Triangle;
    class Vector3D;
	
    class OrientedBox3DTree {
    public:
        OrientedBox3DTree();

        OrientedBox3DTree
        (
                GaussPointsFit const & functor, //Functor to compute box
                std::vector<Vector3D> const & vertices, //vertices
                std::vector<Triangle> const & triples, //triples
                std::vector<Vector3D> const & centers//triangles centers
                );

        OrientedBox3DTree
        (
                GaussTrianglesFit const &, //Functor to compute box
                std::vector<Vector3D> const & vertices, //vertices
                std::vector<Triangle> const & triples, //triples
                std::vector<Vector3D> const & centers, //triangles centers
                std::vector<Real> const & areas //triangle areas
                );

        OrientedBox3DTree(std::ifstream & read);
        ~OrientedBox3DTree();

        bool equals(OrientedBox3DTree const & rhs, Real tol)const;
        std::shared_ptr<OrientedBox3DTree> const & getLeftChild()const;
        std::shared_ptr<OrientedBox3DTree> const & getRightChild()const;
        std::shared_ptr<OrientedBox3D> const & getBox()const;
        int unsigned getTripleIndex(int unsigned i)const;
		std::shared_ptr<std::vector<int unsigned>> const & getTripleIndices() const;
        int unsigned getVertexIndex(int unsigned i)const;
		std::shared_ptr<std::vector<int unsigned>> const & getVertexIndices() const;
		
		void setBox(std::shared_ptr<OrientedBox3D> const & box);
		void setLeftChild(std::shared_ptr<OrientedBox3DTree> const & leftChild);
		void setRightChild(std::shared_ptr<OrientedBox3DTree> const & rightChild);
		void setTripleIndex(int unsigned index, int unsigned value);
		void setVertexIndex(int unsigned index, int unsigned value);
		void setTripleIndices(std::shared_ptr<std::vector< int unsigned >> const & tripleIndices);
		void setVertexIndices(std::shared_ptr<std::vector< int unsigned >> const & vertexIndices);

        int unsigned number0fTrees()const;
        int unsigned numberOfTripleIndices()const;
        int unsigned numberOfVertexIndices()const;
        Real volume()const;
        void writeToBinaryFile(std::ofstream &)const;

    private:
        std::shared_ptr<OrientedBox3DTree> leftChild_;
        std::shared_ptr<OrientedBox3DTree> rightChild_;
        std::shared_ptr<OrientedBox3D> box_;
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
        std::shared_ptr<OrientedBox3DTree> getLeftChild();
        std::shared_ptr<OrientedBox3DTree> getRightChild();
        void initializeIndices(int unsigned n_vertex_indices, int unsigned n_triple_indices);
        void writeToBinaryFileAux(std::ofstream &)const;
    };

    
    std::ostream & operator<<(std::ostream & out, OrientedBox3DTree const & obbt);

    ////////////////////////////////////////////////////////////////////////
}

#endif // ORIENTED_BOX_3D_TREE_H