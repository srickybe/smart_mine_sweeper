#include "MeshBuilder.h"
#include "IllegalArgumentException.h"
#include "Line.h"
#include "Math.h"
#include "Matrix3D.h"
#include "Mesh.h"
#include "Quad.h"
#include "Triangle.h"
#include "Utility.h"
#include "Vector3D.h"
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <vector>

namespace ngn {

	MeshBuilder::CompareVector3D::CompareVector3D() {
		
	}
	
	bool MeshBuilder::CompareVector3D::operator()(Vector3D const & a, Vector3D const & b) const {
		for (int i = 0; i < 3; ++i) {
			if (a.get(i) < b.get(i)) {
				return true;
			} else if (a.get(i) > b.get(i)){
				return false;
			}
		}

		return false;
		
		/*Vector3D diff(Vector3D::sub(b, a));
		
		if (diff.length() >= 1.0e-12) {
			for (int i = 0; i < 3; ++i) {
				if (a.get(i) < b.get(i)) {
					return true;
				} else if (a.get(i) > b.get(i)){
					return false;
				}
			}

			return false;
		} else {
			return false;
		}*/
	}
	
	SharedPtrMesh MeshBuilder::boxMesh(Real xLength, Real yLength, Real zLength) {
		if (xLength <= 0 || yLength <= 0 || zLength <= 0) {
			std::string message = "MeshBuilder::boxMesh(Real xLength, ";
			message += "Real yLength, Real zLength)\n";
			throw IllegalArgumentException(message);
		}
		
		SharedPtrMesh result = unitCubeMesh();
		Matrix3D scaling(
			xLength, 0.0, 0.0,
			0.0, yLength, 0.0,
			0.0, 0.0, zLength
		);
		
		std::shared_ptr<std::vector<Vector3D>> points;
		points = result->getPoints();
		
		for (int unsigned i = 0; i < points->size(); ++i) {
			points->operator [](i) = scaling.mult(points->operator [](i));
		}
		
		return result;
	}
		
    SharedPtrMesh MeshBuilder::unitCubeMesh() {
        std::shared_ptr<std::vector<Quad>> quads(new std::vector<Quad> (6));
        std::shared_ptr<std::vector < Line >> lines(new std::vector<Line> (12));
        std::shared_ptr<std::vector<Vector3D>> vertices(new std::vector<Vector3D> (24));
        std::shared_ptr<std::vector<Vector3D>> normals(new std::vector<Vector3D> (24));
        Real a = (Real) 0.5;

        //points in plane z = -a, bottom face
        vertices->operator[](0) = Vector3D(a, a, -a); //P0
        vertices->operator[](1) = Vector3D(a, -a, -a); //P1
        vertices->operator[](2) = Vector3D(-a, -a, -a); //P2
        vertices->operator[](3) = Vector3D(-a, a, -a); //P3

        normals->operator[](0) = Vector3D(0.0, 0.0, -1.0); //N0
        normals->operator[](1) = Vector3D(0.0, 0.0, -1.0); //N1
        normals->operator[](2) = Vector3D(0.0, 0.0, -1.0); //N2
        normals->operator[](3) = Vector3D(0.0, 0.0, -1.0); //N3

        lines->operator[](0) = Line(0, 1);
        lines->operator[](1) = Line(1, 2);
        lines->operator[](2) = Line(2, 3);
        lines->operator[](3) = Line(3, 0);
        quads->operator[](0) = Quad(0, 1, 2, 3);

        //points in plane x = a, front face
        vertices->operator[](4) = Vector3D(a, a, -a); //P4
        vertices->operator[](5) = Vector3D(a, a, a); //P5
        vertices->operator[](6) = Vector3D(a, -a, a); //P6
        vertices->operator[](7) = Vector3D(a, -a, -a); //P7

        normals->operator[](4) = Vector3D(1.0, 0.0, 0.0); //N4
        normals->operator[](5) = Vector3D(1.0, 0.0, 0.0); //N5
        normals->operator[](6) = Vector3D(1.0, 0.0, 0.0); //N6
        normals->operator[](7) = Vector3D(1.0, 0.0, 0.0); //N7

        lines->operator[](4) = Line(4, 5);
        lines->operator[](5) = Line(5, 6);
        lines->operator[](6) = Line(6, 7);
        quads->operator[](1) = Quad(4, 5, 6, 7);

        //point in plane y = a, right face
        vertices->operator[](8) = Vector3D(a, a, -a); //P8
        vertices->operator[](9) = Vector3D(-a, a, -a); //P9
        vertices->operator[](10) = Vector3D(-a, a, a); //P10
        vertices->operator[](11) = Vector3D(a, a, a); //P11

        normals->operator[](8) = Vector3D(0.0, 1.0, 0.0); //N8
        normals->operator[](9) = Vector3D(0.0, 1.0, 0.0); //N9
        normals->operator[](10) = Vector3D(0.0, 1.0, 0.0); //N10
        normals->operator[](11) = Vector3D(0.0, 1.0, 0.0); //N11

        lines->operator[](7) = Line(9, 10);
        lines->operator[](8) = Line(10, 11);
        quads->operator[](2) = Quad(8, 9, 10, 11);

        //points in plane x = -a, back face
        vertices->operator[](12) = Vector3D(-a, a, -a); //P12
        vertices->operator[](13) = Vector3D(-a, -a, -a); //P13
        vertices->operator[](14) = Vector3D(-a, -a, a); //P14
        vertices->operator[](15) = Vector3D(-a, a, a); //P15

        normals->operator[](12) = Vector3D(-1.0, 0.0, 0.0); //N12
        normals->operator[](13) = Vector3D(-1.0, 0.0, 0.0); //N13
        normals->operator[](14) = Vector3D(-1.0, 0.0, 0.0); //N14
        normals->operator[](15) = Vector3D(-1.0, 0.0, 0.0); //N15

        lines->operator[](9) = Line(13, 14);
        lines->operator[](10) = Line(14, 15);
        quads->operator[](3) = Quad(12, 13, 14, 15);

        //points in plane y = -a, left face
        vertices->operator[](16) = Vector3D(a, -a, -a); //P16
        vertices->operator[](17) = Vector3D(a, -a, a); //P17
        vertices->operator[](18) = Vector3D(-a, -a, a); //P18
        vertices->operator[](19) = Vector3D(-a, -a, -a); //P19

        normals->operator[](16) = Vector3D(0.0, -1.0, 0.0); //N16
        normals->operator[](17) = Vector3D(0.0, -1.0, 0.0); //N17
        normals->operator[](18) = Vector3D(0.0, -1.0, 0.0); //N18
        normals->operator[](19) = Vector3D(0.0, -1.0, 0.0); //N19

        lines->operator[](11) = Line(17, 18);
        quads->operator[](4) = Quad(16, 17, 18, 19);

        //points in plane z = a, top face
        vertices->operator[](20) = Vector3D(a, a, a); //P20
        vertices->operator[](21) = Vector3D(-a, a, a); //P21
        vertices->operator[](22) = Vector3D(-a, -a, a); //P22
        vertices->operator[](23) = Vector3D(a, -a, a); //P23

        normals->operator[](20) = Vector3D(0.0, 0.0, 1.0); //N20
        normals->operator[](21) = Vector3D(0.0, 0.0, 1.0); //N21
        normals->operator[](22) = Vector3D(0.0, 0.0, 1.0); //N22
        normals->operator[](23) = Vector3D(0.0, 0.0, 1.0); //N23

        quads->operator[](5) = Quad(20, 21, 22, 23);

        ////////////////////////////////////////////////////////////////////////////////

		SharedPtrMesh mesh(new Mesh());
        mesh->setPoints(vertices);
        mesh->setNormals(normals);
        mesh->setLines(lines);
        mesh->setQuads(quads);

        return mesh;
    }

    SharedPtrMesh MeshBuilder::unitCircleMesh(int numberOfPoints) {
		Real angle = 2.0 * Math<Real>::PI / numberOfPoints;
		std::shared_ptr<std::vector<Vector3D>> points(new std::vector<Vector3D>());
		std::shared_ptr<std::vector<Line>> lines(new std::vector<Line>());
		
		for (int i = 0; i < numberOfPoints; ++i) {
			Vector3D point(Math<Real>::cos(i * angle), Math<Real>::sin(i * angle), (Real)0.0);
			points->push_back(point);
			
			if (i > 0) {
				lines->push_back(Line(i, i - 1));
			}
		}
		
		std::string name = "";
		std::shared_ptr<Material> material;
		std::shared_ptr<std::vector<Vector3D>> texture_coords3;
		std::shared_ptr<std::vector<Vector2D>> texture_coords2;
		std::shared_ptr<std::vector<Vector3D>> normals;
		std::shared_ptr<std::vector<Triangle>> triples;
		std::shared_ptr<std::vector<Quad>> quadruples;
		std::shared_ptr<std::vector<Polygon>> nuples;
		
		SharedPtrMesh mesh(
			new Mesh(
				name, 
				material, 
				points, 
				texture_coords3, 
				texture_coords2, 
				normals, 
				lines, 
				triples, 
				quadruples, 
				nuples
			)
		);
		
		return mesh;
	}
	
	SharedPtrMesh MeshBuilder::unitDiskMesh(int numberOfPoints) {
		Vector3D center(Vector3D::zero());
		std::shared_ptr<std::vector<Vector3D>> points(new std::vector<Vector3D>());
		points->push_back(center);
		std::shared_ptr<std::vector<Triangle>> triangles(new std::vector<Triangle>());
		Real angle = 2.0 * Math<Real>::PI / numberOfPoints;
		
		for (int i = 0; i < numberOfPoints; ++i) {
			Vector3D point(Math<Real>::cos(i * angle), Math<Real>::sin(i * angle), (Real)0.0);
			points->push_back(point);
			
			if (i > 0) {
				int nPoints = points->size();
				triangles->push_back(Triangle(0, nPoints - 2, nPoints - 1));
			}
		}
		
		std::string name = "";
		std::shared_ptr<Material> material;
		std::shared_ptr<std::vector<Vector3D>> texture_coords3;
		std::shared_ptr<std::vector<Vector2D>> texture_coords2;
		std::shared_ptr<std::vector<Vector3D>> normals;
		std::shared_ptr<std::vector<Line>> lines;
		std::shared_ptr<std::vector<Quad>> quads;
		std::shared_ptr<std::vector<Polygon>> polygons;
		
		SharedPtrMesh mesh(
			new Mesh(
				name, 
				material, 
				points, 
				texture_coords3, 
				texture_coords2, 
				normals, 
				lines, 
				triangles, 
				quads, 
				polygons
			)
		);
		
		return mesh;
	}
	
    SharedPtrMesh MeshBuilder::unitSphereMesh(int levelOfDetail) {
		SharedPtrMesh result;
		result = icosahedron(1.0);
		
		for (int i = 0; i < levelOfDetail; ++i) {
			std::pair<std::shared_ptr<std::vector<Triangle>>, std::shared_ptr<std::vector<Vector3D>>> tmp;
			tmp = Utility::divideTrianglesInFour(*(result->getTriangles()), *(result->getPoints()));
			std::shared_ptr<std::vector<Vector3D>> vertices;
			vertices = tmp.second;
			
			for (int unsigned j = result->getPoints()->size(); j < vertices->size(); ++j) {
				vertices->operator[](j).norm();
			}
			
			std::shared_ptr<std::vector<Triangle>> triangles;
			triangles = tmp.first;
			std::shared_ptr<std::vector<Vector3D>> normals(new std::vector<Vector3D>());
			
			for (int unsigned j = 0; j < triangles->size(); ++j) {
				Triangle triple = triangles->operator [](j);
				Vector3D v0 = vertices->operator [](triple.getVertexIndex(0));
				Vector3D v1 = vertices->operator [](triple.getVertexIndex(1));
				Vector3D v2 = vertices->operator [](triple.getVertexIndex(2));

				Vector3D d1 = Vector3D::sub(v1, v0);
				Vector3D d2 = Vector3D::sub(v2, v0);
				Vector3D normal = d2.cross(d1);
				//normal.norm();
				
				if (normal.dot(v0) < 0) {
					normal.negate();
				}
				
				normals->push_back(normal);
			}
			
			result->setTriangles(triangles);
			result->setPoints(vertices);
			result->setNormals(normals);
		}
		
        return result;
    }

    
    void addToLines(std::vector<Vector3D> const & vertices, std::vector<Line> &lines, Line const & line) {
        for (int unsigned i = 0; i < lines.size(); ++i) {
            Line currentLine = lines.operator[](i);

            if (currentLine.getVertexIndex(0) == line.getVertexIndex(0) &&
                    currentLine.getVertexIndex(1) == line.getVertexIndex(1)) {
                return;
            } else {
                if (currentLine.getVertexIndex(0) == line.getVertexIndex(1) &&
                        currentLine.getVertexIndex(1) == line.getVertexIndex(0)) {
                    return;
                }
            }
        }

        lines.push_back(line);
    }

    
    void addToTriangles(
		std::vector<Vector3D> const & vertices, 
		std::vector<Triangle> &triples, 
		Triangle const & triple, 
		std::vector<Vector3D> &normals
	) {
        Vector3D v0 = vertices.operator [](triple.getVertexIndex(0));
        Vector3D v1 = vertices.operator [](triple.getVertexIndex(1));
        Vector3D v2 = vertices.operator [](triple.getVertexIndex(2));

        Vector3D d1 = Vector3D::sub(v1, v0);
        Vector3D d2 = Vector3D::sub(v2, v0);
        Vector3D normal = d2.cross(d1);
        normal.norm();

        if (normal.dot(v0) < 0) {
            normal.negate();
		}
		
		normals.push_back(normal);
		triples.push_back(triple);
    }

    /*https://mathcurve.com/polyedres/icosaedre/icosaedre.shtml
     * Constructions 1) à partir de 3 rectangles d'or (rapport longueur/largeur égal au nombre d'or) 2 à 2 orthogonaux
     */
    
    SharedPtrMesh MeshBuilder::icosahedron() {
		Real radius = 1.0;
        static const Real EPS = 1.0e-6;
        Real den = std::sqrt(1 + std::pow(Math<Real>::GOLDEN_RATIO, 2.0));
        Real b = radius * Math<Real>::GOLDEN_RATIO / den;
        Real a = radius / den;
        Real len = 2 * radius / den;
        std::shared_ptr<std::vector<Vector3D>> points(new std::vector<Vector3D>(12));
        points->operator[](0) = (Vector3D(a, -b, 0));
        points->operator[](1) = (Vector3D(a, b, 0));
        points->operator[](2) = (Vector3D(-a, b, 0));
        points->operator[](3) = (Vector3D(-a, -b, 0));
        points->operator[](4) = (Vector3D(0, a, -b));
        points->operator[](5) = (Vector3D(0, a, b));
        points->operator[](6) = (Vector3D(0, -a, b));
        points->operator[](7) = (Vector3D(0, -a, -b));
        points->operator[](8) = (Vector3D(b, 0, a));
        points->operator[](9) = (Vector3D(b, 0, -a));
        points->operator[](10) = (Vector3D(-b, 0, -a));
        points->operator[](11) = (Vector3D(-b, 0, a));

        //std::cout << "a = " << a << std::endl;
        //std::cout << "b = " << b << std::endl;
        //std::cout << "len = " << len << std::endl;

        for (int unsigned i = 0; i < points->size(); ++i) {
			bool test = Math<Real>::areEqualWithTol(points->operator[](i).length(), radius, EPS);
			
            if (!test) {
                std::cout << "vertices[" << i << "] is not on the sphere with radius = " << radius << "\n";
            }
        }

        std::shared_ptr<std::vector<Triangle>> triangles(new std::vector<Triangle>());

        for (int unsigned i = 0; i < points->size(); ++i) {
            for (int unsigned j = i + 1; j < points->size(); ++j) {
				Vector3D d1 = Vector3D::sub(points->at(i), points->at(j));
				//std::cout << "length(d1) = " << length(d1) << std::endl;
				//std::cout << "std::abs(length(d1) - len) = ";
				//std::cout << std::abs(length(d1) - len) << std::endl;
				
				if (Math<Real>::abs(d1.length() - len) / len <= EPS) {
					for (int unsigned k = j + 1; k < points->size(); ++k) {
                        Vector3D d2 = Vector3D::sub(points->at(j), points->at(k));
                        //std::cout << "length(d2) = " << length(d2) << std::endl;

                        if (Math<Real>::abs(d2.length() - len) / len <= EPS) {
                            Vector3D d3 = Vector3D::sub(points->at(k), points->at(i));
                            //std::cout << "length(d3) = " << length(d3) << std::endl;

                            if (std::abs(d3.length() - len) / len <= EPS) {
                                Triangle triple(i, j, k);
								triangles->push_back(triple);
                                //std::cout << "The triangle = (" << i << ", " << j << ", " << k << ") " << "is equilateral\n";
                            }
                        }
                    }
                }
            }
        }
		
        std::shared_ptr<std::vector<Vector3D>> normals(new std::vector<Vector3D>(points->size()));

		for (int unsigned i = 0; i < points->size(); ++i) {
			normals->operator [](i) = points->operator [](i);
		}

		SharedPtrMesh mesh(new Mesh());
        mesh->setPoints(points);
        mesh->setTriangles(triangles);
        mesh->setNormals(normals);

        return mesh;
    }
	
	SharedPtrMesh MeshBuilder::icosahedron(Real radius) {
		SharedPtrMesh result = icosahedron();
		
		for (int unsigned i = 0; i < result->getPoints()->size(); ++i) {
			result->getPoints()->operator[](i).mult(radius);
		}
		
		return result;
	}
	
	SharedPtrMesh MeshBuilder::icosahedron(Real radius, int unsigned levelOfDetail) {
		SharedPtrMesh result = icosahedron(radius);
		
		for (int unsigned i = 0; i < levelOfDetail; ++i) {
			result = refineIcosahedron(*result, radius);
		}
		
		return result;
	}
	
    SharedPtrMesh MeshBuilder::refineIcosahedron(Mesh const & mesh, Real radius) {
		std::pair<std::shared_ptr<std::vector<Triangle>>, std::shared_ptr<std::vector<Vector3D>>> tmpRes;
		tmpRes = Utility::divideTrianglesInFour(
			*(mesh.getTriangles()),
			*(mesh.getPoints())
		);

		std::shared_ptr<std::vector<Vector3D>> points = tmpRes.second;
		
		for (int unsigned i = mesh.getPoints()->size(); i < points->size(); ++i) {
			points->operator[](i).norm().mult(radius);
		}

		std::shared_ptr<std::vector<Vector3D>> normals(new std::vector<Vector3D>(points->size()));
		int unsigned previousNumberOfPoints = mesh.getPoints()->size();
		
		for (int unsigned i = 0; i < previousNumberOfPoints; ++i) {
			normals->operator[] (i) = mesh.getNormals()->operator[] (i);
		}

		for (int unsigned i = previousNumberOfPoints; i < points->size(); ++i) {
			normals->operator[] (i) = Vector3D::norm(points->operator[] (i));
		}
		
		SharedPtrMesh result(new Mesh());
		result->setPoints(points);
		result->setNormals(normals);
		result->setTriangles(tmpRes.first);
		
		///*std::cout << "points->size() = " << points->size() << "\n";
		//std::set<Vector3D, MeshBuilder::CompareVector3D> vertices;
		
		//for (int unsigned i = 0; i < points->size(); ++i) {
			//vertices.insert(points->operator [](i));
		//}

		//std::cout << "vertices.size() = " << vertices.size() << "\n";*/
		
        return result;
    }
	
	/*void MeshBuilder::rotate(SharedPtrMesh & mesh, Matrix3D const & rotation) {
		
	}
	
	void MeshBuilder::translate(SharedPtrMesh & mesh, Vector3D const & translation) {
		
	}*/
}