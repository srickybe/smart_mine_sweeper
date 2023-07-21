#include "ComputeTrianglesAreas.h"
#include <cassert>
#include <iostream>
#include <memory>
#include "Triangle.h"
#include "Vector3D.h"


namespace ngn {
	
	ComputeTrianglesAreas::ComputeTrianglesAreas() {
    }

    
    std::shared_ptr<std::vector<Real>>
    ComputeTrianglesAreas::operator()(std::vector<Vector3D> const & vertices, std::vector<Triangle> const & triangles) const {
        assert(!vertices.empty());
        assert(!triangles.empty());

        std::shared_ptr<std::vector < Real >> areas(new std::vector<Real>());

        for (int unsigned i = 0; i < triangles.size(); ++i) {
            Vector3D v1(vertices.at(triangles.at(i).getVertexIndex(0)));
            Vector3D v2(vertices.at(triangles.at(i).getVertexIndex(1)));
            Vector3D v3(vertices.at(triangles.at(i).getVertexIndex(2)));

            Real area = computeTriangleArea(v1, v2, v3);

            if (area == (Real) 0.0) {
                std::cout << "triple n°" << i << "\n";
                std::cout << "Area n°" << i << "\n";
                std::cout << " is equal to zero!!!\n";
                std::cout << "v0 =\n" << v1 << "\n";
                std::cout << "v1 =\n" << v2 << "\n";
                std::cout << "v2 =\n" << v3 << "\n";
            }

            areas->push_back(area);
        }

        return areas;
    }

    
    Real ComputeTrianglesAreas::computeTriangleArea(Vector3D const & v1, Vector3D const & v2, Vector3D const & v3) const {
        Vector3D side1(Vector3D::sub(v2, v1));
        Vector3D side2(Vector3D::sub(v3, v1));
        Vector3D normal(Vector3D::cross(side1, side2));
        Real area = normal.length() / (Real) 2.0;

        return area;
    }
}