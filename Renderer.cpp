 #include "Renderer.h"
#include "AxisAngle.h"
#include "Math.h"
#include "Matrix3D.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "Model.h"
#include "Octree.h"
#include "OrientedBox3D.h"
#include "OrientedBox3DTree.h"
#include "OrientedEllipsoid.h"
#include "Polygon.h"
#include "RGBColor.h"
#include "Sphere.h"
#include "SphereTree.h"
#include "Traits.h"
#include "Triangle.h"
#include "Vector3D.h"
#include "MeshBuilder.h"

#include <GL/gl.h>


namespace ngn {
	
	void Renderer::setLevelOfDetailOfIcosahedron(int level) {
		if (level < 0) {
			throw IllegalArgumentException("level < 0"); 
		}
		
		levelOfDetailOfIcosahedron_ = level;
		int startingLevel = (int)icosahedrons_.size() - 1;
 
		if (level > startingLevel) {
			for (int i = startingLevel; i < levelOfDetailOfIcosahedron_; ++i) {
				int lastIndex = icosahedrons_.size() - 1;
				SharedPtrMesh lastMesh = icosahedrons_.operator [](lastIndex);
				SharedPtrMesh mesh = MeshBuilder::refineIcosahedron(*lastMesh, (Real)1.0);
				icosahedrons_.push_back(mesh);
			}
		}
	}
	
    Renderer::Renderer() :
		unitCubeMesh_(MeshBuilder::unitCubeMesh()),
		unitSphereMesh_(MeshBuilder::icosahedron()),
		levelOfDetailOfIcosahedron_(0),
		icosahedrons_(
			{MeshBuilder::unitSphereMesh(Renderer::levelOfDetailOfIcosahedron_)}
		)
	{
    }

    Renderer::~Renderer() {
    }

    
    void Renderer::render(std::vector<Vector3D> const & vertices, std::vector<Triangle> const & triples) const {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, Traits<Real>::real_t, 0, vertices[0].constantPointerToCoordinates());
        glDrawElements(GL_TRIANGLES, 3 * triples.size(), GL_UNSIGNED_INT, triples[0].pointerToIndices());
        glDisableClientState(GL_VERTEX_ARRAY);
    }

	void Renderer::render(Vector3D const & origin, Matrix3D const & basis) const {
        glPushMatrix();
		Traits<Real>::glTranslate(origin.getX(), origin.getY(), origin.getZ());

        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
		Traits<Real>::glVertex3(origin.getX(), origin.getY(), origin.getZ());
		Traits<Real>::glVertex3(basis.get(0, 0), basis.get(1, 0), basis.get(2, 0));

        glColor3f(0.0f, 1.0f, 0.0f);
		Traits<Real>::glVertex3(origin.getX(), origin.getY(), origin.getZ());
		Traits<Real>::glVertex3(basis.get(0, 1), basis.get(1, 1), basis.get(2, 1));

        glColor3f(0.0f, 0.0f, 1.0f);
		Traits<Real>::glVertex3(origin.getX(), origin.getY(), origin.getZ());
		Traits<Real>::glVertex3(basis.get(0, 2), basis.get(1, 2), basis.get(2, 2));

        glEnd();
        glPopMatrix();
    }

     void Renderer::render(Sphere const & sphere)const {
        glPushMatrix();
        Traits<Real>::glTranslate(
			sphere.getCenter().getX(),
			sphere.getCenter().getY(),
			sphere.getCenter().getZ()
		);
		Traits<Real>::glScale(sphere.getRadius(), sphere.getRadius(), sphere.getRadius());
		render(*icosahedrons_.operator [](levelOfDetailOfIcosahedron_));
        glPopMatrix();
    }

    void Renderer::render(Sphere const & sphere, Vector3D const & axis, Real angle) const {
        glPushMatrix();
        Traits<Real>::glTranslate(
			sphere.getCenter().getX(),
			sphere.getCenter().getY(),
			sphere.getCenter().getZ()
		);
        Traits<Real>::glRotate(
			angle,
			axis.getX(),
			axis.getY(),
			axis.getZ()
		);
		Traits<Real>::glScale(sphere.getRadius(), sphere.getRadius(), sphere.getRadius());
		render(*icosahedrons_.operator [](levelOfDetailOfIcosahedron_));
        glPopMatrix();
    }

    
   void Renderer::render(Mesh const & mesh) const {
        if (mesh.hasPoints()) {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, Traits<Real>::real_t, 0, mesh.pointerToCoordinatesOfFirstPoint());

            if (mesh.hasNormals()) {
                glEnableClientState(GL_NORMAL_ARRAY);
                glNormalPointer(Traits<Real>::real_t, 0, mesh.pointerToCoordinatesOfFirstNormal());
            }

			if (mesh.hasColors()) {
				glEnableClientState(GL_COLOR_ARRAY);
				glColorPointer(
					RGBColor::numberOfComponents, 
					RGBColor::componentsType, 
					0, 
					mesh.pointerToComponentsOfFirstColor()
				); 
			}
			
            if (mesh.hasLines()) {
                glDrawElements(GL_LINES, 2 * mesh.getNumberOfLines(), GL_UNSIGNED_INT, mesh.pointerToIndicesOfFirstCouple());
            }

            if (mesh.hasTriangles()) {
                glDrawElements(GL_TRIANGLES, 3 * mesh.getNumberOfTriangles(), GL_UNSIGNED_INT, mesh.pointerToIndicesOfFirstTriple());
            }

            if (mesh.hasQuads()) {
                glDrawElements(GL_QUADS, 4 * mesh.getNumberOfQuads(), GL_UNSIGNED_INT, mesh.pointerToIndicesOfFirstQuadruple());
            }

            if (mesh.hasPolygons()) {
                for (int i = 0; i < mesh.getNumberOfPolygons(); ++i) {
                    glDrawElements(GL_POLYGON, mesh.getPolygon(i).getNumberOfVertexIndices(), GL_UNSIGNED_INT, mesh.pointerToIndicesOfNupleAt(i));
                }
            }

            glDisableClientState(GL_VERTEX_ARRAY);

            if (mesh.hasNormals()) {
                glDisableClientState(GL_NORMAL_ARRAY);
            }
        }
    }

	void Renderer::render(Vector3D const & position, AxisAngle const & axisAngle, Mesh const & mesh) const {
        glPushMatrix();
        Traits<Real>::glTranslate(position.getX(), position.getY(), position.getZ());
		Vector3D axis = axisAngle.getAxis();
        Traits<Real>::glRotate(axisAngle.getAngle(), axis.getX(), axis.getY(), axis.getZ());
		this->render(mesh);
		glPopMatrix();
	}
	
	void Renderer::render(Vector3D const & position, Matrix3D const & orientation, Mesh const & mesh) const {
		AxisAngle axisAngle = orientation.toAxisAngle();
		render(position, axisAngle, mesh);
	}
	
    void Renderer::render(Model const & model) const {
        for (ModelConstantIterator it = model.begin(); it != model.end(); ++it) {
            this->render(**it);
        }
    }

    void Renderer::render(OrientedBox3D const & obb) const {
		AxisAngle aa = obb.getOrientation().toAxisAngle();
		Real angle = aa.getAngle();
		Vector3D axis = aa.getAxis();

        if (axis.lengthSquared() != 0) {

            glPushMatrix();
            Traits<Real>::glTranslate(
				obb.getCenter().getX(),
				obb.getCenter().getY(),
				obb.getCenter().getZ()
			);
            Traits<Real>::glRotate(
				Math<Real>::radToDeg(angle),
				axis.getX(),
				axis.getY(),
				axis.getZ()
			);
            Traits<Real>::glScale(
				2.0 * obb.getHalfExtents().getX(),
				2.0 * obb.getHalfExtents().getY(),
				2.0 * obb.getHalfExtents().getZ()
			);

            this->render(*unitCubeMesh_);

            glPopMatrix();

            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
        }
    }

    void Renderer::render(OrientedBox3DTree const & obt)const {
        if (obt.getBox() != 0) {
            this->render(*obt.getBox());

            if (obt.getLeftChild() != 0) {
                this->render(*obt.getLeftChild());
            }

            if (obt.getRightChild() != 0) {
                this->render(*obt.getRightChild());
            }
        }
    }

    void Renderer::render(OrientedBox3DTree const & obt, int unsigned depth) const {
        this->render(obt, depth, 0);
    }

    void Renderer::render(OrientedBox3DTree const & obt, int unsigned depth, int unsigned current_depth) const {
        if (obt.getBox() != 0) {
            if (current_depth == depth) {
                this->render(*obt.getBox());
            } else {
                if (obt.getLeftChild() != 0) {
                    this->render(*obt.getLeftChild(), depth, current_depth + 1);
                }

                if (obt.getRightChild() != 0) {
                    this->render(*obt.getRightChild(), depth, current_depth + 1);
                }
            }
        }
    }

    void Renderer::render(SphereTree const & sphereTree)const {
        if (sphereTree.getSphere() != 0) {
            this->render(*sphereTree.getSphere());

            if (sphereTree.getLeftChild() != 0) {
                this->render(*sphereTree.getLeftChild());
            }

            if (sphereTree.getRightChild() != 0) {
                this->render(*sphereTree.getRightChild());
            }
        }
    }

    void Renderer::render(SphereTree const & sphereTree, int unsigned depth) const {
        this->render(sphereTree, depth, 0);
    }

    void Renderer::render(SphereTree const & sphereTree, int unsigned depth, int unsigned current_depth) const {
        if (sphereTree.getSphere() != 0) {
            if (current_depth == depth) {
                this->render(*sphereTree.getSphere());
            } else {
                if (sphereTree.getLeftChild() != 0) {
                    this->render(*sphereTree.getLeftChild(), depth, current_depth + 1);
                }

                if (sphereTree.getRightChild() != 0) {
                    this->render(*sphereTree.getRightChild(), depth, current_depth + 1);
                }
            }
        }
    }

    void Renderer::render(Octree const & octree)const {
        if (octree.getSphere() != 0) {
            this->render(*octree.getSphere());

            for (int unsigned i = 0; i < octree.numberOfChildren(); ++i) {
                if (octree.getChild(i) != 0) {
                    this->render(*octree.getChild(i));
                }
            }
        }
    }

    void Renderer::render(Octree const & octree, int unsigned depth) const {
        this->render(octree, depth, 0);
    }

    void Renderer::render(Octree const & octree, int unsigned depth, int unsigned current_depth) const {
        if (octree.getSphere() != 0) {
            if (current_depth == depth) {
                this->render(*octree.getSphere());
            } else {
                for (int unsigned i = 0; i < octree.numberOfChildren(); ++i) {
                    if (octree.getChild(i) != 0) {
                        this->render(*octree.getChild(i), depth, current_depth + 1);
                    }
                }
            }
        }
    }

    void Renderer::render(OrientedEllipsoid const & ellipsoid)
    const {
        AxisAngle aa = ellipsoid.getOrientation().toAxisAngle();
        Real angle = aa.getAngle();
		Vector3D axis = aa.getAxis();

        glPushMatrix();
        Traits<Real>::glTranslate(
			ellipsoid.getCenter().getX(),
			ellipsoid.getCenter().getY(),
			ellipsoid.getCenter().getZ()
		);
        Traits<Real>::glRotate(
			Math<Real>::radToDeg(angle),
			axis.getX(),
			axis.getY(),
			axis.getZ()
		);
        Traits<Real>::glScale(
			ellipsoid.getExtents().getX(),
			ellipsoid.getExtents().getY(),
			ellipsoid.getExtents().getZ()
		);
		render(*icosahedrons_.operator [](levelOfDetailOfIcosahedron_));
        glPopMatrix();
    }
}