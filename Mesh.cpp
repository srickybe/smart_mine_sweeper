#include "Mesh.h"
#include <iostream>
/*#include "Line.h"
#include "Material.h"
#include "Polygon.h"
#include "Quad.h"
#include "Rand.h"
#include "RGBColor.h"
#include "Triangle.h"
#include "Vector2D.h"
#include "Vector3D.h"*/

namespace ngn {

	Mesh::Mesh(): 
		name_(),
		material_(),
		points_(new std::vector<Vector3D>()),
		texture_coords3_(new std::vector<Vector3D>()),
		texture_coords2_(new std::vector<Vector2D > ()),
		normals_(new std::vector<Vector3D>()),
		lines_(new std::vector<Line>()),
		triangles_(new std::vector<Triangle>()),
		quads_(new std::vector<Quad>()),
		polygons_(new std::vector<Polygon>()) 
	{
    }

	Mesh::Mesh(
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
	) {
        name_ = name;
        material_ = material;
        points_ = points;
        texture_coords3_ = texture_coords3;
        texture_coords2_ = texture_coords2;
        normals_ = normals;
        lines_ = couples;
        triangles_ = triples;
        quads_ = quadruples;
        polygons_ = nuples;
    }

	Mesh::Mesh(Mesh const & rhs) {
        name_ = rhs.name_;
        material_ = rhs.material_;
        points_ = rhs.points_;
        texture_coords3_ = rhs.texture_coords3_;
        texture_coords2_ = rhs.texture_coords2_;
        normals_ = rhs.normals_;
        lines_ = rhs.lines_;
        triangles_ = rhs.triangles_;
        quads_ = rhs.quads_;
        polygons_ = rhs.polygons_;
    }

	Mesh::Mesh(std::string const & name): 
		name_(name),
		points_(new std::vector<Vector3D>()),
		texture_coords3_(new std::vector<Vector3D>()),
		texture_coords2_(new std::vector<Vector2D > ()),
		normals_(new std::vector<Vector3D>()),
		lines_(new std::vector<Line>()),
		triangles_(new std::vector<Triangle>()),
		quads_(new std::vector<Quad>()),
		polygons_(new std::vector<Polygon>()) 
	{
    }

	std::string const & Mesh::getName()const {
        return name_;
    }

	std::shared_ptr<Material> const & Mesh::getMaterial()const {
        return material_;
    }

    
    std::shared_ptr<std::vector<Vector3D>> const & Mesh::getPoints()const {
        return points_;
    }

    
    std::shared_ptr<std::vector<Vector3D>> const & Mesh::getNormals()const {
        return normals_;
    }

    
    std::shared_ptr<std::vector<Vector3D>> const & Mesh::getTextureCoords3()const {
        return texture_coords3_;
    }

    
    std::shared_ptr<std::vector<Vector2D>> const & Mesh::getTextureCoords2()const {
        return texture_coords2_;
    }

    
    std::shared_ptr<std::vector<Line> > const & Mesh::getLines()const {
        return lines_;
    }

    
    std::shared_ptr<std::vector<Triangle> > const & Mesh::getTriangles()const {
        return triangles_;
    }

    
    std::shared_ptr<std::vector<Quad> > const & Mesh::getQuads()const {
        return quads_;
    }

    
    std::shared_ptr<std::vector<Polygon> > const & Mesh::getPolygons()const {
        return polygons_;
    }

    
    void Mesh::setLines(std::shared_ptr<std::vector<Line> > const & couples) {
        lines_ = couples;
    }

    
    void Mesh::setTriangles(std::shared_ptr<std::vector<Triangle> > const & triples) {
        triangles_ = triples;
    }

    
    void Mesh::setQuads(std::shared_ptr<std::vector<Quad> > const & quadruples) {
        quads_ = quadruples;
    }

    
    void Mesh::setPolygons(std::shared_ptr<std::vector<Polygon> > const & nuples) {
        polygons_ = nuples;
    }

    void Mesh::setName(std::string const & name) {
        name_ = name;
    }

    void Mesh::setMaterial(std::shared_ptr< Material > const & material) {
        material_ = material;
    }

    void Mesh::setPoints(std::shared_ptr<std::vector<Vector3D>> const & points) {
        points_ = points;
    }

    void Mesh::setTextureCoordinates(std::shared_ptr<std::vector<Vector3D>> const & text_coords) {
        texture_coords3_ = text_coords;
    }

    void Mesh::setTextureCoordinates(std::shared_ptr<std::vector<Vector2D>> const & text_coords) {
        texture_coords2_ = text_coords;
    }

    void Mesh::setNormals(std::shared_ptr<std::vector<Vector3D>> const & normals) {
        normals_ = normals;
    }

	void Mesh::setColors(std::shared_ptr<std::vector<RGBColor>> const & colors) {
		colors_ = colors;
	}
	
	std::shared_ptr<std::vector<RGBColor>> const Mesh::getColors() const {
		return colors_;
	}
	
     Line const & Mesh::getLine(int i)const {
        assert(i < static_cast<int> (lines_->size()));

        return lines_->operator[](i);
    }

     Triangle const & Mesh::getTriangle(int i)const {
        assert(i < static_cast<int> (triangles_->size()));

        return triangles_->operator[](i);
    }

     Quad const & Mesh::getQuad(int i)const {
        assert(i < static_cast<int> (quads_->size()));

        return quads_->operator[](i);
    }

     Polygon const & Mesh::getPolygon(int i)const {
        assert(i < static_cast<int> (polygons_->size()));

        return polygons_->operator[](i);
    }

     int Mesh::getNumberOfLines()const {
        return lines_->size();
    }

     int Mesh::getNumberOfTriangles()const {
        return triangles_->size();
    }

     int Mesh::getNumberOfQuads()const {
        return quads_->size();
    }

     int Mesh::getNumberOfPolygons()const {
        return polygons_->size();
    }

    void Mesh::addLine(Line const & couple) {
        lines_->push_back(couple);
    }

    void Mesh::addTriangle(Triangle const & triple) {
        triangles_->push_back(triple);
    }

    void Mesh::addQuad(Quad const & quadruple) {
        quads_->push_back(quadruple);
    }

    void Mesh::addPolygon(Polygon const & nuple) {
        polygons_->push_back(nuple);
    }

    
    bool Mesh::hasLines()const {
        return lines_ != 0 && !lines_->empty();
    }

    
    bool Mesh::hasNormals()const {
        return normals_ != 0 && !normals_->empty();
    }

    
    bool Mesh::hasPoints()const {
        return points_ != 0 && !points_->empty();
    }

    
    bool Mesh::hasPolygons()const {
        return polygons_ != 0 && !polygons_->empty();
    }

    
    bool Mesh::hasQuads()const {
        return quads_ != 0 && !quads_->empty();
    }

    
    bool Mesh::hasTriangles()const {
        return triangles_ != 0 && !triangles_->empty();
    }

	bool Mesh::hasColors() const {
		return colors_ != 0 && !colors_->empty();
	}
	
    void Mesh::writeTo(std::ostream & out)const {
        out << "name: " << name_ << "\n";

        if (material_ != 0) {
            out << "material: " << material_->getName() << "\n";
        }

        out << "number of vertices = " << points_->size() << "\n";
        out << "number of couples = " << lines_->size() << "\n";
        out << "number of triples = " << triangles_->size() << "\n";
        out << "number of quadruples = " << quads_->size() << "\n";
        out << "number of nuples = " << polygons_->size() << "\n";

        for (int unsigned i = 0; i < polygons_->size(); ++i) {
            out << "nuple_" << i << " = " << (polygons_->operator[](i)) << "\n";
        }
    }

     Real const * Mesh::pointerToCoordinatesOfFirstPoint() const {
        return (points_->operator[](0)).constantPointerToCoordinates();
    }

     Real const * Mesh::pointerToCoordinatesOfFirstNormal() const {
        return (normals_->operator[](0)).constantPointerToCoordinates();
    }

     unsigned int const * Mesh::pointerToIndicesOfFirstCouple() const {
        return lines_->operator[](0).pointerToIndices();
    }

     unsigned int const * Mesh::pointerToIndicesOfFirstTriple() const {
        return triangles_->operator[](0).pointerToIndices();
    }

     unsigned int const * Mesh::pointerToIndicesOfFirstQuadruple() const {
        return quads_->operator[](0).pointerToIndices();
    }

     unsigned int const * Mesh::pointerToIndicesOfFirstNuple() const {
        return polygons_->operator[](0).pointerToIndices();
    }

     unsigned int const * Mesh::pointerToIndicesOfNupleAt(int i) const {
        return polygons_->operator[](i).pointerToIndices();
    }

	GLfloat const * Mesh::pointerToComponentsOfFirstColor() const {
		return colors_->operator [](0).pointerToComponents();
	}
	
    /*void Mesh::render()const {
        render_aux_();
    }

    void Mesh::render_aux_()const {
        assert(points_ != 0 && !points_->empty());
        {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, Traits< Real >::real_t, 0, pointerToCoordinatesOfFirstPoint());

            if (normals_ != 0) {
                if (!normals_->empty()) {
                    glEnableClientState(GL_NORMAL_ARRAY);
                    glNormalPointer(Traits< Real >::real_t, 0, pointerToCoordinatesOfFirstNormal());
                }
            }

            if (!lines_->empty()) {
                glDrawElements(GL_LINES, 2 * lines_->size(), GL_UNSIGNED_INT, pointerToIndicesOfFirstCouple());
            }

            if (!triangles_->empty()) {
                glDrawElements(GL_TRIANGLES, 3 * triangles_->size(), GL_UNSIGNED_INT, pointerToIndicesOfFirstTriple());
            }

            if (!quads_->empty()) {
                glDrawElements(GL_QUADS, 4 * quads_->size(), GL_UNSIGNED_INT, pointerToIndicesOfFirstQuadruple());
            }

            for (int unsigned i = 0; i < polygons_->size(); ++i) {
                glDrawElements(GL_POLYGON, (polygons_->operator[](i)).getNumberOfVertexIndices(), GL_UNSIGNED_INT, pointerToIndicesOfNupleAt(i));
            }

            glDisableClientState(GL_VERTEX_ARRAY);

            if (normals_ != 0) {
                if (!normals_->empty()) {
                    glDisableClientState(GL_NORMAL_ARRAY);
                }
            }
        }
    }*/

     bool Mesh::replaceDegeneratedPrimitives(Real eps) {
        bool replaced = false;

        if (!triangles_->empty()) {
            for (std::vector<Triangle>::iterator it = triangles_->begin(); it < triangles_->end();) {
                Vector3D d1 = (*points_)[it->getVertexIndex(1)];
                d1.sub((*points_)[it->getVertexIndex(0)]);
                Vector3D d2 = (*points_)[it->getVertexIndex(2)];
                d2.sub((*points_)[it->getVertexIndex(0)]);

                if (d1.isColinear(d2, eps)) {
                    if (!replaced) {
                        replaced = true;
                    }

                    Real d = d1.dot(d2);

                    if (d > (Real) 0) {
                        if (d1.lengthSquared() > d2.lengthSquared()) {
                            lines_->push_back(Line(it->getVertexIndex(0), it->getVertexIndex(1)));
                        } else {
                            lines_->push_back(Line(it->getVertexIndex(0), it->getVertexIndex(2)));
                        }
                    } else {
                        lines_->push_back(Line(it->getVertexIndex(1), it->getVertexIndex(2)));
                    }

                    it = triangles_->erase(it);
                } else {
                    ++it;
                }
            }
        }

        if (!quads_->empty()) {
            std::cout << "mesh " << name_ << " no replacement for quadruples!\n";

            for (int unsigned i = 0; i < quads_->size(); ++i) {
                Quad quad = quads_->operator[](i);
                Vector3D p0 = points_->operator[](quad.getVertexIndex(0));
                Vector3D p1 = points_->operator[](quad.getVertexIndex(1));
                Vector3D p2 = points_->operator[](quad.getVertexIndex(2));

                Vector3D d1 = Vector3D::sub(p1, p0);
                Vector3D d2 = Vector3D::sub(p2, p0);

                if (d1.isColinear(d2, (Real) 1.0e-6)) {
                    std::cout << "quad_" << i << " is not a quad!!!\n";
                }

                Vector3D d3 = Vector3D::sub(p2, p1);
                Vector3D p3 = points_->operator[](quad.getVertexIndex(3));
                Vector3D d4 = Vector3D::sub(p3, p1);

                if (d3.isColinear(d4, (Real) 1.0e-6)) {
                    std::cout << "quad_" << i << " is not a quad!!!\n";
                }
            }
        }

        if (!polygons_->empty()) {
            std::cout << "mesh " << name_ << "no replacement for nuples!\n";
        }

        return replaced;
    }

     std::shared_ptr<Mesh> Mesh::triangulate() const {
        if (triangles_->empty() && quads_->empty()) {
            return std::shared_ptr<Mesh> ();
        }

        std::vector<Triangle> tris;

        if (!quads_->empty()) {
            for (int unsigned i = 0; i < quads_->size(); ++i) {
                Quad quad = quads_->operator[](i);
                int unsigned vertexIndex0 = quad.getVertexIndex(0);
                int unsigned vertexIndex1 = quad.getVertexIndex(1);
                int unsigned vertexIndex2 = quad.getVertexIndex(2);
                int unsigned vertexIndex3 = quad.getVertexIndex(3);
                tris.push_back(Triangle(vertexIndex0, vertexIndex1, vertexIndex2));
                tris.push_back(Triangle(vertexIndex0, vertexIndex2, vertexIndex3));
            }
        }

        if (!polygons_->empty()) {
            for (int unsigned i = 0; i < polygons_->size(); ++i) {
                Polygon nuple = polygons_->operator[](i);

                for (int unsigned j = 0; j < nuple.getNumberOfVertexIndices() - 2; ++j) {
                    tris.push_back(Triangle(nuple.getVertexIndex(0), nuple.getVertexIndex(j + 1), nuple.getVertexIndex(j + 2)));
                }
            }
        }

        std::shared_ptr<Mesh> mesh(new Mesh(*this));
        mesh->quads_ = std::shared_ptr<std::vector<Quad> >(new std::vector<Quad>());
        mesh->polygons_ = std::shared_ptr<std::vector<Polygon> >(new std::vector<Polygon>());

        for (int unsigned i = 0; i < tris.size(); ++i) {
            mesh->triangles_->push_back(tris.operator[](i));
        }

        return mesh;
    }

     bool Mesh::valid()const {
        if (!triangles_->empty()) {
            std::vector<Triangle> const & tris = *triangles_;

            for (int unsigned i = 0; i < tris.size(); ++i) {
                Vector3D const & v0 = (*points_)[tris[i].getVertexIndex(0)];
                Vector3D const & v1 = (*points_)[tris[i].getVertexIndex(1)];
                Vector3D const & v2 = (*points_)[tris[i].getVertexIndex(2)];
                Vector3D dv1 = Vector3D::sub(v1, v0);
                Vector3D dv2 = Vector3D::sub(v2, v0);

                if (dv1.isColinear(dv2, (Real) 1.0e-6)) {
                    return false;
                }
            }
        }

        if (!quads_->empty()) {
            std::vector<Quad> const & quads = *quads_;

            for (int unsigned i = 0; i < quads.size(); ++i) {
                Vector3D const & v0 = (*points_)[quads[i].getVertexIndex(0)];
                Vector3D const & v1 = (*points_)[quads[i].getVertexIndex(1)];
                Vector3D const & v2 = (*points_)[quads[i].getVertexIndex(2)];
                Vector3D dv1 = Vector3D::sub(v1, v0);
                Vector3D dv2 = Vector3D::sub(v2, v0);

                if (dv1.isColinear(dv2, (Real) 1.0e-6)) {
                    return false;
                }

                Vector3D const & v3 = (*points_)[quads[i].getVertexIndex(3)];
                Vector3D dv3 = Vector3D::sub(v2, v1);
                Vector3D dv4 = Vector3D::sub(v3, v1);

                if (dv3.isColinear(dv4, (Real) 1.0e-6)) {
                    return false;
                }
            }
        }

        if (!polygons_->empty()) {
            std::cout << "no validity check for nuples!\n";
        }

        return true;
    }

    
    std::ostream & operator<<(std::ostream & out, Mesh const & mesh) {
        mesh.writeTo(out);

        return out;
    }
}