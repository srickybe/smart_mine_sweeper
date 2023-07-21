#ifndef PHYSIC_OBJECT_3D_H
#define PHYSIC_OBJECT_3D_H

#include <iosfwd>
#include <memory>
#include <set>
#include <vector>
#include "Indexes.h"
#include "Matrix3D.h"
#include "Mesh.h"
#include "Real.h"
#include "SharedPtrCell3D.h"
#include "SharedPtrPhysicObject3D.h"
#include "Sphere.h"
#include "Vector3D.h"
#include "WeakPtrCell3D.h"

namespace ngn{
	class PhysicObject3D {
	public:
		PhysicObject3D();
		
		bool boundingSpheresCollision(PhysicObject3D const & object) const;
		bool boundingVolumesCollision(PhysicObject3D const & object) const;
		bool collidesWithObjectInIntersectingCells() const;
		Real distanceBetweenSurfaceOfBoundingSpheres(PhysicObject3D const & rhs) const;
		std::vector<WeakPtrCell3D> const & getCell3Ds() const;
		std::vector<Indexes> getCell3DsIndexes() const;
		int getID() const;
		std::set<SharedPtrPhysicObject3D> objectsInCells() const;	
		void printCell3DsIndexes(std::ostream & out) const;
		void setIntersectingCell3Ds(std::vector<SharedPtrCell3D> const & clls);
		Real squaredDistanceBetweenCenters(PhysicObject3D const & rhs) const;

		//virtual std::shared_ptr<Intersectable> const & getBoundingVolume() const = 0;
		virtual Sphere const & getBoundingSphere() const = 0;
		virtual SharedPtrIntersectable const & getBoundingVolume() const = 0;
		virtual Vector3D const & getPosition() const = 0;
		//virtual Matrix3D const & getOrientation() const = 0;
		//virtual std::shared_ptr<Mesh> const & getMesh() const = 0;
		virtual bool isMovable() const = 0;
		virtual void print(std::ostream & out) const = 0;
		virtual void setBoundingSphere(Sphere const & sphere) = 0;
		virtual void setMovable(bool movable) = 0;
		virtual void setPosition(Vector3D const & pstn) = 0;
		
	private:
		static int NUMBER_OF_ENTITIES;
		int ID;
		std::vector<WeakPtrCell3D> cells;
	};

	std::ostream & operator<<(std::ostream & out, PhysicObject3D const & entity);
}

#endif // PHYSIC_OBJECT_3D_H