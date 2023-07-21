#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <map>
#include <set>
#include <vector>
#include "Cell3D.h"
#include "DefaultSteeringFunction.h"
#include "Grid3D.h"
#include "IsSharedPtrPhysicObject3D.h"
#include "Math.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "Parameters.h"
#include "PhysicObject3D.h"
#include "PredicateOfPairOfSharedPtrPhysicObject3D.h"
#include "Real.h"
#include "Rand.h"
#include "Result.h"
#include "Sigmoid.h"
#include "Simulation.h"
#include "Sphere.h"
#include "Tank.h"
#include "TestIcosahedron.h"
#include "Application.h"
#include "TestWorldMesh.h"
#include "Triangle.h"
#include "UnsupportedOperationException.h"                                               
#include "Utility.h"
#include "Vector2D.h"
#include "Vector3D.h"

using namespace std;
using namespace ngn;

class Entity;
class Predicate;

class Predicate: public PredicateOfPairOfSharedPtrPhysicObject3D {
public:
	Predicate() {}
	
	bool test(PairOfSharedPtrPhysicObject3D const & objectPairPtr) const {
		return objectPairPtr.first != nullptr && objectPairPtr.second != nullptr;
	}
};

class Entity: public PhysicObject3D {
public:
	Entity() :
		position_(Vector3D(0.0, 0.0, 0.0)),
		orientation_(Matrix3D::identity()),
		sphere_(std::make_shared<Sphere>(Vector3D(0.0, 0.0, 0.0), 0.0)),
		movable_(false)
	{
		
	}
		
	Sphere const & getBoundingSphere() const {
		std::shared_ptr<Sphere> const & sphere = std::dynamic_pointer_cast<Sphere>(sphere_);
		
		return *sphere;
	}
	
	SharedPtrIntersectable const & getBoundingVolume() const {
		return sphere_;
	}
	
	void setBoundingSphere(Sphere const & sphr) {
		if (sphr.getCenter().equalsWithTol(getPosition(), 1.0e-6)) {
			sphere_ = std::make_shared<Sphere>(sphr);
		} else {
			cout << "sphere.getCenter() = " << getBoundingSphere().getCenter() << "\n";
			cout << "sphr.getCenter() = " << sphr.getCenter() << "\n";
			throw std::exception();
		}
	}
	
	Vector3D const & getPosition() const {
		return position_;
	}
	
	Matrix3D const & getOrientation() const {
		return orientation_;
	}
	
	std::shared_ptr<Mesh> const & getMesh() const {
		return mesh_;
	}
	
	void setPosition(Vector3D const & position) {
		position_ = position;
	}

	bool isMovable() const {
		return movable_;
	}
	
	void setMovable(bool mvbl) {
		movable_ = mvbl;
	}

	void print(std::ostream & out) const {
		out << "PhysicObject3D{ID=" << getID() << ", position=" << getPosition();
		out << ", cells=[";
		
		if (!getCell3Ds().empty()) {
			if (SharedPtrCell3D cell = getCell3Ds().operator[](0).lock()) {
				out << "0: grid(";
				out << cell->getI() << ", ";
				out << cell->getJ() << ", ";
				out << cell->getK() << ")";
			}
		}
		
		for (int unsigned i = 1; i < getCell3Ds().size(); ++i) {
			if (SharedPtrCell3D cell = getCell3Ds().operator[](i).lock()) {
				out << ", " << i << ": grid(";
				out << cell->getI() << ", "; 
				out << cell->getJ() << ", "; 
				out << cell->getK() << ")";
			}	
		}
		
		out << "}";
	}

private:
	Vector3D position_;
	Matrix3D orientation_;
	ngn::SharedPtrIntersectable sphere_;
	std::shared_ptr<Mesh> mesh_;
	bool movable_;
};

void test() {
    Vector3D origin(200.0, 200.0, 200.0);
    Vector3D extents(1000.0, 1000.0, 1000.0);    
	Partitions partitions(10, 10, 10);
    Grid3D grid(origin, extents, partitions);
	Vector3D position(300.0, 300.0, 300.0);
	SharedPtrPhysicObject3D entity = make_shared<Entity>();
	entity->setPosition(position);
	Sphere sphere(position, 20.0);
	entity->setBoundingSphere(sphere);
	grid.assignIntersectingCell3DsToPhysicObject3D(entity);
	vector<WeakPtrCell3D> cells = entity->getCell3Ds();
	cout << "number of cells of entity = " << cells.size() << "\n";
	
	for (int unsigned i = 0; i < cells.size(); ++i) {
		if (SharedPtrCell3D cell = cells[i].lock()) {
			cout << "cells[" << i << "] contains entity ?" << (cell->contains(entity) ? "true": "false") << "\n";
		}
	}
	
	SharedPtrPhysicObject3D e2 = make_shared<Entity>();
	cout << "e2->getID() = " << e2->getID() << "\n";
	e2->setPosition(Vector3D(400.0, 400.0, 400.0));
	Sphere s2(e2->getPosition(), 30.0);
	e2->setBoundingSphere(s2);
	grid.assignIntersectingCell3DsToPhysicObject3D(e2);
	IsSharedPtrPhysicObject3D predicate;
	Result res = grid.closestNeighbor(e2, predicate);
	cout << "e2 has a closest neighbor? " << (res.isPositive()? "yes": "no") << "\n";
	
	if (res.isPositive()) {
		cout << "closestNeighbor->getId() = " << res.getClosestNeighbor()->getID() << "\n";
	}
}

void test2() {
    Vector3D origin(200.0, 200.0, 200.0);
    Vector3D extents(1000.0, 1000.0, 1000.0);    
	Partitions partitions(10, 10, 10);
    Grid3D grid(origin, extents, partitions);
	Vector3D position(300.0, 300.0, 300.0);
	SharedPtrPhysicObject3D e1 = make_shared<Entity>();
	e1->setPosition(position);
	Sphere s1(position, 20.0);
	e1->setBoundingSphere(s1);
	grid.assignIntersectingCell3DsToPhysicObject3D(e1);
	
	SharedPtrPhysicObject3D e2 = make_shared<Entity>();
	cout << "e2->getID() = " << e2->getID() << "\n";
	e2->setPosition(Vector3D(400.0, 400.0, 400.0));
	Sphere s2(e2->getPosition(), 30.0);
	e2->setBoundingSphere(s2);
	grid.assignIntersectingCell3DsToPhysicObject3D(e2);
	IsSharedPtrPhysicObject3D predicate;
	Result res = grid.closestNeighbor(e2, predicate);
	cout << "e2 has a closest neighbor? " << (res.isPositive()? "yes": "no") << "\n";
	
	if (res.isPositive()) {
		cout << "closestNeighbor->getId() = " << res.getClosestNeighbor()->getID() << "\n";
	}
	
	SharedPtrPhysicObject3D e3 = make_shared<Entity>();
	cout << "e3->getID() = " << e3->getID() << "\n";
	e3->setPosition(Vector3D(350.0, 350.0, 350.0));
	Sphere s3(e3->getPosition(), 30.0);
	e3->setBoundingSphere(s3);
	grid.assignIntersectingCell3DsToPhysicObject3D(e3);
	res = grid.closestNeighbor(e1, predicate);
	
	cout << "e1 has a closest neighbor? " << (res.isPositive()? "yes": "no") << "\n";
	
	if (res.isPositive()) {
		cout << "closestNeighbor->getId() = " << res.getClosestNeighbor()->getID() << "\n";
	}
}

void test3() {
    Vector3D origin(200.0, 200.0, 200.0);
    Vector3D extents(1000.0, 1000.0, 1000.0);    
	Partitions partitions(10, 10, 10);
    Grid3D grid(origin, extents, partitions);
	Vector3D position(300.0, 300.0, 200.0);
	SharedPtrPhysicObject3D e1 = make_shared<Entity>();
	e1->setPosition(position);
	Sphere s1(position, 20.0);
	e1->setBoundingSphere(s1);
	grid.assignIntersectingCell3DsToPhysicObject3D(e1);
	
	SharedPtrPhysicObject3D e2 = make_shared<Entity>();
	cout << "e2->getID() = " << e2->getID() << "\n";
	e2->setPosition(Vector3D(600.0, 600.0, 200.0));
	Sphere s2(e2->getPosition(), 30.0);
	e2->setBoundingSphere(s2);
	grid.assignIntersectingCell3DsToPhysicObject3D(e2);
	IsSharedPtrPhysicObject3D predicate;
	Result res = grid.closestNeighbor(e1, predicate);
	cout << "e1 has a closest neighbor? " << (res.isPositive()? "yes": "no") << "\n";
	
	if (res.isPositive()) {
		cout << "closestNeighbor->getId() = " << res.getClosestNeighbor()->getID() << "\n";
	}
	
	SharedPtrCell3D c1 = grid.getCell3D(4, 2, 0);
	Real radius = 2.0 * grid.getCell3DHalfExtents().length();
	Sphere s3(position, radius);
	cout << "s3 is a sphere with its center equal to position of e1 ";
	cout << "and its radius equal to twice the half extents of the cells of the grid\n";
	cout << "c1 is the cell that has as indexes (4, 2, 0)\n";
	cout << "c1->intersectSphere(s3) ? " << (c1->intersectSphere(s3) ? "true": "false") << "\n";
	
	SharedPtrPhysicObject3D e3 = make_shared<Entity>();
	cout << "e3->getID() = " << e3->getID() << "\n";
	e3->setPosition(Vector3D(650.0, 450.0, 200.0));
	Sphere s4(e3->getPosition(), 25.0);
	e3->setBoundingSphere(s4);
	cout << "s4 is the bounding sphere of e3\n";
	cout << "c1->intersectSphere(s4) ? " << (c1->intersectSphere(s4) ? "true": "false") << "\n";
	cout << "c1 = " << *c1 << "\n";
	
	Real d1 = e2->distanceBetweenSurfaceOfBoundingSpheres(*e1);
	Real d2 = e3->distanceBetweenSurfaceOfBoundingSpheres(*e1);
	cout << "distance between the surfaces of the bounding spheres of e2 and e1 = " << d1 << "\n";
	cout << "distance between the surfaces of the bounding spheres of e3 and e1 = " << d2 << "\n";
	grid.assignIntersectingCell3DsToPhysicObject3D(e3);
	cout << "e3 = " << *e3 << "\n";
	cout << "c1 = " << *c1 << "\n";
	Result res2 = grid.closestNeighbor(e1, predicate);
	cout << "e1 has a closest neighbor? " << (res2.isPositive()? "yes": "no") << "\n";
	
	if (res2.isPositive()) {
		cout << "closestNeighbor->getId() = " << res2.getClosestNeighbor()->getID() << "\n";
	}
}

/* Testing of the algorithm of the search of the closest neighbor
 * The closest neighbor in this test doesn't belong to a cell that intersects the first test sphere 
 * (its radius is equal to the length of the vector of the extents of a cell) that intersects a non empty cell.
 * It belongs to the second test sphere (its radius is equal to the distance between the first candidate 
 * for the closest neighbor and the entity for which we search for the closest neighbor in the grid) 
 * test4() tests the possibility that we need to test again the possibility of the existence of a closer neighbor
 * after having found one with the first test sphere
 */
 
void test4() {
    Vector3D origin(200.0, 200.0, 200.0);
    Vector3D extents(1000.0, 1000.0, 1000.0);    
	Partitions partitions(10, 10, 10);
    Grid3D grid(origin, extents, partitions);
	Vector3D position(300.0, 300.0, 200.0);
	SharedPtrPhysicObject3D e1 = make_shared<Entity>();
	e1->setPosition(position);
	Sphere s1(position, 20.0);
	e1->setBoundingSphere(s1);
	grid.assignIntersectingCell3DsToPhysicObject3D(e1);
	
	SharedPtrPhysicObject3D e2 = make_shared<Entity>();
	//cout << "e2->getID() = " << e2->getID() << "\n";
	e2->setPosition(Vector3D(505.0, 505.0, 200.0));
	Sphere s2(e2->getPosition(), 30.0);
	e2->setBoundingSphere(s2);
	grid.assignIntersectingCell3DsToPhysicObject3D(e2);
	//Result res = grid.closestNeighbor(e1);
	//cout << "e1 has a closest neighbor? " << (res.isPositive()? "yes": "no") << "\n";
	
	//if (res.isPositive()) {
		//cout << "closestNeighbor->getId() = " << res.getClosestNeighbor()->getID() << "\n";
	//}
	
	SharedPtrCell3D c1 = grid.getCell3D(3, 1, 0);
	Real radius = 2.0 * grid.getCell3DHalfExtents().length();
	Sphere s3(position, radius);
	//cout << "s3 is a sphere with its center equal to position of e1 ";
	//cout << "and its radius equal to twice the half extents of the cells of the grid\n";
	//cout << "c1 is the cell that has as indexes (3, 1, 0)\n";
	//cout << "c1->intersectSphere(s3) ? " << (c1->intersectSphere(s3) ? "true": "false") << "\n";
	
	SharedPtrPhysicObject3D e3 = make_shared<Entity>();
	//cout << "e3->getID() = " << e3->getID() << "\n";
	e3->setPosition(Vector3D(550.0,350.0, 200.0));
	Sphere s4(e3->getPosition(), 25.0);
	e3->setBoundingSphere(s4);
	//cout << "s4 is the bounding sphere of e3\n";
	//cout << "c1->intersectSphere(s4) ? " << (c1->intersectSphere(s4) ? "true": "false") << "\n";
	//cout << "c1 = " << *c1 << "\n";
	
	//Real d1 = e2->distanceBetweenSurfaceOfBoundingSpheres(*e1);
	//Real d2 = e3->distanceBetweenSurfaceOfBoundingSpheres(*e1);
	//cout << "distance between the surfaces of the bounding spheres of e2 and e1 = " << d1 << "\n";
	//cout << "distance between the surfaces of the bounding spheres of e3 and e1 = " << d2 << "\n";
	grid.assignIntersectingCell3DsToPhysicObject3D(e3);
	//cout << "e3 = " << *e3 << "\n";
	//cout << "c1 = " << *c1 << "\n";
	IsSharedPtrPhysicObject3D predicate;
	Result res2 = grid.closestNeighbor(e1, predicate);
	//cout << "e1 has a closest neighbor? " << (res2.isPositive()? "yes": "no") << "\n";
	
	//if (res2.isPositive()) {
		//cout << "closestNeighbor->getId() = " << res2.getClosestNeighbor()->getID() << "\n";
	//}

	if (res2.getClosestNeighbor() == nullptr) {
		throw exception();
	}
	
	if (res2.getClosestNeighbor()->getID() != 2) {
		throw exception();
	}
	
	cout << "test4() succeeded!!!\n";
}

void test5() {
    Vector3D origin(200.0, 200.0, 200.0);
    Vector3D extents(1000.0, 1000.0, 1000.0);    
	Partitions partitions(10, 10, 10);
    Grid3D grid(origin, extents, partitions);
	Vector3D position(400.0, 400.0, 400.0);
	SharedPtrPhysicObject3D e1 = make_shared<Entity>();
	e1->setPosition(position);
	Real radius = 101;
	Sphere s1(position, radius);
	e1->setBoundingSphere(s1);
	grid.assignIntersectingCell3DsToPhysicObject3D(e1);
	vector<WeakPtrCell3D> e1Cells = e1->getCell3Ds(); 
	std::cout << "e1 has " << e1Cells.size() << " intersecting cells\n";

	SharedPtrPhysicObject3D e2 = make_shared<Entity>();
	//cout << "e2->getID() = " << e2->getID() << "\n";
	e2->setPosition(Vector3D(500.0, 500.0, 500.0));
	Sphere s2(e2->getPosition(), radius);
	e2->setBoundingSphere(s2);
	grid.assignIntersectingCell3DsToPhysicObject3D(e2);
	vector<WeakPtrCell3D> e2Cells = e2->getCell3Ds();
	std::cout << "e2 has " << e2Cells.size() << " intersecting cells\n";
	set<SharedPtrCell3D> e2SetOfCells;
	
	for (int unsigned i = 0; i < e2Cells.size(); ++i) {
		if (SharedPtrCell3D cell = e2Cells[i].lock()) {
			e2SetOfCells.insert(cell);
		}
	}
	
	set<SharedPtrCell3D> e1SetOfCells;
	
	for (int unsigned i = 0; i < e1Cells.size(); ++i) {
		if (SharedPtrCell3D cell = e1Cells[i].lock()) {
			e1SetOfCells.insert(cell);
		}
	}
	
	set<SharedPtrCell3D> commonCells;
	set<SharedPtrCell3D>::const_iterator i;
	
	for (i = e1SetOfCells.begin(); i != e1SetOfCells.end(); ++i) {
		if (e2SetOfCells.find(*i) != e2SetOfCells.end()) {
			commonCells.insert(*i);
		}
	}
	
	cout << "number of common cells = " << commonCells.size() << "\n";
	
	Predicate predicate;
	vector<PairOfSharedPtrPhysicObject3D> objectsColliding = grid.objectsCollidingAndVerifyingPredicate(predicate);
	cout << "objectsColliding.size() = " << objectsColliding.size() << "\n";
	
	if (objectsColliding.size() > 1) {
		throw std::exception();
	}
	
	cout << "test5 has been successfully passed\n";
}

bool areEquivalentPairsOfSharedPtrPhysicObject3D(
	PairOfSharedPtrPhysicObject3D const & pair1, 
	PairOfSharedPtrPhysicObject3D const & pair2
);

bool areEquivalentPairsOfSharedPtrPhysicObject3D(
	PairOfSharedPtrPhysicObject3D const & pair1, 
	PairOfSharedPtrPhysicObject3D const & pair2
) {
	return (pair1.first == pair2.first && pair1.second == pair2.second) 
		|| (pair1.first == pair2.second && pair1.second == pair2.first);
}
	
void test6() {
	std::cout << "void Grid2D::test6()\n" << "\n";
	Vector3D origin(0.0, 0.0, 0.0);
	Vector3D extents(10, 10, 10);
	Partitions partitions(4, 4, 4);
	Grid3D grid(origin, extents, partitions);
	int nEntities = 1000;
	Real minR = 0.15;
	Real maxR = 0.25;
	std::vector<SharedPtrPhysicObject3D> entities;
	
	for (int i = 0; i < nEntities; ++i) {
		Vector3D p1 = grid.randomPosition();
		Real r1 = util::Rand<Real>::getInstance().next(minR, maxR);
		Sphere c1(p1, r1);
		SharedPtrPhysicObject3D e1 = std::make_shared<Entity>();
		e1->setPosition(p1);
		e1->setBoundingSphere(c1);
		
		while (true) {
			bool test = false;
			
			for (int unsigned j = 0; j < entities.size() && !test; ++j) {
				if (e1->boundingSpheresCollision(*entities[j])) {
					test = true;
				}		
			}
			
			if (test) {
				p1 = grid.randomPosition();
				r1 = util::Rand<Real>::getInstance().next(minR, maxR);
				c1 = Sphere(p1, r1);
				e1->setPosition(p1); 
				e1->setBoundingSphere(c1);
			} else {
				break;
			}
		}
		
		entities.push_back(e1);
		
		Real r2 = util::Rand<Real>::getInstance().next(minR, maxR);
		Real dist = (r1 + r2) * util::Rand<Real>::getInstance().next(0.85, 0.90);
		Real phi = util::Rand<Real>::getInstance().next(0.0, Math<Real>::PI * 2);
		Real theta = util::Rand<Real>::getInstance().next(0.0, Math<Real>::PI);
		Vector3D dp(
			Math<Real>::sin(theta) * Math<Real>::cos(phi) * dist, 
			Math<Real>::sin(theta) * Math<Real>::sin(phi) * dist,
			Math<Real>::cos(theta) * dist
		);
		Vector3D p2 = Vector3D::add(e1->getPosition(), dp);
		Sphere c2(p2, r2);
		SharedPtrPhysicObject3D e2 = std::make_shared<Entity>();
		e2->setPosition(p2);
		e2->setBoundingSphere(c2);
		
		while (true) {
			bool test = false;
			
			if (grid.containsPosition(e2->getPosition())) {
				for (int j = 0; j < (static_cast<int>(entities.size()) - 1) && !test; ++j) {
					if (e2->boundingSpheresCollision(*entities[j])) {
						test = true;
					}		
				}
			} else {
				test = true;
			}
			
			if (test) {
				r2 = util::Rand<Real>::getInstance().next(minR, maxR);
				dist = (r1 + r2) * util::Rand<Real>::getInstance().next(0.85, 0.90);
				phi = util::Rand<Real>::getInstance().next(0.0, Math<Real>::PI * 2);
				theta = util::Rand<Real>::getInstance().next(0.0, Math<Real>::PI);
				dp = Vector3D(
					Math<Real>::sin(theta) * Math<Real>::cos(phi) * dist, 
					Math<Real>::sin(theta) * Math<Real>::sin(phi) * dist,
					Math<Real>::cos(theta) * dist
				);
				p2 = Vector3D::add(e1->getPosition(), dp);
				c2 = Sphere(p2, r2);
				e2 = std::make_shared<Entity>();
				e2->setPosition(p2);
				e2->setBoundingSphere(c2);
			} else {
				break;
			}
		}
		
		entities.push_back(e2);
		
		bool collided = e1->boundingSpheresCollision(*e2);
		
		if (!collided) {
			throw std::exception();
		}
	}
	
	std::vector<PairOfSharedPtrPhysicObject3D> collidingPairs;
	
	for (int unsigned i = 0; i < entities.size(); ++i) {
		for (int unsigned j = i + 1; j < entities.size(); ++j) {
			if (entities[i] == entities[j]) {
				continue;
			}
			
			if (entities[i]->boundingSpheresCollision(*entities[j])) {
				if (entities[i] < entities[j]) {
					collidingPairs.push_back(PairOfSharedPtrPhysicObject3D(entities[i], entities[j]));
				} else {
					collidingPairs.push_back(PairOfSharedPtrPhysicObject3D(entities[j], entities[i]));
				}
			}
		}
	}
	
	std::cout << "# number of colliding pairs = " << collidingPairs.size() << "\n";
	
	for (int unsigned i = 0; i < entities.size(); ++i) {
		if(!grid.assignIntersectingCell3DsToPhysicObject3D(entities[i])) {
			cout << "entity" << i << " not assigned any cell\n";
		}
	}
	
	std::vector<PairOfSharedPtrPhysicObject3D> collidingPairs_2;
	
	class Predicate: public PredicateOfPairOfSharedPtrPhysicObject3D{
	public:
		bool test(PairOfSharedPtrPhysicObject3D const & objectPairPtr) const {
			if (objectPairPtr.first != 0 && objectPairPtr.second != 0) {
				return true;
			}
			
			return false;
		}
	};
	
	Predicate predicate;
	collidingPairs_2 = grid.objectsCollidingAndVerifyingPredicate(predicate);
	std::cout << "# number of colliding pairs = " << collidingPairs_2.size() << "\n";
	
	if (collidingPairs.size() != collidingPairs_2.size()) {
		std::vector<PairOfSharedPtrPhysicObject3D> collidingPairsNotFound;
		std::vector<PairOfSharedPtrPhysicObject3D> pairs1;
		std::vector<PairOfSharedPtrPhysicObject3D> pairs2;
		
		if (collidingPairs.size() > collidingPairs_2.size()) {
			pairs1 = collidingPairs;
			pairs2 = collidingPairs_2;
		} else {
			pairs1 = collidingPairs_2;
			pairs2 = collidingPairs;				
		}
		
		for (int unsigned i = 0; i < pairs1.size(); ++i) {
			PairOfSharedPtrPhysicObject3D pair1 = pairs1.operator [](i);
			bool found = false;
			
			for (int unsigned j = 0; j < pairs2.size(); ++j) {
				PairOfSharedPtrPhysicObject3D pair2 = pairs2.operator [](j);
				
				if (areEquivalentPairsOfSharedPtrPhysicObject3D(pair1, pair2)) {
					found = true;
				}
			}
			
			if (!found) {
				collidingPairsNotFound.push_back(pair1);
			}
		}	
		
		for (int unsigned i = 0; i < collidingPairsNotFound.size(); ++i) {
			PairOfSharedPtrPhysicObject3D pr = collidingPairsNotFound.operator [](i);
			std::cout << "i = " << i << "\n";
			std::cout << "obj1's ID = " << pr.first->getID() << "\n";
			std::cout << "obj1's position = " << pr.first->getPosition() << "\n";
			std::cout << "obj2's ID = " << pr.second->getID() << "\n";
			std::cout << "obj1's position = " << pr.second->getPosition() << "\n";
			vector<Indexes> IJKs1 = pr.first->getCell3DsIndexes();
			cout << "cells of obj1:\n";
			
			for (int unsigned k = 0; k < IJKs1.size(); ++k) {
				cout << IJKs1.size() << " cell" << IJKs1[k].getI() << IJKs1[k].getJ() << IJKs1[k].getK() << "\n";
			}
			
			vector<Indexes> IJKs2 = pr.second->getCell3DsIndexes();
			cout << IJKs2.size() << " cells for obj2:\n";
			
			for (int unsigned k = 0; k < IJKs2.size(); ++k) {
				cout << "cell" << IJKs2[k].getI() << IJKs2[k].getJ() << IJKs2[k].getK() << "\n";
			}
		}
		
		class PairOfSharedPtrPhysicObject3DContains: public PredicateOfPairOfSharedPtrPhysicObject3D {
		public:
			PairOfSharedPtrPhysicObject3DContains(SharedPtrPhysicObject3D const & object): object_(object) {}

			bool test(PairOfSharedPtrPhysicObject3D const & objectPairPtr) const {
				return objectPairPtr.first == object_ || objectPairPtr.second == object_;
			}
			
		private:
			SharedPtrPhysicObject3D object_;
		};
		
		PairOfSharedPtrPhysicObject3DContains containsPhysicObject2D(collidingPairsNotFound.operator [](0).first);
		std::vector<PairOfSharedPtrPhysicObject3D> collidingPairs_3 = grid.objectsCollidingAndVerifyingPredicate(containsPhysicObject2D);
	
		throw std::exception();
	}
}

void test7() {
	std::vector<Vector3D> vertices;
	vertices.push_back(Vector3D::zero());
	vertices.push_back(Vector3D(10.0, 0.0, 0.0));
	Vector3D d0 = Vector3D::sub(vertices[1], vertices[0]);
	Real l = d0.length();
	Real a = Math<Real>::PI / 3.0;
	vertices.push_back(Vector3D(l * Math<Real>::cos(a), l * Math<Real>::sin(a), 0.0));
	Vector3D d1 = Vector3D::sub(vertices[2], vertices[1]);
	Vector3D d2 = Vector3D::sub(vertices[0], vertices[2]);
	
	cout << "d0.length() = " << d0.length() << "\n";
	cout << "d1.length() = " << d1.length() << "\n";
	cout << "d2.length() = " << d2.length() << "\n";
	vector<Triangle> triangles;
	triangles.push_back(Triangle(0, 1, 2));
	cout << "triangles[0] = " << triangles[0] << "\n";
	cout << "area[0] = " << Utility::areaOfTriangle(triangles[0], vertices) << "\n";
	int nLoops = 3;
	vector<pair<shared_ptr<vector<Triangle>>, shared_ptr<vector<Vector3D>>>> results;
	
	for (int k = 0; k < nLoops; ++k) {
		results.push_back(Utility::divideTrianglesInFour(triangles, vertices));
		shared_ptr<std::vector<Triangle>> tris;
		tris = results[k].first;
		shared_ptr<vector<Vector3D>> points;
		points = results[k].second;
		
		cout << "***************points.size() = " << points->size() << "\n";
		cout << "***************tris.size() = " << tris->size() << "\n";
		
		for (int unsigned i = 0; i < tris->size(); ++i) {
			cout << "tris[" << i << "] = " << (*tris)[i] << "\n";
			cout << "area[" << i << "] = "; 
			cout << Utility::areaOfTriangle((*tris)[i], *points) << "\n";
		}
		
		cout << "############################################################\n";
		triangles = *tris;
		vertices = *points;
	}
}

void test8(int argc, char **argv) {
	TestIcosahedron test(argc, argv);
	test.start();
	
	//testIcosahedron(argc, argv);
}

void test9() {
	Graphics graphics;
	std::shared_ptr<std::vector<SharedPtrGraphicObject>> objects;
	objects = std::make_shared<std::vector<SharedPtrGraphicObject>>();
	MeshBuilder meshBuilder;
	objects->push_back(
		std::make_shared<GraphicObject>(
			meshBuilder.icosahedron(20.0, 2),
			Vector3D::zero(),
			Matrix3D::identity()
		)
	);
	
	objects->push_back(
		std::make_shared<GraphicObject>(
			meshBuilder.icosahedron(25.0, 2),
			Vector3D(75.0, 0.0, 0.0),
			Matrix3D::identity()
		)
	);
	
	graphics.setGraphicObjects(objects);
	graphics.start();
	graphics.loop();
}

void testOfCollisionDetectionBetweenSweeperAndMine() {
	std::cout << "testOfCollisionDetectionBetweenSweeperAndMine()\n";
	Vector3D origin(0.0, 0.0, 0.0);
	Vector3D extents(10, 10, 10);
	Partitions partitions(4, 4, 4);
	Grid3D grid(origin, extents, partitions);
	std::vector<SharedPtrPhysicObject3D> entities;
	Vector3D position(9.0, 9.0, 0.0);
	Real radius = 0.25;
	SharedPtrIntersectable sphere = make_shared<Sphere>(position, radius);
	smrtsw::SharedPtrMine mine = make_shared<smrtsw::Mine>(position, sphere);
	entities.push_back(mine);
	int nInputs = 1;
	std::vector<int> nNeuronsByLayer = {10, 2};
	ngn::Range weightRange(-1.0, 1.0);
	ngn::SharedPtrFunction func = std::make_shared<ngn::Sigmoid>(0.5);
	std::vector<std::shared_ptr<std::vector<ngn::SharedPtrFunction>>> functions;
	
	for (int unsigned i = 0; i < nNeuronsByLayer.size(); ++i) {
		functions.push_back(std::make_shared<std::vector<ngn::SharedPtrFunction>>());
		
		for (int j = 0; j < nNeuronsByLayer.operator [](i); ++j) {
			functions.operator [](i)->push_back(func);
		}
	}
	
	ai::NeuralNetwork network 
		= ai::NeuralNetwork::nullWeights(
			nInputs,
			nNeuronsByLayer,
			weightRange,
			functions
		);
	network.setBiasAtRowInLayerWithValue(0, 1, -1.0);
	network.setBiasAtRowInLayerWithValue(1, 1, -1.0);
	int collectedMines = 0;
	smrtsw::SharedPtrBrain brain = std::make_shared<smrtsw::Brain>(network, collectedMines);
	std::cout << "brain =\n" << *brain << "\n";
	Vector3D pos(1.0, 1.0, 0.0);
	Vector2D p1(position.getX(), position.getY());
	Vector2D p2(pos.getX(), pos.getY());
	Real angle = Vector2D::sub(p1, p2).angle();
	std::cout << "angle = " << angle * 180.0 / ngn::Math<Real>::PI << "°\n";
	Real leftTrack = 0;
	Real rightTrack = 0;
	Real maximumTrackSpeed = 0.03;
	Real maximumTurnRate = 0.03;
	Real halfWheelBase = 0.10;
	Real halfWidth = 0.07;
	Real halfHeight = 0.015;
	pos.setZ(halfHeight);
	Vector3D exts(halfWheelBase, halfWidth, halfHeight);
	Matrix3D orientation = Matrix3D::fromAxisAngle(AxisAngle(Vector3D::z_axis(), angle));
	SharedPtrIntersectable boundingVolume = 
		std::make_shared<OrientedBox3D>(
			pos,
			orientation,
			exts
		);
	Real r = Math<Real>::sqrt(halfWheelBase * halfWheelBase + halfWidth * halfWidth + halfHeight * halfHeight);
	ngn::Sphere boundingSphere(pos, r);
	SharedPtrMobile mobile;
	mobile = 
		std::make_shared<smrtsw::Tank>(
			boundingVolume,
			boundingSphere,
			angle,
			leftTrack,
			rightTrack,
			maximumTrackSpeed,
			maximumTurnRate
		);		
	smrtsw::SharedPtrSmartMineSweeper sweeper;
	sweeper = std::make_shared<smrtsw::SmartMineSweeper>(brain, mobile, mine);
	std::cout << "***sweeper's bounding sphere = " << sweeper->getBoundingSphere() << "\n";
	entities.push_back(sweeper);
	bool assigned1 = grid.assignIntersectingCell3DsToPhysicObject3D(entities.operator [](0));
	
	if (!assigned1) {
		throw UnsupportedOperationException("");
	}
	
	bool assigned2 = grid.assignIntersectingCell3DsToPhysicObject3D(entities.operator [](1));
	
	if (!assigned2) {
		throw UnsupportedOperationException("");
	}
	
	Real dt = 1.0 / 30.0;
	Real time = 0.0;
	smrtsw::SharedPtrSteeringFunction steering;
	steering = std::make_shared<smrtsw::DefaultSteeringFunction>();
	
	while (time < 2.5) {
		sweeper->steerToClosestMine(steering);
		sweeper->update(dt);
		bool assigned = grid.assignIntersectingCell3DsToPhysicObject3D(entities.operator [](1));
		
		if (!assigned) {
			std::cout << "sweeper is out of the grid\n";
			grid.relocateOutOfBoundsPhysicObject3D(entities.operator [](1));
		}
		
		std::cout << "sweeper's position = " << sweeper->getPosition() << "\n";
		std::cout << "sweeper's bounding sphere = " << sweeper->getBoundingSphere() << "\n";
		std::vector<ngn::Indexes> cell3DsIndexes;
		cell3DsIndexes = sweeper->getCell3DsIndexes();
		std::cout << "sweeper's cell indexes =\n";
		
		for (int unsigned i = 0; i < cell3DsIndexes.size(); ++i) {
			std::cout << i << ": " << cell3DsIndexes.operator [](i) << "\n";
		}
		
		bool collided = sweeper->boundingSpheresCollision(*mine);
		
		if (collided) {
			std::cout << "###sweeper and mine have collided!!!\n";
			std::cout << "sweeper's bounding sphere = " << sweeper->getBoundingSphere() << "\n";
		}
		
		class Predicate: public ngn::PredicateOfPairOfSharedPtrPhysicObject3D {
		public:
			Predicate() {}
			
			bool test(ngn::PairOfSharedPtrPhysicObject3D const & pair) const {
				return pair.first != nullptr && pair.second != nullptr;
			}
		};
		
		Predicate predicate;
		std::vector<ngn::PairOfSharedPtrPhysicObject3D> objectPairs;
		objectPairs = grid.objectsCollidingAndVerifyingPredicate(predicate);
		
		if (!objectPairs.empty()) {
			std::cout << "///There's a collision inside the grid\n";
		}
		
		time += dt;
	}
}

void testOfCollisionDetectionBetweenSweeperAndMineInSimulation() {
	std::cout << "testOfCollisionDetectionBetweenSweeperAndMineInSimulation()\n";
	Vector3D origin(0.0, 0.0, 0.0);
	Vector3D extents(10, 10, 10);
	Partitions partitions(4, 4, 4);
	Grid3D grid(origin, extents, partitions);
	Vector3D position(9.0, 9.0, 0.0);
	Real radius = 0.25;
	SharedPtrIntersectable sphere = make_shared<Sphere>(position, radius);
	smrtsw::SharedPtrMine mine = make_shared<smrtsw::Mine>(position, sphere);
	int nInputs = 1;
	std::vector<int> nNeuronsByLayer = {10, 2};
	ngn::Range weightRange(-1.0, 1.0);
	ngn::SharedPtrFunction func = std::make_shared<ngn::Sigmoid>(0.5);
	std::vector<std::shared_ptr<std::vector<ngn::SharedPtrFunction>>> functions;
	
	for (int unsigned i = 0; i < nNeuronsByLayer.size(); ++i) {
		functions.push_back(std::make_shared<std::vector<ngn::SharedPtrFunction>>());
		
		for (int j = 0; j < nNeuronsByLayer.operator [](i); ++j) {
			functions.operator [](i)->push_back(func);
		}
	}
	
	ai::NeuralNetwork network 
		= ai::NeuralNetwork::nullWeights(
			nInputs,
			nNeuronsByLayer,
			weightRange,
			functions
		);
	network.setBiasAtRowInLayerWithValue(0, 1, -1.0);
	network.setBiasAtRowInLayerWithValue(1, 1, -1.0);
	int collectedMines = 0;
	smrtsw::SharedPtrBrain brain = std::make_shared<smrtsw::Brain>(network, collectedMines);
	std::cout << "brain =\n" << *brain << "\n";
	Vector3D pos(1.0, 1.0, 0.0);
	Vector2D p1(position.getX(), position.getY());
	Vector2D p2(pos.getX(), pos.getY());
	Real angle = Vector2D::sub(p1, p2).angle();
	std::cout << "angle = " << angle * 180.0 / ngn::Math<Real>::PI << "°\n";
	Real leftTrack = 0;
	Real rightTrack = 0;
	Real maximumTrackSpeed = 1.0;
	Real maximumTurnRate = 1.0;
	Real halfWheelBase = 0.10;
	Real halfWidth = 0.07;
	Real halfHeight = 0.015;
	pos.setZ(halfHeight);
	Vector3D exts(halfWheelBase, halfWidth, halfHeight);
	Matrix3D orientation = Matrix3D::fromAxisAngle(AxisAngle(Vector3D::z_axis(), angle));
	SharedPtrIntersectable boundingVolume = 
		std::make_shared<OrientedBox3D>(
			pos,
			orientation,
			exts
		);
	Real r = Math<Real>::sqrt(halfWheelBase * halfWheelBase + halfWidth * halfWidth + halfHeight * halfHeight);
	ngn::Sphere boundingSphere(pos, r);
	SharedPtrMobile mobile;
	mobile = 
		std::make_shared<smrtsw::Tank>(
			boundingVolume,
			boundingSphere,
			angle,
			leftTrack,
			rightTrack,
			maximumTrackSpeed,
			maximumTurnRate
		);
	smrtsw::SharedPtrSmartMineSweeper sweeper;
	sweeper = std::make_shared<smrtsw::SmartMineSweeper>(brain, mobile, mine);
	std::cout << "sweeper's position = " << sweeper->getPosition() << "\n";
	std::string paramsFilePath = "/home/john/Documents/Programming/SmartSweepersV2/params_example.ini";
	ai::Parameters params(paramsFilePath);
	Settings settings(params.getGASettingsFilePath());
	//smrtsw::World world(grid.getOrigin(), grid.getExtents());
	std::shared_ptr<std::vector<smrtsw::SharedPtrSmartMineSweeper>> sweepers;
	sweepers = std::make_shared<std::vector<smrtsw::SharedPtrSmartMineSweeper>>();
	sweepers->push_back(sweeper);
	std::shared_ptr<std::vector<smrtsw::SharedPtrMine>> mines;
	mines = std::make_shared<std::vector<smrtsw::SharedPtrMine>>();
	mines->push_back(mine);
	
	class MySteeringFunction: public smrtsw::SteeringFunction {
	public:
		MySteeringFunction() {}

		void steer(smrtsw::SmartMineSweeper & sweeper) {
			Vector inputs(1);
			Vector2D v1(
				sweeper.getClosestMineDirection()->getX(), 
				sweeper.getClosestMineDirection()->getY()
			);
			Vector3D heading = sweeper.heading();
			Vector2D v2(heading.getX(), heading.getY());
			Real deltaAngle = (v1.angle() - v2.angle()) / (Math<Real>::PI);
			inputs.setElem(0, deltaAngle);

			Vector outputs = sweeper.processSteeringInputs(inputs);
			sweeper.applySteeringOutputs(outputs);
		}
	};
	
	smrtsw::SharedPtrSteeringFunction steering;
	steering = std::make_shared<smrtsw::DefaultSteeringFunction>();
	smrtsw::Simulation simulation(
		params,
		settings,
		//world,
		grid,
		sweepers,
		mines,
		steering
	);
	
	class MyBrainEvolver: public smrtsw::BrainEvolver {
	public:
		MyBrainEvolver() {}
		
		std::vector<ai::Population>
		evolveBrains(std::vector<ai::Population> const & populations) const {
			return populations;
		}
	};
	
	std::shared_ptr<smrtsw::BrainEvolver> brainEvolver;
	brainEvolver = std::make_shared<MyBrainEvolver>();
	simulation.setBrainEvolver(brainEvolver);
	//simulation.start();
}

int main(int argc, char **argv)
{
	//test9();
    //test8(argc, argv);
	//ngn::Cell3D::test();
	std::string paramsFilePath = "/home/john/Documents/Programming/SmartSweepersV2/params.ini";
	ai::Parameters params(paramsFilePath);
	smrtsw::SharedPtrSteeringFunction steeringFunction;
	steeringFunction = std::make_shared<smrtsw::DefaultSteeringFunction>();
	smrtsw::Application test(params, steeringFunction);
	test.start();
	//smrtsw::Simulation simulation(params, steeringFunction);
	//simulation.start();
	//simulation.test();
	
	//testOfCollisionDetectionBetweenSweeperAndMine();
	//testOfCollisionDetectionBetweenSweeperAndMineInSimulation();
	
	/*ngn::TestWorldMesh testWorldMesh;
	testWorldMesh.start();*/
	
    /*cout << "Grid3D test\n" << "\n";
    Vector3D origin(0.0, 0.0, 0.0);
    Vector3D extents(10, 10, 10);
    //Partitions partitions{2, 2, 2};
    //Grid3D grid(origin, extents, partitions);
    //SharedPtrEntity e1(new PhysicObject3D(Vector3D(7.4, 2.51, 1.24), SharedPtrCell3D()));
    //SharedPtrEntity e2(new PhysicObject3D(Vector3D(1.5, 5.51, 7.24), SharedPtrCell3D()));
    //grid.assignCell3DToPhysicObject3D(e1);
    //cout << "*e1 =\n" << *e1 << "\n";
    //cout << "cell(1, 0, 0) = " << *(grid.getCell3D(1, 0, 0)) << "\n";
    //grid.assignCell3DToPhysicObject3D(e2);
    //cout << "*e2 =\n" << *e2 << "\n";
    //e1->setPosition(Vector3D(7.4, 5.62, 8.35));
    //grid.assignCell3DToPhysicObject3D(e1);
    //cout << "*e1 =\n" << *e1 << "\n";
    //cout << "cell(1, 0, 0) = " << *(grid.getCell3D(1, 0, 0)) << "\n";
    //SharedPtrCell3D c1 = e1->getCell3D().lock();
    //cout << "e1->cell->(i, j, k) = (" << c1->getI() << ", " << c1->getJ() << ", " << c1->getK() << ")\n";
    //cout << "cell(1, 1, 1) = " << *(grid.getCell3D(1, 1, 1)) << "\n";
    Partitions partitions1{4, 4, 4};
    Grid3D grid1(origin, extents, partitions1);
   
    //for (int i = 0; i < partitions1[0]; ++i) {
        //for (int j = 0; j < partitions1[1]; ++j) {
            //for (int k = 0; k < partitions1[2]; ++k) {
                //cout << "(" << i << ", " << j << ", " << k << ")\n";
                //set<SharedPtrCell3D> cells = grid1.cellsAtDistanceFromCell3D(1, *grid1.getCell3D(i, j, k));
                //cout << "cells.size() = " << cells.size() << "\n";
                //cout << "cell's neighbors =\n";
               
                //for (set<SharedPtrCell3D>::iterator it = cells.begin(); it != cells.end(); ++it) {
                   //cout << "(" << (*it)->getI() << ", " << (*it)->getJ() << ", " << (*it)->getK() << ")\n";
                //}
               
                //cout << "##################################\n";
            //}
        //}
    //}
   
    int nTests = 1000;
    int nEntities = 250  ;
    chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();
    chrono::time_point<chrono::system_clock> prev = start;
    chrono::time_point<chrono::system_clock> curr;
   
    for (int t = 0; t < nTests; ++t) {
        if (t % 10000 == 0) {
            cout << "t = " << t << endl;
            curr = chrono::system_clock::now();
            std::chrono::duration<Real> diff = curr - prev;
            prev = curr;
            cout << "duration = " << diff.count() << endl;
        }
       
        grid1.clearAllCell3Ds();
        vector<SharedPtrEntity> entities;
       
        for (int i = 0; i < nEntities; ++i) {
            Real x = ((Real)(rand() % RAND_MAX) / (Real)RAND_MAX) * grid1.getExtents().getX();
            Real y = ((Real)(rand() % RAND_MAX) / (Real)RAND_MAX) * grid1.getExtents().getY();
            Real z = ((Real)(rand() % RAND_MAX) / (Real)RAND_MAX) * grid1.getExtents().getZ();
            Vector3D position(x, y, z);
            position.add(grid1.getOrigin());
            entities.push_back(make_shared<Entity>(position, SharedPtrCell3D()));
        }
       
        for (int i = 0; i < nEntities; ++i) {
            //grid1.assignCell3DToPhysicObject3D(entities[i]);
			grid1.assignIntersectingCell3DsToPhysicObject3D(entities[i]);
        }
       
        if (grid1.numberOfEntities() != nEntities) {
            throw exception();
        }
       
        for (int i = 0; i < nEntities; ++i) {
			Triple<bool, SharedPtrEntity, Real> searchResult = grid1.closestNeighbor_1(entities[i]);
           
            Real minSqrdDist = numeric_limits<Real>::max();
            SharedPtrEntity result;
            vector<Triple<int, int, Real>> distances;
           
            for (int j = 0; j < nEntities; ++j) {
                if (j != i) {
                    Real tmp = entities[i]->distanceBetweenSurfaceOfBoundingSpheres(*entities[j]);//entities[i]->squaredDistanceBetweenCenters(*entities[j]);
                    distances.push_back(makeTriple(entities[i]->getID(), entities[j]->getID(), tmp));
                   
                    if (tmp < minSqrdDist) {
                        minSqrdDist = tmp;
                        result = entities[j];
                    }
                }
            }
           
            if (searchResult.second != result) {
                cout << "#####i = " << i << "\n";
				//cout << "searchResult.second = " << searchResult.second << endl;
				int ID1 = entities[i]->getID();
				int ID2 = searchResult.second->getID();
				
				if (searchResult.second != 0) {
					cout << "entity[ID=" << ID2 << "] = " << *searchResult.second << endl;
					cout << "entity[ID=" << ID2 << "] is not the closest to ";
					cout << "entity[ID=" << ID1 << "]\n";
					cout << "distance between entity_" << ID2 << " and entity_" << ID1 << ": ";
					cout << searchResult.third << "\n";
					cout << "entity[ID=" << ID2 << "] indexes of cells: ";
					searchResult.second->printCell3DsIndexes(cout);
					cout << "\n";
				}
				
                int ID3 = result->getID();
                cout << "entity[ID=" << ID3 << "] is the closest\n";
                //cout << "entity[ID=" << ID3 << "] = " << *result << endl;
				cout << "distance between entity_" << ID3 << " and entity_" << ID1 << ": ";
				cout << entities[i]->distanceBetweenSurfaceOfBoundingSpheres(*result) << "\n";
               
                for (int unsigned k = 0; k < distances.size(); ++k) {
                    cout << "distance(entity_" << distances[k].first << ", entity_" << distances[k].second << ") = ";
                    cout << distances[k].third << "\n";
                }
               
                throw exception();
            }
        }
    }
   
    chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
    std::chrono::duration<Real> res = end - start;
    std::cout << "duration = " << res.count() << endl;*/
   
    return 0;
}