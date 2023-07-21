#include "NotClosestObjectException.h"
#include <iostream>
#include "Cell3D.h"
#include "Math.h"
#include "PhysicObject3D.h"
#include "Real.h"

namespace ngn {
	
	NotClosestObjectException::NotClosestObjectException(
		SharedPtrPhysicObject3D const & object,
		SharedPtrPhysicObject3D const & objectFound,
		SharedPtrPhysicObject3D const & closestObject,
		int generation
	) :
		object_(object),
		objectFound_(objectFound),
		closestObject_(closestObject),
		generation_(generation)
	{
		std::cout << "object->getID() = " << object_->getID() << "\n";
		std::cout << "objectFound->getID() = " << objectFound_->getID() << "\n";
		std::cout << "closestObject->getID() = " << closestObject_->getID() << "\n";
		std::cout << "generation = " << generation_ << "\n";
		std::cout << "squaredDistance(object, objectFound) = ";
		Real dist1 = Math<Real>::sqrt(
			Vector3D::squaredDistanceFrom(
				object_->getPosition(), 
				objectFound_->getPosition()
			)
		);
		std::cout << dist1 << "\n";
		std::cout << "squaredDistance(object, closestObject) = ";
		Real dist2 = Math<Real>::sqrt(
			Vector3D::squaredDistanceFrom(
				object_->getPosition(), 
				closestObject_->getPosition()
			)
		);
		std::cout << dist2 << "\n";
		std::cout << "object's cell3Ds =\n"; 
		object_->printCell3DsIndexes(std::cout);
		std::cout << "\n"; 
		std::cout << "object contained by its cells? ";
		
		for (int unsigned i = 0; i < object_->getCell3Ds().size(); ++i) {
			if (SharedPtrCell3D cell = object_->getCell3Ds().at(i).lock()) {
				std::cout << cell->contains(object_) << "\n";
			}
		}
		
		std::cout << "objectFound's cell3Ds =\n"; 
		objectFound_->printCell3DsIndexes(std::cout);
		std::cout << "\n";
		std::cout << "objectFound contained by its cell? ";

		for (int unsigned i = 0; i < objectFound_->getCell3Ds().size(); ++i) {
			if (SharedPtrCell3D cell = objectFound_->getCell3Ds().at(i).lock()) {
				std::cout << cell->contains(objectFound_) << "\n";
			}
		}
		
		std::cout << "closestObject's cell3Ds =\n";
		closestObject_->printCell3DsIndexes(std::cout);
		std::cout << "\n";
		std::cout << "closestObject contained by its cell? ";

		for (int unsigned i = 0; i < closestObject_->getCell3Ds().size(); ++i) {
			if (SharedPtrCell3D cell = closestObject_->getCell3Ds().at(i).lock()) {
				std::cout << cell->contains(closestObject_) << "\n";
			}
		}
		
		std::cout << "Do closest object's cells intersect the sphere \n";
		std::cout << "formed by object and the object found ?\n"; 
		ngn::Sphere sphere(
			object_->getPosition(), 
			Vector3D::squaredDistanceFrom(
				object_->getPosition(), 
				objectFound_->getPosition()
			)
		);
		
		for (int unsigned i = 0; i < closestObject_->getCell3Ds().size(); ++i) {
			if (SharedPtrCell3D cell = closestObject_->getCell3Ds().at(i).lock()) {
				std::cout << "cell_";
				cell->getIndexes().print(std::cout);
				std::cout << "\t";
				bool intersected = cell->intersectSphere(sphere);
				std::cout << intersected << "\n";
			}
		}
	}

	SharedPtrPhysicObject3D const & NotClosestObjectException::getObject() const {
		return object_;
	}

	SharedPtrPhysicObject3D const & NotClosestObjectException::getObjectFound() const {
		return objectFound_;
	}

	SharedPtrPhysicObject3D const & NotClosestObjectException::getClosestObject() const {
		return closestObject_;
	}

	int NotClosestObjectException::getGeneration() const {
		return generation_;
	}
	
	char const * NotClosestObjectException::what() const throw() {
		return "NotClosestObjectException!!!\n";
	}
}