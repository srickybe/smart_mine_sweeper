#include "Cell3D.h"
#include <iostream>
#include <limits>
#include "PredicateOfPairOfSharedPtrPhysicObject3D.h"
#include "PredicateOfSharedPtrPhysicObject3D.h"
#include "UnsupportedOperationException.h"

using namespace std;

namespace ngn {
	Cell3D::Cell3D() :
		i(),
		j(),
		k(),
		box(),
		objects()
	{
	   
	}

	Cell3D::Cell3D(int a, int b, int c, Vector3D const & pstn, Vector3D const & hlfxtnts) :
		i(a),
		j(b),
		k(c),
		box(pstn, hlfxtnts)
	{
	   
	}

	bool Cell3D::addPhysicObject3D(SharedPtrPhysicObject3D const & entity) {
		pair<typename SetType::iterator, bool> res = objects.insert(entity);
	   
		return res.second;
	}

	Cell3D::ConstIteratorType Cell3D::begin() const {
		return objects.begin();
	}

	Cell3D::ConstIteratorType Cell3D::end() const {
		return objects.end();
	}

	bool Cell3D::contains(SharedPtrPhysicObject3D const & entity) const {
		return objects.find(entity) != objects.end();
	}

	Real Cell3D::distanceBetweenEntities(PhysicObject3D const & e1, PhysicObject3D const & e2) const {
		return e1.distanceBetweenSurfaceOfBoundingSpheres(e2);
	}

	Result Cell3D::closestNeighborToPhysicObject3D(SharedPtrPhysicObject3D const & entity) {
		Result result(false, SharedPtrPhysicObject3D(), numeric_limits<Real>::max(), set<SharedPtrCell3D>());
		
		if (entity == 0) {
			return result;
		}
	   
		for (ConstIteratorType entitySetIterator = begin(); entitySetIterator != end(); ++entitySetIterator) {
			if ((*entitySetIterator) != entity) {
				Real distance = distanceBetweenEntities(*entity, **entitySetIterator);
		   
				if (distance < result.getDistance()) {
					if (!result.isPositive()) {
						result.setPositive(true);
					}
					
					result.setDistance(distance);
					result.setClosestNeighbor(*entitySetIterator);
				}
			}
		}
	   
		return result;   
	}

	Result Cell3D::closestNeighborToPhysicObject3D(
		SharedPtrPhysicObject3D const & entity,
		PredicateOfSharedPtrPhysicObject3D const & predicate
	) 
	{
		Result result(false, SharedPtrPhysicObject3D(), numeric_limits<Real>::max(), set<SharedPtrCell3D>());
		
		if (entity == 0) {
			return result;
		}
	   
		for (ConstIteratorType entitySetIterator = begin(); entitySetIterator != end(); ++entitySetIterator) {
			if ((*entitySetIterator) != entity) {
				if (predicate.test((*entitySetIterator))) {
					Real distance = distanceBetweenEntities(*entity, **entitySetIterator);
			   
					if (distance < result.getDistance()) {
						if (!result.isPositive()) {
							result.setPositive(true);
						}
						
						result.setDistance(distance);
						result.setClosestNeighbor(*entitySetIterator);
					}
				}
			}
		}
	   
		return result;   
	}
	
	bool Cell3D::removePhysicObject3D(SharedPtrPhysicObject3D const & entity) {
		int nValuesErased = objects.erase(entity);
	   
		if (nValuesErased == 1) {
			return true;
		} else if (nValuesErased == 0) {
			return false;
		} else {
			throw exception();
		}
	}

	AxisAlignedBox3D const & Cell3D::getAxisAlignedBox3D() const {
		return box;
	}

	void Cell3D::clear() {
		objects.clear();
	}

	Vector3D const & Cell3D::getCenter() const {
		return box.getCenter();
	}

	Vector3D const & Cell3D::getHalfExtents() const {
		return box.getHalfExtents();
	}

	int Cell3D::getI() const {
		return i;
	}

	int Cell3D::getJ() const {
		return j;
	}

	int Cell3D::getK() const {
		return k;
	}

	Indexes Cell3D::getIndexes() const {
			return Indexes(getI(), getJ(), getK());
	}

	bool Cell3D::hasAnObjectCollidingWithObject(
		SharedPtrPhysicObject3D const & object,
		PredicateOfSharedPtrPhysicObject3D const & predicate
	) const {
		ConstIteratorType it = begin();
		
		for (; it != end(); ++it) {
			SharedPtrPhysicObject3D otherObject = *it;
			
			if (otherObject == nullptr) {
				throw UnsupportedOperationException("cell contains a null pointer to PhysicObject3D");
			}
			
			if (object != otherObject && predicate.test(otherObject)) {
				if (object->boundingSpheresCollision(*otherObject)) {
					return true;
				}
			}
		}
		
		return false;
	}
	
	bool Cell3D::isEmpty() const {
		return objects.empty();
	}
	
	bool Cell3D::intersectSphere(Sphere const & sphere) const {
		return (getAxisAlignedBox3D().intersectSphere(sphere)).isPositive();
	}

	int Cell3D::numberOfPhysicObject3D(PredicateOfSharedPtrPhysicObject3D const & predicate) const {
		int count = 0;
		ConstIteratorType it;
		
		for (it = objects.begin(); it != objects.end(); ++it) {
			if (predicate.test(*it)) {
				count += 1;
			}
		}
		
		return count;
		//return objects.size();
	}

	vector<PairOfSharedPtrPhysicObject3D> 
			Cell3D::objectsCollidingAndVerifyingPredicate(PredicateOfPairOfSharedPtrPhysicObject3D const & predicate) const {
		vector<PairOfSharedPtrPhysicObject3D> collidingPairs;
		set<SharedPtrPhysicObject3D>::const_iterator i;
		
		for (i = objects.begin(); i != objects.end(); ++i) {
			SharedPtrPhysicObject3D objectPtr1 = *i;
			set<SharedPtrPhysicObject3D>::const_iterator j = i;
			++j;
			
			for(; j != objects.end(); ++j) {
				SharedPtrPhysicObject3D objectPtr2 = *j;
				PairOfSharedPtrPhysicObject3D pairOfObjectPtrs;
				pairOfObjectPtrs = make_pair(objectPtr1, objectPtr2);
				bool pairMatchesPredicate = predicate.test(pairOfObjectPtrs);
				
				if (pairMatchesPredicate) {
					bool boundingSpheresCollide = objectPtr1->boundingSpheresCollision(*objectPtr2);
					
					if (boundingSpheresCollide) {
						bool boundingVolumesCollide = objectPtr1->boundingVolumesCollision(*objectPtr2);
						
						if (boundingVolumesCollide) {
							if (objectPtr1 < objectPtr2) {
								collidingPairs.push_back(make_pair(objectPtr1, objectPtr2));
							} else {
								collidingPairs.push_back(make_pair(objectPtr2, objectPtr1));
							}							
						}
					}
				}
			} 
		}
		
		return collidingPairs;
	}
		
	void Cell3D::print(ostream & out) const {
		out << *this;
	}

	Vector3D Cell3D::randomPosition() const {
		Real dx = util::Rand<Real>::getInstance().next(-1.0, 1.0) * getHalfExtents().getX();
		Real dy = util::Rand<Real>::getInstance().next(-1.0, 1.0) * getHalfExtents().getY();
		Real dz = util::Rand<Real>::getInstance().next(-1.0, 1.0) * getHalfExtents().getZ();
		Vector3D delta(dx, dy, dz);
		Vector3D result(Vector3D::add(getCenter(), delta));
		
		return result;
	}
	
	ostream & operator<<(ostream & out, Cell3D const & cell)
	{
		out << "Cell3D{i=" << cell.getI()<< ", j=" << cell.getJ() << ", k=" << cell.getK();
		out << ", center={" << cell.getCenter();
		out << "}, halfExtents={" << cell.getHalfExtents();
		out << "}, objects=[";
	   
		Cell3D::ConstIteratorType it = cell.begin();
	   
		if (it != cell.end()) {
			out << "ID=" << (*it)->getID();
			++it;
		}
	   
		for (; it != cell.end(); ++it) {
			out << ", ID=" << (*it)->getID();
		}
	   
		out << "]}";
	   
		return out;
	}
	
	void Cell3D::test() {
		class PhysicObject: public PhysicObject3D {
		public:
			PhysicObject() : boundingVolume_(std::make_shared<Sphere>(Vector3D::zero(), 0.25)) {}
			
			Sphere const & getBoundingSphere() const {
				Sphere const & sphere = *std::dynamic_pointer_cast<Sphere>(boundingVolume_);
				
				return sphere;
			}
			
			SharedPtrIntersectable const & getBoundingVolume() const { 
				return boundingVolume_;
			}
			
			Vector3D const & getPosition() const {
				return boundingVolume_->getPosition();
			}
			//Matrix3D const & getOrientation() const{}
			//std::shared_ptr<Mesh> const & getMesh() const{}
			bool isMovable() const {
				return false;
			}
			
			void print(std::ostream & out) const {}
			void setBoundingSphere(Sphere const & sphere) {}
			void setMovable(bool movable) {}
			void setPosition(Vector3D const & pstn) {}
			
		private:
			SharedPtrIntersectable boundingVolume_;
		};
		
		Vector3D position(Vector3D::zero());
		Vector3D halfExtents(1, 1, 1);
		SharedPtrCell3D cell = std::make_shared<Cell3D>(0, 0, 0, position, halfExtents);
		std::cout << "cell is empty ? " << (cell->isEmpty() ? "true": "false") << "\n";
		SharedPtrPhysicObject3D object = std::make_shared<PhysicObject>();
		bool added = cell->addPhysicObject3D(object);
		
		if (added) {
			std::cout << "object added\n";
		}
		
		std::cout << "cell is empty ? " << (cell->isEmpty() ? "true": "false") << "\n";
	}
}