#include "Model.h"
#include <iostream>
#include "Line.h"
#include "Polygon.h"
#include "Quad.h"
#include "Triangle.h"
#include "Vector2D.h"
#include "Vector3D.h"

namespace ngn {

	Model::Model()
    :   points_(new std::vector< Vector3D >()),
        texture_coordinates_2_(new std::vector< Vector2D >()), 
        texture_coordinates_3_(new std::vector< Vector3D >()), 
        normals_(new std::vector< Vector3D >()),
        meshes_() 
    {
    }

    
    std::map< std::string, std::shared_ptr< Mesh > > const & Model::getMeshes() const {
        return meshes_;
    }
    
    std::shared_ptr<std::vector<Vector3D>> const & Model::getVertices() const {
        return points_;
    }

    std::shared_ptr<std::vector<Vector3D>> const & Model::getNormals() const {
        return normals_;
    }

    Vector3D const & Model::getVertex(int i)const {
        assert(i < static_cast<int> (points_->size()));

        return points_->at(i);
    }

    int Model::numberOfVertices()const {
        return points_->size();
    }

    int Model::numberOfLines()const {
        int n_couples = 0;

        for (Model::const_iterator it = meshes_.begin(); it != meshes_.end(); ++it) {
            n_couples += (**it).getNumberOfLines();
        }

        //std::cout << "this->couples_->size() = " << this->couples_->size() << "\n";
        return n_couples;
    }
    
    int Model::numberOfTriangles()const {
        int n_triples = 0;

        for (Model::const_iterator it = meshes_.begin(); it != meshes_.end(); ++it) {
            n_triples += (**it).getNumberOfTriangles();
        }

        //std::cout << "this->triples_->size() = " << this->triples_->size() << "\n";
        return n_triples;
    }

    int Model::numberOfQuads()const {
        int n_quadruples = 0;

        for (Model::const_iterator it = meshes_.begin(); it != meshes_.end(); ++it) {
            n_quadruples += (**it).getNumberOfQuads();
        }

        //std::cout << "this->quadruples_->size() = " << this->quadruples_->size() << "\n";
        return n_quadruples;
    }

    int Model::numberOfPolygons()const {
        int n_nuples = 0;

        for (Model::const_iterator it = meshes_.begin(); it != meshes_.end(); ++it) {
            n_nuples += (**it).getNumberOfPolygons();
        }

        //std::cout << "this->nuples_->size() = " << this->nuples_->size() << "\n";
        return n_nuples;
    }

    std::shared_ptr<std::vector<Line> > Model::linesFromMeshes() const {
        std::shared_ptr<std::vector<Line> > couples(new std::vector<Line> ());

        for (ModelConstantIterator it = begin(); it != end(); ++it) {
            Mesh & mesh = (**it);

            for (int i = 0; i < mesh.getNumberOfLines(); ++i) {
                couples->push_back(mesh.getLine(i));
            }
        }
        
        return couples;
    }

    std::shared_ptr<std::vector<Triangle>> Model::trianglesFromMeshes() const {
        std::shared_ptr<std::vector<Triangle> > triples(new std::vector<Triangle> ());

        for (ModelConstantIterator it = begin(); it != end(); ++it) {
            Mesh & mesh = (**it);

            for (int i = 0; i < mesh.getNumberOfTriangles(); ++i) {
                triples->push_back(mesh.getTriangle(i));
            }
        }
        
        return triples;
    }

    std::shared_ptr<std::vector<Quad>> Model::quadsFromMeshes() const {
        std::shared_ptr<std::vector<Quad> > quads(new std::vector<Quad> ());

        for (ModelConstantIterator it = begin(); it != end(); ++it) {
            Mesh & mesh = (**it);

            for (int i = 0; i < mesh.getNumberOfQuads(); ++i) {
                quads->push_back(mesh.getQuad(i));
            }
        }
        
        return quads;
    }

    std::shared_ptr<std::vector<Polygon>> Model::polygonsFromMeshes() const {
        std::shared_ptr<std::vector<Polygon> > nuples(new std::vector<Polygon> ());

        for (ModelConstantIterator it = begin(); it != end(); ++it) {
            Mesh & mesh = (**it);

            for (int i = 0; i < mesh.getNumberOfPolygons(); ++i) {
                nuples->push_back(mesh.getPolygon(i));
            }
        }
        
        return nuples;
    }

    void Model::setNormals(std::shared_ptr< std::vector< Vector3D > > const & normals) {
        if (normals_ != 0) {
            if (normals_->empty()) {
                normals_.reset();
            } else {
                normals_ = normals;
            }
        } else {
            normals_ = normals;
        }
    }

    void Model::setPoints(std::shared_ptr< std::vector< Vector3D > > const & points) {
        points_ = points;
    }

    void Model::setTextureCoordinates2(std::shared_ptr< std::vector< Vector2D > > const & tc) {
        texture_coordinates_2_ = tc;
    }

    void Model::setTextureCoordinates3(std::shared_ptr< std::vector< Vector3D > > const & tc) {
        texture_coordinates_3_ = tc;
    }

    
    Model::const_iterator Model::begin()const {
        return Model::const_iterator(meshes_.begin());
    }

    
    typename Model::iterator Model::begin() {
        return Model::iterator(meshes_.begin());
    }

    
    std::shared_ptr< Mesh > const &
    Model::createMesh(std::string const & name) {
        std::pair< typename container_type::iterator, bool > iter = meshes_.insert(typename container_type::value_type(name, std::shared_ptr< Mesh >(new Mesh())));
        iter.first->second->setName(name);

        return iter.first->second;
    }

    
    typename Model::const_iterator Model::end()const {
        return Model::const_iterator(meshes_.end());
    }

    
    typename Model::iterator Model::end() {
        return Model::iterator(meshes_.end());
    }

    
    Real const * Model::pointerToFirstCoordinateOfFirstVertex() const {
        //return &((points_->operator[](0)).getX());
		return points_->operator[](0).constantPointerToCoordinates();
    }

    
    Vector3D const * Model::pointerToFirstVertex() const {
        return &(points_->operator[](0));
    }

    void Model::writeTo(std::ostream & out)const {
        typedef typename container_type::const_iterator const_iterator;

        std::cout << "Model infos:\n";

        for (const_iterator it = meshes_.begin(); it != meshes_.end(); ++it) {
            it->second->writeTo(out);
            out << "\n";
        }

        if (points_ != 0) {
            std::cout << "number of vertices = " << points_->size() << "\n";
        }

        if (normals_ != 0) {
            std::cout << "number of normals = " << normals_->size() << "\n";
        }

        if (texture_coordinates_2_ != 0) {
            std::cout << "number of 2D texture coordinates = ";
            std::cout << texture_coordinates_2_->size() << "\n";
        }

        if (texture_coordinates_3_ != 0) {
            std::cout << "number of 3D texture coordinates = ";
            std::cout << texture_coordinates_3_->size() << "\n";
        }

        std::cout << "###total number of couples = ";
        std::cout << this->numberOfLines() << "\n";
        std::cout << "###total number of triples = ";
        std::cout << this->numberOfTriangles() << "\n";
        std::cout << "###total number of quadruples = ";
        std::cout << this->numberOfQuads() << "\n";
        std::cout << "###total number of nuples = ";
        std::cout << this->numberOfPolygons() << "\n";
    }

    void Model::buildNormals() {
        if (points_ != 0 && !points_->empty()) {
            std::cout << "normals computing!!!\n";
            
            if (normals_ != 0 && !normals_->empty()) {
                std::cout << "normals already defined!\n";

                return;
            }

            normals_ = std::shared_ptr< std::vector< Vector3D > >(new std::vector< Vector3D >());
            normals_->resize(points_->size(), Vector3D::zero());
            int pi[4];

            for (ModelIterator it = begin(); it != end(); ++it) {
                Mesh & mesh = (**it);
                mesh.setNormals(normals_);

                for (int i = 0; i < mesh.getNumberOfTriangles(); ++i) {
                    for (int j = 0; j < 3; ++j) {
                        pi[j] = mesh.getTriangle(i).getVertexIndex(j);
                    }

                    Vector3D vec1 = Vector3D::sub(points_->operator[](pi[1]), points_->operator[](pi[0]));
                    Vector3D vec2 = Vector3D::sub(points_->operator[](pi[2]), points_->operator[](pi[0]));
                    Vector3D normal = vec1.cross(vec2);

                    for (int j = 0; j < 3; ++j) {
                        normals_->operator[](pi[j]).add(normal);
                    }
                }

                for (int i = 0; i < mesh.getNumberOfQuads(); ++i) {
                    for (int j = 0; j < 4; ++j) {
                        pi[j] = mesh.getQuad(i).getVertexIndex(j);
                    }

                    Vector3D vec1 = Vector3D::sub(points_->operator[](pi[1]), points_->operator[](pi[0]));
                    Vector3D vec2 = Vector3D::sub(points_->operator[](pi[2]), points_->operator[](pi[0]));
                    Vector3D normal = vec1.cross(vec2);

                    Vector3D vec3 = Vector3D::sub(points_->operator[](pi[2]), points_->operator[](pi[0]));
                    Vector3D vec4 = Vector3D::sub(points_->operator[](pi[3]), points_->operator[](pi[0]));
                    normal.add(vec3.cross(vec4));

                    for (int j = 0; j < 4; ++j) {
                        normals_->operator[](pi[j]).add(normal);
                    }
                }

                //Assumption made: the polygon( nuple ) is convex
                if (mesh.getNumberOfPolygons()) {
                    int n_indices;
                    int const MAX_NUPLES = 100;
                    std::vector< int > pi(MAX_NUPLES);

                    for (int i = 0; i < mesh.getNumberOfPolygons(); ++i) {
                        n_indices = mesh.getPolygon(i).getNumberOfVertexIndices();

                        if (n_indices >= MAX_NUPLES) {
                            std::string message = " nuple_";
                            message += std::to_string(i);
                            message += " has ";
                            message += std::to_string(n_indices);
                            message += " which are more than the allowed number of vertex indices = ";
                            message += std::to_string(MAX_NUPLES);
                            std::cout << "message = " << message << "\n";
                            throw ModelBuildNormalsInvalidNumberOfIndicesException(message);
                        } else {
                            pi.resize(n_indices);
                        }

                        for (int j = 0; j < n_indices; ++j) {
                            pi[j] = mesh.getPolygon(i).getVertexIndex(j);
                        }

                        Vector3D normal = Vector3D::zero();

                        for (int k = 0; k < n_indices - 2; ++k) {
                            Vector3D v1 = Vector3D::sub(points_->operator[](pi[k + 1]), points_->operator[](pi[0]));
                            Vector3D v2 = Vector3D::sub(points_->operator[](pi[k + 2]), points_->operator[](pi[0]));

                            normal.add(v1.cross(v2));
                        }

                        for (int j = 0; j < n_indices; ++j) {
                            normals_->operator[](pi[j]).add(normal);
                        }
                    }
                }
            }

            for (int i = 0; i < static_cast<int> (normals_->size()); ++i) {
                if (normals_->operator[](i).getX() != (Real) 0.0 || normals_->operator[](i).getY() != (Real) 0.0 || normals_->operator[](i).getZ() != (Real) 0.0) {
                    normals_->operator[](i).norm();
                } else {
                    std::cout << "no normal computed for point " << i << "\n";
                    //std::cout << "(*normals_)[" << i << "] = " << (*normals_)[i] << "\n";
                }
            }
        } else {
            std::cout << "normals already defined!!!\n";
        }
    }

    /*void Model::render()const {
        for (ModelConstantIterator it = begin(); it != end(); ++it) {
            it->render();
        }
    }*/

    void Model::scale(Real factor) {
        for (int unsigned i = 0; i < points_->size(); ++i) {
            points_->operator [](i) = Vector3D::mult(points_->operator [](i), factor);
        }
    }
   
    std::shared_ptr<Model> Model::triangulate() const {
        std::shared_ptr<Model> model(new Model());
        model->points_ = this->points_;
        model->texture_coordinates_2_ = this->texture_coordinates_2_;
        model->texture_coordinates_3_ = this->texture_coordinates_3_;
        model->normals_ = this->normals_;
        
        for (ModelConstantIterator it = this->begin(); it != this->end(); ++it) {
            std::shared_ptr<Mesh> mesh = it->triangulate();
            
            if (mesh != 0) {
                model->meshes_.insert(typename container_type::value_type(mesh->getName(), mesh));
            } else {
                model->meshes_.insert(typename container_type::value_type(it->getName(), *it));
            }
        }
        
        return model;
    }
}