#ifndef CELL3D_H
#define CELL3D_H

#include <iosfwd>
#include <memory>
#include <set>
#include "AxisAlignedBox3D.h"
#include "Indexes.h"
#include "PhysicObject3D.h"
#include "PredicateOfPairOfSharedPtrPhysicObject3D.h"
#include "Real.h"
#include "Result.h"

namespace ngn {
	
	class PredicateOfSharedPtrPhysicObject3D;
	class Result;

	class Cell3D {   
	public:
		typedef std::set<SharedPtrPhysicObject3D> SetType;
		typedef SetType::const_iterator ConstIteratorType;
	   
		Cell3D();
		Cell3D(int a, int b, int c, Vector3D const & pstn, Vector3D const & hlfxtnts);
		bool addPhysicObject3D(SharedPtrPhysicObject3D const & entity);
		ConstIteratorType begin() const;
		ConstIteratorType end() const;
		bool contains(SharedPtrPhysicObject3D const & entity) const;
		Real distanceBetweenEntities(PhysicObject3D const & e1, PhysicObject3D const & e2) const;
		Result closestNeighborToPhysicObject3D(SharedPtrPhysicObject3D const & entity);
		Result closestNeighborToPhysicObject3D(
			SharedPtrPhysicObject3D const & entity, 
			PredicateOfSharedPtrPhysicObject3D const & predicate
		);
		bool removePhysicObject3D(SharedPtrPhysicObject3D const & entity);
		AxisAlignedBox3D const & getAxisAlignedBox3D() const;
		void clear();
		Vector3D const & getCenter() const;
		Vector3D const & getHalfExtents() const;
		int getI() const;
		int getJ() const;
		int getK() const;
		Indexes getIndexes() const;
		bool hasAnObjectCollidingWithObject(
			SharedPtrPhysicObject3D const & object,
			PredicateOfSharedPtrPhysicObject3D const & predicate
		) const;
		bool isEmpty() const;
		bool intersectSphere(Sphere const & sphere) const;
		int numberOfPhysicObject3D(PredicateOfSharedPtrPhysicObject3D const & predicate) const;
		std::vector<PairOfSharedPtrPhysicObject3D> 
			objectsCollidingAndVerifyingPredicate(PredicateOfPairOfSharedPtrPhysicObject3D const & predicate) const;
		void print(std::ostream & out) const;
		Vector3D randomPosition() const;
		
		static void test();
		
	private:
		int i, j, k;
		AxisAlignedBox3D box;
		std::set<SharedPtrPhysicObject3D> objects;
	};

	std::ostream & operator<<(std::ostream & out, Cell3D const & cell);
}

#endif // CELL3D_H