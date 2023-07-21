#ifndef GRID3D_H
#define GRID3D_H

#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include "Indexes.h"
#include "OrientedBox3D.h"
#include "PairOfSharedPtrPhysicObject3D.h"
#include "Partitions.h"
#include "PredicateOfSharedPtrPhysicObject3D.h"
#include "Result.h"
#include "Vector3D.h"

namespace ngn {
	class PredicateOfPairOfSharedPtrPhysicObject3D;
	class Sphere;

	class Grid3D {	   
	public:	
		typedef Result SearchResult;
 
		Grid3D();
		Grid3D(Vector3D const & orgn, Vector3D const & extnts, Partitions const & prttns);
	   
		bool assignIntersectingCell3DsToPhysicObject3D(SharedPtrPhysicObject3D & entity);
		
		std::pair<bool, std::set<int unsigned>> 
		assignIntersectingCell3DsToArrayOfPhysicObject3Ds(std::vector<SharedPtrPhysicObject3D> & entities);
		
		std::set<SharedPtrCell3D> cellsIntersectingSphereExcept(
			Sphere const & sphere,
			std::set<SharedPtrCell3D> const & excludedCell3Ds
		) const;
		
		void clearAllCell3Ds();
		
		Result closestNeighbor(
			SharedPtrPhysicObject3D const & entity,
			PredicateOfSharedPtrPhysicObject3D const & predicate
		) const;
		
		Result closestNeighborInCell3DsIntersectingPhysicObject3D(
			SharedPtrPhysicObject3D const & entity,
			PredicateOfSharedPtrPhysicObject3D const & predicate
		) const;
		
		Result closerNeighBorInCell3DsIntersectingSphere(
			SharedPtrPhysicObject3D const & entity, 
			PredicateOfSharedPtrPhysicObject3D const & predicate,
			Sphere const & sphere, 
			Result const & bestResult
		) const;
		
		bool containsPosition(Vector3D const & position) const;
		
		bool containsPhysicObject3D(SharedPtrPhysicObject3D const & entity) const;
		
		std::vector<SharedPtrCell3D> emptyCells() const;
		
		std::vector<SharedPtrCell3D> findCell3DsIntersectingPhysicObject3D(SharedPtrPhysicObject3D const & entity) const;
		
		static Grid3D fromOriginExtentsPartitions(
			Vector3D const & worldOrigin,
			Vector3D const & worldExtents,
			Partitions const & partitions
		);
		
		Vector3D const & getOrigin() const;
		
		Vector3D getCell3DHalfExtents() const;
		
		Vector3D const & getExtents() const;
		
		Partitions const & getPartitions() const;
		
		SharedPtrCell3D getCell3D(int i, int j, int k) const;
	   
		Indexes indexesOfCell3DContainingPosition(Vector3D const & position) const;
	   
		bool insertRandomlyPhysicObject3DInFirstEmptyCell3D(SharedPtrPhysicObject3D & object);
		
		bool insertPhysicObject3DInRandomEmptyCell3D(SharedPtrPhysicObject3D & object);
		
		std::set<SharedPtrCell3D> intersectingCell3DsWithSphereExceptCell3Ds(
			Sphere const & sphere,
			std::set<SharedPtrCell3D> const & cells
		) const;
	   
		int numberOfCells() const;
		
		int numberOfPhysicObject3D(PredicateOfSharedPtrPhysicObject3D const & predicate) const;
	   
		int numberOfPartitionsAlongXAxis() const;
	   
		int numberOfPartitionsAlongYAxis() const;
	   
		int numberOfPartitionsAlongZAxis() const;
		
		bool hasObjectInGridCollidingWithObject(
			SharedPtrPhysicObject3D const & object,
			PredicateOfSharedPtrPhysicObject3D const & predicate
		) const;
		
		std::vector<PairOfSharedPtrPhysicObject3D> objectsCollidingAndVerifyingPredicate(
			PredicateOfPairOfSharedPtrPhysicObject3D const & predicate
		) const;
		
		Vector3D randomPosition() const;
		
		void relocateOutOfBoundsPhysicObject3D(SharedPtrPhysicObject3D & object);
		
		bool setPhysicObject3DAtRandomPositionInCell3D(SharedPtrPhysicObject3D & object, SharedPtrCell3D & cell);
		
	private:
		Vector3D origin;
		Vector3D extents;
		OrientedBox3D box;
		Partitions partitions;
		std::vector<std::vector<std::vector<SharedPtrCell3D>>> cells;
		Vector3D farthestPointFromOrigin;
		
		void removePhysicObject3DFromItsCells(SharedPtrPhysicObject3D object);
		OrientedBox3D boxFromOriginAndExtents(Vector3D const & origin, Vector3D const & extents);
	};
}

#endif // GRID3D_H