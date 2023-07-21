#ifndef MESH_HPP
#define MESH_HPP

#include <GL/gl.h>
#include <iosfwd>
#include <memory>
#include <string>
#include <vector>
#include "Line.h"
#include "Material.h"
#include "Polygon.h"
#include "Quad.h"
#include "Rand.h"
#include "Real.h"
#include "RGBColor.h"
#include "Triangle.h"
#include "Vector2D.h"
#include "Vector3D.h"


namespace ngn {

	/*class Line;
	class Material;
	class Polygon;
	class Quad;
	class RGBColor;
	class Triangle;
	class Vector2D;
	class Vector3D;*/
	
    class Mesh {
    public:
        Mesh();
        Mesh(Mesh const &);
        Mesh(
			std::string const & name,
			std::shared_ptr< Material > const & material,
			std::shared_ptr<std::vector<Vector3D>> const & points,
			std::shared_ptr<std::vector<Vector3D>> const & texture_coords3,
			std::shared_ptr<std::vector<Vector2D>> const & texture_coords2,
			std::shared_ptr<std::vector<Vector3D>> const & normals,
			std::shared_ptr<std::vector<Line>> const & couples,
			std::shared_ptr<std::vector<Triangle>> const & triples,
			std::shared_ptr<std::vector<Quad>> const & quadruples,
			std::shared_ptr<std::vector<Polygon>> const & nuples
		);
        explicit Mesh(std::string const & name);

        std::string const & getName()const;
        std::shared_ptr<Material> const & getMaterial()const;

        std::shared_ptr<std::vector<Vector3D>> const & getTextureCoords3()const;
        std::shared_ptr<std::vector<Vector2D>> const & getTextureCoords2()const;

        std::shared_ptr<std::vector<Vector3D>> const & getPoints()const;
        std::shared_ptr<std::vector<Vector3D>> const & getNormals()const;
        std::shared_ptr<std::vector<Line> > const & getLines()const;
        std::shared_ptr<std::vector<Triangle> > const & getTriangles()const;
        std::shared_ptr<std::vector<Quad> > const & getQuads()const;
        std::shared_ptr<std::vector<Polygon> > const & getPolygons()const;
		
		std::shared_ptr<std::vector<RGBColor>> const getColors() const;

        Line const & getLine(int i)const;
        Triangle const & getTriangle(int i)const;
        Quad const & getQuad(int i)const;
        Polygon const & getPolygon(int i)const;

        int getNumberOfLines()const;
        int getNumberOfTriangles()const;
        int getNumberOfQuads()const;
        int getNumberOfPolygons()const;

        void setName(std::string const & name);
        void setLines(std::shared_ptr<std::vector<Line> > const & couples);
        void setTriangles(std::shared_ptr<std::vector<Triangle> > const & triples);
        void setQuads(std::shared_ptr<std::vector<Quad> > const & quadruples);
        void setPolygons(std::shared_ptr<std::vector<Polygon> > const & nuples);
        void setMaterial(std::shared_ptr< Material > const & material);
        void setPoints(std::shared_ptr<std::vector<Vector3D>> const & points);
        void setTextureCoordinates(std::shared_ptr<std::vector<Vector3D>> const & text_coords);
        void setTextureCoordinates(std::shared_ptr<std::vector<Vector2D>> const & text_coords);
        void setNormals(std::shared_ptr<std::vector<Vector3D>> const & normals);
		void setColors(std::shared_ptr<std::vector<RGBColor>> const & colors);

        void addLine(Line const & couple);
        void addTriangle(Triangle const & triple);
        void addQuad(Quad const & quadruple);
        void addPolygon(Polygon const & nuple);
        bool hasLines()const;
        bool hasNormals()const;
        bool hasPoints()const;
        bool hasPolygons()const;
        bool hasQuads()const;
        bool hasTriangles()const;
		bool hasColors() const;
        Real const * pointerToCoordinatesOfFirstPoint() const;
        Real const * pointerToCoordinatesOfFirstNormal() const;
        unsigned int const * pointerToIndicesOfFirstCouple() const;
        unsigned int const * pointerToIndicesOfFirstTriple() const;
        unsigned int const * pointerToIndicesOfFirstQuadruple() const;
        unsigned int const * pointerToIndicesOfFirstNuple() const;
        unsigned int const * pointerToIndicesOfNupleAt(int i)const;
		GLfloat const * pointerToComponentsOfFirstColor() const;
        void writeTo(std::ostream & out)const;
        //void render()const;
        bool replaceDegeneratedPrimitives(Real eps);
        std::shared_ptr<Mesh> triangulate()const;
        bool valid()const;

    private:
        std::string name_;
        std::shared_ptr< Material > material_;

        std::shared_ptr<std::vector<Vector3D>> points_;
        std::shared_ptr<std::vector<Vector3D>> texture_coords3_;
        std::shared_ptr<std::vector<Vector2D>> texture_coords2_;
        std::shared_ptr<std::vector<Vector3D>> normals_;
		std::shared_ptr<std::vector<RGBColor>> colors_;

        std::shared_ptr<std::vector<Line>> lines_;
        std::shared_ptr<std::vector<Triangle>> triangles_;
        std::shared_ptr<std::vector<Quad>> quads_;
        std::shared_ptr<std::vector<Polygon>> polygons_;

        //void render_aux_()const;
    };

    typedef std::shared_ptr<Mesh> SharedPtrMesh;
    std::ostream & operator<<(std::ostream & out, Mesh const & mesh);

    ////////////////////////////////////////////////////////////////////////
}

#endif // MESH_HPP