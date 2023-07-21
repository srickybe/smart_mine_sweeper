#include "PhysicObject3D.h"
#include <iostream>
#include "Cell3D.h"

namespace ngn {
	int PhysicObject3D::NUMBER_OF_ENTITIES = 0;

	PhysicObject3D::PhysicObject3D() :
		ID(NUMBER_OF_ENTITIES++),
		cells()
	{
		
	}

	std::vector<Indexes> PhysicObject3D::getCell3DsIndexes() const {
		std::vector<Indexes> res;
		
		for (int unsigned i = 0; i < cells.size(); ++i) {
			if (SharedPtrCell3D cll = cells.operator[](i).lock()) {
				res.push_back(cll->getIndexes());
			}
		}
		
		return res;
	}

	std::vector<WeakPtrCell3D> const & PhysicObject3D::getCell3Ds() const {
		return cells;
	}

	int PhysicObject3D::getID() const {
		return ID;
	}

	bool PhysicObject3D::boundingSpheresCollision(PhysicObject3D const & object) const {
		Intersection::Result result = getBoundingSphere().intersectSphere(object.getBoundingSphere());
		
		return result.isPositive();
	}
	
	bool PhysicObject3D::boundingVolumesCollision(PhysicObject3D const & object) const {
		Intersectable const & boundingVolume1 = *getBoundingVolume();
		Intersectable const & boundingVolume2 = *object.getBoundingVolume();
		Intersection::Result result = boundingVolume1.intersectIntersectable(boundingVolume2);
		
		return result.isPositive();
	}
	
	bool PhysicObject3D::collidesWithObjectInIntersectingCells() const {
		for (int unsigned i = 0; i < cells.size(); ++i) {
			if (SharedPtrCell3D cll = cells.operator [](i).lock()) {
				Cell3D::ConstIteratorType start = cll->begin();
				Cell3D::ConstIteratorType end = cll->end();
				Cell3D::ConstIteratorType it;
				
				for (it = start; it != end; ++it) {
					if (this->boundingSpheresCollision(**it)) {
						return true;
					}
				}
			}
		}
		
		return false;
	}
	
	std::set<SharedPtrPhysicObject3D> PhysicObject3D::objectsInCells() const {
		std::set<SharedPtrPhysicObject3D> result;
		
		for (int unsigned i = 0; i < cells.size(); ++i) {
			if (SharedPtrCell3D cell = cells.operator [](i).lock()) {
				Cell3D::ConstIteratorType begin = cell->begin();
				Cell3D::ConstIteratorType end = cell->end();
				Cell3D::ConstIteratorType it;
				
				for (it = begin; it != end; ++it) {
					PhysicObject3D * otherObject = &**it;
					
					if(otherObject != this) {
						result.insert(*it);
					}
				}
			}
		}
		
		return result;
	}
	
	void PhysicObject3D::printCell3DsIndexes(std::ostream & out) const {
		out << "void PhysicObject3D::printCell3DsIndexes(std::ostream & out) const\n";
		out << "cells.size() = " << cells.size() << "\n";
		
		for (int unsigned i = 0; i < cells.size(); ++i) {
			if (SharedPtrCell3D cll = cells[i].lock()) {
				out << "///cell" << i << "=(";
				out << cll->getI() << ",";
				out << cll->getJ() << ",";
				out << cll->getK() << ")\n";
				out << "///cell =\n";
				cll->print(out);
				out << "\n";
			}
		}
	}

	void PhysicObject3D::setIntersectingCell3Ds(std::vector<SharedPtrCell3D> const & clls) {
		cells.clear();
		
		for (int unsigned i = 0; i < clls.size(); ++i) {
			cells.push_back(clls.operator[](i));
		}
	}

	Real PhysicObject3D::squaredDistanceBetweenCenters(PhysicObject3D const & rhs) const {
		//Vector3D diff(Vector3D::sub(getPosition(), rhs.getPosition()));
		
		//return diff.dot(diff);
		return getPosition().squaredDistanceFrom(rhs.getPosition());
	}

	Real PhysicObject3D::distanceBetweenSurfaceOfBoundingSpheres(PhysicObject3D const & rhs) const {
		return getBoundingSphere().distanceBetweenSurfaces(rhs.getBoundingSphere());
	}


	std::ostream & operator<<(std::ostream & out, PhysicObject3D const & entity)
	{
		out << "PhysicObject3D{ID=" << entity.getID() << ", position=" << entity.getPosition();
		std::cout << ", cells=[";
		
		if (!entity.getCell3Ds().empty()) {
			if (SharedPtrCell3D cell = entity.getCell3Ds().operator[](0).lock()) {
				out << "0: grid(";
				out << cell->getI() << ", ";
				out << cell->getJ() << ", ";
				out << cell->getK() << ")";
			}
		}
		
		for (int unsigned i = 1; i < entity.getCell3Ds().size(); ++i) {
			if (SharedPtrCell3D cell = entity.getCell3Ds().operator[](i).lock()) {
				out << ", " << i << ": grid(";
				out << cell->getI() << ", "; 
				out << cell->getJ() << ", "; 
				out << cell->getK() << ")";
			}	
		}
		
		out << "}";
		
		return out;
	}
}