#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glu.h>
#include <memory>
#include <vector>
#include "Real.h"

namespace ngn {

	class AxisAngle;
	class Intersectable;
	class Matrix3D;
	class Mesh;
	class Model;
	class Octree;
	class OrientedBox3D;
	class OrientedBox3DTree;
	class OrientedEllipsoid;
	class Polygon;
	class Sphere;
	class SphereTree;
	class Triangle;
	class Vector3D;
	
    class Renderer {
    public:
        Renderer();
        ~Renderer();

		void render(std::vector<Vector3D> const &, std::vector<Triangle> const &) const;

		void render(Vector3D const & origin, Matrix3D const & basis)const;

        void render(Mesh const &) const;
		
		void render(Vector3D const & position, AxisAngle const & axisAngle, Mesh const & mesh) const;
		
		void render(Vector3D const & position, Matrix3D const & orientation, Mesh const & mesh) const;

		void render(Model const &) const;

        void render(OrientedBox3D const &) const;

        void render(OrientedBox3DTree const &) const;

        void render(OrientedBox3DTree const & obt, int unsigned depth) const;

        void render(OrientedBox3DTree const & obt, int unsigned depth, int unsigned current_depth) const;

        void render(SphereTree const & st)const;

        void render(SphereTree const & st, int unsigned depth) const;

        void render(SphereTree const & st, int unsigned depth, int unsigned current_depth) const;

        void render(Octree const & st)const;

        void render(Octree const & st, int unsigned depth) const;

        void render(Octree const & st, int unsigned depth, int unsigned current_depth) const;

        void render(OrientedEllipsoid const &) const;

        void render(Sphere const &) const;

        void render(Sphere const & sphere, Vector3D const & orient, Real angle)const;
		
		void setLevelOfDetailOfIcosahedron(int level);

    private:
        std::shared_ptr<Mesh> unitCubeMesh_;
		std::shared_ptr<Mesh> unitSphereMesh_;
		int levelOfDetailOfIcosahedron_;
		std::vector<std::shared_ptr<Mesh>> icosahedrons_;
    };

    ////////////////////////////////////////////////////////////////////////
}

#endif // RENDERER_H