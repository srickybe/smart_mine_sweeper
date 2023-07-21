#ifndef MODEL_HPP
#define MODEL_HPP

#include <cassert>
#include <iosfwd>
#include <map>
#include <memory>
#include <vector>

#include "Mesh.h"
#include "ModelIterator.h"
#include "ModelConstantIterator.h"

namespace ngn {
    
	class Mesh;
	class Vector2D;
	class Vector3D;
	
    class Model {
    public:

        class ModelBuildNormalsInvalidNumberOfIndicesException {
        public:
            ModelBuildNormalsInvalidNumberOfIndicesException(std::string const & message) {
                message_ = message;
            }
            
        private:
            std::string message_;
        };
        
        typedef Mesh mesh_t;
        typedef std::shared_ptr<mesh_t> mesh_ptr_t;
        typedef ModelConstantIterator const_iterator;
        typedef ModelIterator iterator;

        Model();

        std::map< std::string, std::shared_ptr< Mesh > > const & getMeshes() const;
        std::shared_ptr<std::vector<Vector3D>> const & getVertices() const;
        std::shared_ptr<std::vector<Vector3D>> const & getNormals() const;
        Vector3D const & getVertex(int i)const;
        int numberOfVertices()const;
        int numberOfLines()const;
        int numberOfTriangles()const;
        int numberOfQuads()const;
        int numberOfPolygons()const;
        
        std::shared_ptr<std::vector<Line> > linesFromMeshes() const;
        std::shared_ptr<std::vector<Triangle> > trianglesFromMeshes() const;
        std::shared_ptr<std::vector<Quad> > quadsFromMeshes() const;
        std::shared_ptr<std::vector<Polygon> > polygonsFromMeshes() const;

        void setNormals(std::shared_ptr< std::vector< Vector3D > > const & normals);
        void setPoints(std::shared_ptr< std::vector< Vector3D > > const & points);
        void setTextureCoordinates2(std::shared_ptr< std::vector< Vector2D > > const & tc);
        void setTextureCoordinates3(std::shared_ptr< std::vector< Vector3D > > const & tc);

        void buildNormals();
        Model::const_iterator begin()const;
        Model::iterator begin();
        mesh_ptr_t const & createMesh(std::string const & name);
        Model::const_iterator end()const;
        Model::iterator end();
        Real const * pointerToFirstCoordinateOfFirstVertex() const;
        Vector3D const * pointerToFirstVertex() const;
        void writeTo(std::ostream &)const;
        //void render()const;
        void scale(Real factor);
        std::shared_ptr<Model> triangulate() const;

    private:
        typedef std::map< std::string, std::shared_ptr< Mesh > > container_type;

        std::shared_ptr< std::vector< Vector3D > > points_;
        std::shared_ptr< std::vector< Vector2D > > texture_coordinates_2_;
        std::shared_ptr< std::vector< Vector3D > > texture_coordinates_3_;
        std::shared_ptr< std::vector< Vector3D > > normals_;

        std::map< std::string, std::shared_ptr< Mesh > > meshes_;
    };

    ////////////////////////////////////////////////////////////////////////
}

#endif // MODEL_HPP