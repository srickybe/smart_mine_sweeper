#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include <memory>
#include <vector>
#include "Mesh.h"
#include "Real.h"

namespace ngn {
    
	class Vector3D;
	
    class MeshBuilder {
    public:
		class CompareVector3D {
		public:
			CompareVector3D();
			bool operator()(Vector3D const & a, Vector3D const & b) const;
		};
	
		static SharedPtrMesh boxMesh(Real xLength, Real yLength, Real zLength);
		static SharedPtrMesh unitCircleMesh(int numberOfPoints);
        static SharedPtrMesh unitCubeMesh();
		static SharedPtrMesh unitDiskMesh(int numberOfPoints);
        static SharedPtrMesh unitSphereMesh(int levelOfDetail);
		static SharedPtrMesh icosahedron();
        static SharedPtrMesh icosahedron(Real radius);
		static SharedPtrMesh icosahedron(Real radius, int unsigned levelOfDetail);
        static SharedPtrMesh refineIcosahedron(Mesh const & mesh, Real radius);
		//static void rotate(SharedPtrMesh & mesh, Matrix3D const & rotation);
		//static void translate(SharedPtrMesh & mesh, Vector3D const & translation);
		
    private:
		static std::pair<std::shared_ptr<std::vector<Triangle>>, std::shared_ptr<std::vector<Vector3D>>>
		divideTrianglesInFour(
			std::vector<Triangle> const & triples,
			std::vector<Vector3D> const & points
		);
    };

    ////////////////////////////////////////////////////////////////////////////////

}

#endif // MESH_BUILDER_H