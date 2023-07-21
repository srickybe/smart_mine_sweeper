#include "Sphere.h"
#include <cassert>
#include <iostream>
#include "AxisAlignedBox3D.h"
#include "Matrix2D.h"
#include "Matrix3D.h"
#include "Vector2D.h"
#include "UnsupportedOperationException.h"

namespace ngn {
	
	Sphere::Sphere() :
		center(Vector3D::zero()),
		radius((Real)0.0),
		orientation(Matrix3D::identity())
	{
	   
	}
	
	Sphere::Sphere(Vector3D const & cent, Real rad) :
		center(cent),
		radius(rad),
		orientation(Matrix3D::identity())
	{
	   
	}

	Vector3D const & Sphere::getCenter() const {
		return center;
	}

    Sphere Sphere::fromOnePoint(Vector3D const & p0) {
        return Sphere(p0, (Real) 0.0);
    }

    
    Sphere Sphere::fromTwoPoints(Vector3D const & p0, Vector3D const & p1) {
        Vector3D center = Vector3D::div(Vector3D::add(p0, p1), (Real) 2.0);
        Real radius = Vector3D::sub(p0, p1).length() / (Real) 2.0;

        return Sphere(center, radius);
    }

    
    Sphere Sphere::fromThreePoints(
            Vector3D const & p0,
            Vector3D const & p1,
            Vector3D const & p2) {
        // Compute the circle (in 3D) containing p0, p1, and p2.  The Center in
        // barycentric coordinates is K = u0*p0+u1*p1+u2*p2 where u0+u1+u2=1.
        // The Center is equidistant from the three points, so |K-p0| = |K-p1| =
        // |K-p2| = R where R is the radius of the circle.
        //
        // From these conditions,
        //   K-p0 = u0*A + u1*B - A
        //   K-p1 = u0*A + u1*B - B
        //   K-p2 = u0*A + u1*B
        // where A = p0-p2 and B = p1-p2, which leads to
        //   r^2 = |u0*A+u1*B|^2 - 2*Dot(A,u0*A+u1*B) + |A|^2
        //   r^2 = |u0*A+u1*B|^2 - 2*Dot(B,u0*A+u1*B) + |B|^2
        //   r^2 = |u0*A+u1*B|^2
        // Subtracting the last equation from the first two and writing
        // the equations as a linear system,
        //
        // +-                 -++   -+       +-        -+
        // | Dot(A,A) Dot(A,B) || u0 | = 0.5 | Dot(A,A) |
        // | Dot(B,A) Dot(B,B) || u1 |       | Dot(B,B) |
        // +-                 -++   -+       +-        -+
        //
        // The following code solves this system for u0 and u1, then
        // evaluates the third equation in r^2 to obtain r.
        Vector3D A = Vector3D::sub(p0, p2);
        Vector3D B = Vector3D::sub(p1, p2);
        Real AA = A.dot(A);
        Real AB = A.dot(B);
        Real BA = AB;
        Real BB = B.dot(B);
        Matrix2D m(AA, AB, BA, BB);
        Matrix2D invM;

        Real det = m.det();

        if (det == 0.0) {
            /*std::cout << "####################################\n";
            std::cout << "p0 = " << p0 << "\n";
            std::cout << "p1 = " << p1 << "\n";
            std::cout << "p2 = " << p2 << "\n";
            std::cout << "A = " << A << "\n";
            std::cout << "B = " << B << "\n";
            std::cout << "A.isColinear(B, 1.0e-6) ?\t" << A.isColinear(B, (Real)1.0e-6) << "\n";
            std::cout << "AA = " << AA << "\n";
            std::cout << "AB = " << AB << "\n";
            std::cout << "BB = " << BB << "\n";
            std::cout << "m =\n" << m << "\n";*/

            return Sphere::smallestSphereFromTwoOfThreePoints(p0, p1, p2);
        } else {
            invM = Matrix2D::inv(m);
            Vector2D u = invM.mult(Vector2D::div(Vector2D(AA, BB), (Real) 2.0));
            Real u0 = u.getX();
            Real u1 = u.getY();
            Real u2 = (Real) 1.0 - u0 - u1;
            Vector3D center(Vector3D::mult(p0, u0));
            center.add(Vector3D::mult(p1, u1));
            center.add(Vector3D::mult(p2, u2));
            //Real radius = (Vector3D::add(Vector3D::mult(A, u0), Vector3D::mult(B, u1))).length();
            Real radius = (Vector3D::sub(center, p0)).length();

            return Sphere(center, radius);
        }
    }

    
    Sphere Sphere::fromFourPoints(
            Vector3D const & p0,
            Vector3D const & p1,
            Vector3D const & p2,
            Vector3D const & p3) {
        // Compute the sphere containing p0, p1, p2, and p3.  The Center in
        // barycentric coordinates is K = u0*p0+u1*p1+u2*p2+u3*p3 where
        // u0+u1+u2+u3=1.  The Center is equidistant from the three points, so
        // |K-p0| = |K-p1| = |K-p2| = |K-p3| = R where R is the radius of the
        // sphere.
        //
        // From these conditions,
        //   K-p0 = u0*A + u1*B + u2*C - A
        //   K-p1 = u0*A + u1*B + u2*C - B
        //   K-p2 = u0*A + u1*B + u2*C - C
        //   K-p3 = u0*A + u1*B + u2*C
        // where A = p0-p3, B = p1-p3, and C = p2-p3 which leads to
        //   r^2 = |u0*A+u1*B+u2*C|^2 - 2*Dot(A,u0*A+u1*B+u2*C) + |A|^2
        //   r^2 = |u0*A+u1*B+u2*C|^2 - 2*Dot(B,u0*A+u1*B+u2*C) + |B|^2
        //   r^2 = |u0*A+u1*B+u2*C|^2 - 2*Dot(C,u0*A+u1*B+u2*C) + |C|^2
        //   r^2 = |u0*A+u1*B+u2*C|^2
        // Subtracting the last equation from the first three and writing
        // the equations as a linear system,
        //
        // +-                          -++   -+       +-        -+
        // | Dot(A,A) Dot(A,B) Dot(A,C) || u0 | = 0.5 | Dot(A,A) |
        // | Dot(B,A) Dot(B,B) Dot(B,C) || u1 |       | Dot(B,B) |
        // | Dot(C,A) Dot(C,B) Dot(C,C) || u2 |       | Dot(C,C) |
        // +-                          -++   -+       +-        -+
        //
        // The following code solves this system for u0, u1, and u2, then
        // evaluates the fourth equation in r^2 to obtain r.

        Vector3D A(Vector3D::sub(p0, p3));
        Vector3D B(Vector3D::sub(p1, p3));
        Vector3D C(Vector3D::sub(p2, p3));
        Real AA = A.dot(A);
        Real AB = A.dot(B);
        Real AC = A.dot(C);
        Real BA = AB;
        Real BB = B.dot(B);
        Real BC = B.dot(C);
        Real CA = AC;
        Real CB = BC;
        Real CC = C.dot(C);
        Matrix3D m(AA, AB, AC, BA, BB, BC, CA, CB, CC);

        Real det = m.det();

        if (det == 0.0) {
            /*std::cout << "det == 0\n";
            std::cout << "m =\n" << m << "\n";
            std::cout << "####################################\n";
            std::cout << "p0 = " << p0 << "\n";
            std::cout << "p1 = " << p1 << "\n";
            std::cout << "p2 = " << p2 << "\n";
            std::cout << "p3 = " << p3 << "\n";
            std::cout << "A = " << A << "\n";
            std::cout << "B = " << B << "\n";
            std::cout << "C = " << C << "\n";
            std::cout << "A.isColinear(B, 1.0e-6) ?\t" << A.isColinear(B, (Real)1.0e-6) << "\n";
            std::cout << "A.isColinear(C, 1.0e-6) ?\t" << A.isColinear(C, (Real)1.0e-6) << "\n";
            std::cout << "B.isColinear(C, 1.0e-6) ?\t" << B.isColinear(C, (Real)1.0e-6) << "\n";
            std::cout << "AA = " << AA << "\n";
            std::cout << "AB = " << AB << "\n";
            std::cout << "AC = " << AC << "\n";
            std::cout << "BA = " << BA << "\n";
            std::cout << "BB = " << BB << "\n";
            std::cout << "BC = " << BC << "\n";
            std::cout << "CA = " << CA << "\n";
            std::cout << "CB = " << CB << "\n";
            std::cout << "CC = " << CC << "\n";
            std::cout << "m =\n" << m << "\n";*/

            return smallestSphereFromSomeOfFourPoints(p0, p1, p2, p3);
        } else {
            Matrix3D invM = Matrix3D::inv(m);
            Vector3D u = invM.mult(Vector3D::div(Vector3D(AA, BB, CC), (Real) 2.0));
            Real u0 = u.getX();
            Real u1 = u.getY();
            Real u2 = u.getZ();
            Real u3 = (Real) 1.0 - u0 - u1 - u2;
            Vector3D center(Vector3D::mult(p0, u0));
            center.add(Vector3D::mult(p1, u1));
            center.add(Vector3D::mult(p2, u2));
            center.add(Vector3D::mult(p3, u3));
            Real radius = Vector3D::sub(p0, center).length();
            /*
             * Vector3D tmp(Vector3D::mult(A, u0));
             * tmp.add(Vector3D::mult(B, u1));
             * tmp.add(Vector3D::mult(C, u2));
             * Real radius = tmp.length();
             */

            return Sphere(center, radius);
        }
    }

    Sphere Sphere::smallestSphereFromTwoOfThreePoints(Vector3D const & p0, Vector3D const & p1, Vector3D const & p2) {
        Real minRadius = std::numeric_limits<Real>::max();
        int index = -1;

        Sphere spheres[3];
        Vector3D points[3] = {p0, p1, p2};
        int perm[3][3] = {
            {0, 1,/**/ 2},
            {0, 2,/**/ 1},
            {1, 2,/**/ 0}
        };

        for (int i = 0; i < 3; ++i) {
            spheres[i] = Sphere::fromTwoPoints(points[perm[i][0]], points[perm[i][1]]);

            if (spheres[i].containsWithTol(points[perm[i][2]], (Real)1.0e-6)) {
                if (spheres[i].getRadius() < minRadius) {
                    minRadius = spheres[i].getRadius();
                    index = i;
                }
            }
        }

        if (index != -1){
          return spheres[index];
        } else {
            std::cout << "Sphere::fromThreePoints(...)\n";
            throw UnsupportedOperationException("");
        }
    }

    
    Sphere Sphere::smallestSphereFromSomeOfFourPoints(Vector3D const & p0, Vector3D const & p1, Vector3D const & p2, Vector3D const & p3) {
        Sphere spheres[10];
        Real minRadius = std::numeric_limits<Real>::max();
        int index = -1;

        Vector3D points[4] = {p0, p1, p2, p3};
        int perm[10][4] = {
            {0, 1, 2,/**/ 3},
            {0, 1, 3,/**/ 2},
            {0, 2, 3,/**/ 1},
            {1, 2, 3,/**/ 0},
            {0, 1,/**/ 2, 3},
            {0, 2,/**/ 1, 3},
            {0, 3,/**/ 1, 2},
            {1, 2,/**/ 0, 3},
            {1, 3,/**/ 0, 2},
            {2, 3,/**/ 0, 1}
        };

        Real tol = (Real)1.0e-6;

        for (int i = 0; i < 4; ++i) {
            spheres[i] = Sphere::fromThreePoints(points[perm[i][0]], points[perm[i][1]], points[perm[i][2]]);

            if (spheres[i].containsWithTol(points[perm[i][3]], tol)) {
                if (spheres[i].getRadius() < minRadius) {
                    minRadius = spheres[i].getRadius();
                    index = i;
                }
            }
        }

        for (int i = 4; i < 10; ++i) {
            spheres[i] = Sphere::fromTwoPoints(points[perm[i][0]], points[perm[i][1]]);

            if (spheres[i].containsWithTol(points[perm[i][2]], tol) && spheres[i].containsWithTol(points[perm[i][3]], tol)) {
                if (spheres[i].getRadius() < minRadius) {
                    minRadius = spheres[i].getRadius();
                    index = i;
                }
            }
        }

        if (index != -1) {
            return spheres[index];
        } else {
            std::cout << "Sphere::fromFourPoints(...)\n";

            for (int i = 0; i < 4; ++i) {
                std::cout << "p" << i << " = " << points[i] << "\n";
            }

            std::cout << "Sphere(Vector3D::zero(), std::numeric_limits<Real>::max()) =\n";
            std::cout << Sphere(Vector3D::zero(), std::numeric_limits<Real>::max()) << "\n";

            for (int i = 0; i < 10; ++i) {
                std::cout << "spheres[" << i << "] = \n" << spheres[i] << "\n";
            }

            for (int i = 0; i < 4; ++i) {
                int j = perm[i][3];
                std::cout << "spheres[" << i << "].containsWithTol(p" << j << ", " << tol << ") ?\t";
                std::cout << spheres[i].containsWithTol(points[j], tol) << "\n";
            }

            for (int i = 4; i < 10; ++i) {
                int j = perm[i][2];
                int k = perm[i][3];
                std::cout << "spheres[" << i << "].containsWithTol(p" << j << ", " << tol << " && ";
                std::cout << "spheres[" << i << "].containsWithTol(p" << k << ", " << tol << " ?\t";
                std::cout << (spheres[i].containsWithTol(points[j], tol) && spheres[i].containsWithTol(points[k], tol)) << "\n";
            }

            throw UnsupportedOperationException("");
        }
    }

	Real Sphere::getRadius() const {
		return radius;
	}
    
    bool Sphere::contains(Vector3D const & point) const {
        return Vector3D::sub(point, getCenter()).length() <= getRadius();
    }

    bool Sphere::containsWithTol(Vector3D const & point, Real tol) const {
        assert(tol > (Real)0.0);

        return Vector3D::sub(point, getCenter()).length() <= getRadius() + tol;
    }
	
    std::pair<bool, Real> Sphere::contains2(Vector3D const & point) const {
        Vector3D delta = Vector3D::sub(point, getCenter());
        Real dist = delta.length();

        return std::pair<bool, Real > (dist <= getRadius(), dist);
    }
	
	Real Sphere::distanceBetweenSurfaces(Sphere const & rhs) const {
		Vector3D diff = Vector3D::sub(rhs.getCenter(), getCenter());
		Real res = diff.length() - rhs.getRadius() - getRadius();
		
		return res;
	}

	bool Sphere::equalsWithTol(Sphere const & rhs, Real tol) const {
		return getCenter().equalsWithTol(rhs.getCenter(), tol) 
			&& Math<Real>::areEqualWithTol(getRadius(), rhs.getRadius(), tol);
	}
	
	Vector3D const & Sphere::getPosition() const {
		return getCenter();
	}
	
	void Sphere::setPosition(Vector3D const & position) {
		center = position;
	}
		
	Matrix3D const & Sphere::getOrientation() const {
		return orientation;
	}
	
	void Sphere::setOrientation(Matrix3D const & orient) {
		orientation = orient;
	}
	
	Intersection::Result Sphere::intersectIntersectable(Intersectable const & intersectable) const {
		return intersectable.intersectSphere(*this);
	}
	
	Intersection::Result Sphere::intersectAxisAlignedBox3D(AxisAlignedBox3D const & box) const {
		Intersection::Result result = Intersection::axisAlignedBox3DIntersectSphere(box, *this);
		
		return result;
	}

	Intersection::Result Sphere::intersectLineSegment(LineSegment const & lineSegment) const {
		Intersection::Result result = Intersection::lineSegmentIntersectSphere(lineSegment, *this);
		
		return result;
	}
	
	Intersection::Result Sphere::intersectOrientedBox3D(OrientedBox3D const & box) const {
		Intersection::Result result = Intersection::orientedBox3DIntersectSphere(box, *this);
		
		return result;
	}
	
	Intersection::Result Sphere::intersectPlane(Plane const & plane) const {
		Intersection::Result result = Intersection::planeIntersectSphere(plane, *this);
		
		return result;
	}
	
	Intersection::Result Sphere::intersectSphere(Sphere const & sphere) const {
		Intersection::Result result = Intersection::sphereIntersectSphere(*this, sphere);
		
		return result;
	}

	void Sphere::print(std::ostream & out) const {
		out << "Sphere{position=" << getCenter(); 
		out << ", radius=" << getRadius(); 
		out << "}";
	}
	
	Real Sphere::volume() const {
		return 4.0 * Math<Real>::PI * Math<Real>::pow(getRadius(), 3.0) / 3.0; 
	}
	
	std::ostream & operator<<(std::ostream & out, Sphere const & sphere) {
		sphere.print(out);
	   
		return out;
	}
}