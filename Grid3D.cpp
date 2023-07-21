#include "Grid3D.h"
#include "Cell3D.h"
#include "Matrix3D.h"
#include "PhysicObject3D.h"
#include "PredicateOfPairOfSharedPtrPhysicObject3D.h"
#include "Rand.h"
#include "Real.h"
#include "Sphere.h"
#include "UnsupportedOperationException.h"

using namespace std;

namespace ngn {
	
	Grid3D::Grid3D() :
		origin(Vector3D::zero()),
		extents(Vector3D::zero()),
		box(boxFromOriginAndExtents(Vector3D::zero(), Vector3D::zero())),
		partitions({0, 0, 0}),
		cells(),
		farthestPointFromOrigin(Vector3D::add(origin, extents))
	{
		
	}
	
	Grid3D::Grid3D(Vector3D const & orgn, Vector3D const & extnts, Partitions const & prttns) :
		origin(orgn),
		extents(extnts),
		box(boxFromOriginAndExtents(orgn, extnts)),
		partitions(prttns),
		cells(),
		farthestPointFromOrigin(Vector3D::add(origin, extents))
	{
		if (numberOfPartitionsAlongXAxis() <= 0 || numberOfPartitionsAlongYAxis() <= 0 || numberOfPartitionsAlongZAxis() <= 0) {
			throw exception();
		}
	   
		Vector3D cellExtents;
		cellExtents.setX(extents.getX() / partitions.getXAxisPartitions());
		cellExtents.setY(extents.getY() / partitions.getYAxisPartitions());
		cellExtents.setZ(extents.getZ() / partitions.getZAxisPartitions());
		Vector3D cellHalfExtents = Vector3D::mult(cellExtents, 0.5);
	   
		for (int i = 0; i < partitions.getXAxisPartitions(); ++i) {
			cells.push_back(vector<vector<SharedPtrCell3D>>());
		   
			for (int j = 0; j < partitions.getYAxisPartitions(); ++j) {
				cells.operator[](i).push_back(vector<SharedPtrCell3D>());
			   
				for (int k = 0; k < partitions.getZAxisPartitions(); ++k) {
					Vector3D cellPosition(cellExtents);
					cellPosition.mult(0.5);
					cellPosition.add(getOrigin());
					cellPosition.add(cellExtents.componentProduct(Vector3D(i, j, k)));
					cells.operator[](i).operator[](j).push_back(
						make_shared<Cell3D>(i, j, k, cellPosition, cellHalfExtents)
					);
					//cout << i << j << k << ":\n" << *cells[i][j][k] << "\n";
				}
			}
		}
	}

	bool Grid3D::assignIntersectingCell3DsToPhysicObject3D(SharedPtrPhysicObject3D & object) {
		vector<SharedPtrCell3D> intersectingCell3Ds;
		intersectingCell3Ds = findCell3DsIntersectingPhysicObject3D(object);
		removePhysicObject3DFromItsCells(object);
		object->setIntersectingCell3Ds(intersectingCell3Ds);
		
		if (intersectingCell3Ds.empty()) {
			return false;
		}
		
		for (int unsigned i = 0; i < intersectingCell3Ds.size(); ++i) {
			intersectingCell3Ds[i]->addPhysicObject3D(object);
		}
		
		return true;
	}

	std::pair<bool, std::set<int unsigned>> 
	Grid3D::assignIntersectingCell3DsToArrayOfPhysicObject3Ds(
		std::vector<SharedPtrPhysicObject3D> & objects
	) {
		std::pair<bool, std::set<int unsigned>> result(false, std::set<int unsigned>());
		
		for (int unsigned i = 0; i < objects.size(); ++i) {
			bool assigned = assignIntersectingCell3DsToPhysicObject3D(objects.operator [](i));
			
			if (!assigned) {
				result.second.insert(i);
			}
		}
		
		if (result.second.empty()) {
			result.first = true;
		}
		
		return result;
	}
	
	OrientedBox3D Grid3D::boxFromOriginAndExtents(Vector3D const & origin, Vector3D const & extents) {
		Vector3D halfExtents(Vector3D::mult(extents, (Real)0.5));
		Vector3D center(Vector3D::add(getOrigin(), halfExtents));
		
		return OrientedBox3D(center, Matrix3D::identity(), halfExtents);
	}
	
	bool Grid3D::containsPosition(Vector3D const & position) const {
		Vector3D diff(Vector3D::sub(position, getOrigin()));
		
		for (int i = 0; i < 3; ++i) {
			if (diff.get(i) < 0.0 || diff.get(i) > getExtents().get(i)) {
				return false;
			}
		}
		
		return true;
	}

	bool Grid3D::containsPhysicObject3D(SharedPtrPhysicObject3D const & entity) const {
		if (entity == nullptr) {
			throw UnsupportedOperationException("");
		}
		
		Sphere sphere = entity->getBoundingSphere();
		Intersection::Result result = sphere.intersectOrientedBox3D(box);
		bool intersected = result.isPositive();
		
		return intersected;
	}
	
	vector<SharedPtrCell3D> Grid3D::findCell3DsIntersectingPhysicObject3D(SharedPtrPhysicObject3D const & object) const {
		//std::cout << "vector<SharedPtrCell3D> Grid3D::findCell3DsIntersectingPhysicObject3D";
		//std::cout << "(SharedPtrPhysicObject3D const & object) const\n";
		vector<SharedPtrCell3D> result;
		Sphere sphere = object->getBoundingSphere();
		//std::cout << "sphere = " << sphere << "\n";
		Vector3D maxDistance = Vector3D(sphere.getRadius(), sphere.getRadius(), sphere.getRadius());
		Vector3D minPoint = Vector3D::sub(sphere.getCenter(), maxDistance);
		Indexes minIndexes = indexesOfCell3DContainingPosition(minPoint);
		//std::cout << "minIndexes = " << minIndexes << "\n";
		Vector3D maxPoint = Vector3D::add(sphere.getCenter(), maxDistance);
		Indexes maxIndexes = indexesOfCell3DContainingPosition(maxPoint);
		//std::cout << "maxIndexes = " << maxIndexes << "\n";
		//std::cout << "starting i = " << max(0, minIndexes.getI()) << "\n";
		//std::cout << "ending i = " << min(partitions.getXAxisPartitions(), maxIndexes.getI() + 1) << "\n";
		
		for (int i = max(0, minIndexes.getI()); i < min(partitions.getXAxisPartitions(), maxIndexes.getI() + 1); ++i) {
			for (int j = max(0, minIndexes.getJ()); j < min(partitions.getYAxisPartitions(), maxIndexes.getJ() + 1); ++j) {
				for (int k = max(0, minIndexes.getK()); k < min(partitions.getZAxisPartitions(), maxIndexes.getK() + 1); ++k) {
					//std::cout << "i,j,k = " << i << ", " << j << ", " << k << "\n";
					SharedPtrCell3D cell = getCell3D(i, j, k);
					
					if (cell->intersectSphere(object->getBoundingSphere())) {
						result.push_back(cell);
					}
				}
			}
		}
	   
		return result;
	}

	Grid3D 
	Grid3D::fromOriginExtentsPartitions(
		Vector3D const & worldOrigin,
		Vector3D const & worldExtents,
		Partitions const & partitions
	)
	{
		return Grid3D(worldOrigin, worldExtents, partitions);
	}
		
	Vector3D const & Grid3D::getOrigin() const {
		return origin;
	}

	Vector3D Grid3D::getCell3DHalfExtents() const {
		Vector3D cellExtents;
		cellExtents.setX(extents.getX() / partitions.getXAxisPartitions());
		cellExtents.setY(extents.getY() / partitions.getYAxisPartitions());
		cellExtents.setZ(extents.getZ() / partitions.getZAxisPartitions());
		Vector3D cellHalfExtents(cellExtents);
		cellHalfExtents.mult(0.5);
		
		return cellHalfExtents;
	}

	Vector3D const & Grid3D::getExtents() const {
		return extents;
	}

	Partitions const & Grid3D::getPartitions() const {
		return partitions;
	}
	
	void Grid3D::clearAllCell3Ds() {
		for (int i = 0; i < numberOfPartitionsAlongXAxis(); ++i) {
			for (int j = 0; j < numberOfPartitionsAlongYAxis(); ++j) {
				for (int k = 0; k < numberOfPartitionsAlongZAxis(); ++k) {
					cells[i][j][k]->clear();
				}
			}
		}
	}

	set<SharedPtrCell3D> Grid3D::cellsIntersectingSphereExcept(
		Sphere const & sphere,
		set<SharedPtrCell3D> const & excludedCell3Ds
	) const {
		set<SharedPtrCell3D> result;
		Vector3D delta(sphere.getRadius(), sphere.getRadius(), sphere.getRadius());
		Vector3D minPoint = Vector3D::sub(sphere.getCenter(), delta);
		Indexes minIndexes = indexesOfCell3DContainingPosition(minPoint);
		int minI = max(0, minIndexes.getI());
		int minJ = max(0, minIndexes.getJ());
		int minK = max(0, minIndexes.getK());
		
		Vector3D maxPoint = Vector3D::add(sphere.getCenter(), delta);
		Indexes maxIndexes = indexesOfCell3DContainingPosition(maxPoint);
		int maxI = min(partitions.getXAxisPartitions(), maxIndexes.getI() + 1);
		int maxJ = min(partitions.getYAxisPartitions(), maxIndexes.getJ() + 1);
		int maxK = min(partitions.getZAxisPartitions(), maxIndexes.getK() + 1);
		
		for (int i = minI; i < maxI; ++i) {
			for (int j = minJ; j < maxJ; ++j) {
				for (int k = minK; k < maxK; ++k) {
					SharedPtrCell3D cell = getCell3D(i, j, k);
					bool notContained = excludedCell3Ds.find(cell) == excludedCell3Ds.end();
					
					if (notContained) {
						if (cell->intersectSphere(sphere)) {
							result.insert(cell);
						}
					}
				}
			}
		}
	   
		return result;
	}

	Result Grid3D::closestNeighbor(
		SharedPtrPhysicObject3D const & entity,
		PredicateOfSharedPtrPhysicObject3D const & predicate
	) const {
		Result result = closestNeighborInCell3DsIntersectingPhysicObject3D(entity, predicate);
		int count = 1;
		Real multiplier = 2.0;
		
		while(!result.isPositive()) {
			//cout << "while(!result.isPositive())\n";
			Real radius = count * multiplier * getCell3DHalfExtents().length();
			//cout << "radius = " << radius << "\n";
			Sphere sphere(entity->getPosition(), radius);
			Result tmpRes = closerNeighBorInCell3DsIntersectingSphere(entity, predicate, sphere, result);
			int unsigned previousNumberOfTestedCell3Ds = result.getCell3DsTested().size();
			//cout << "previousNumberOfTestedCell3Ds = " << previousNumberOfTestedCell3Ds << "\n";
			int unsigned currentNumberOfTestedCell3Ds = tmpRes.getCell3DsTested().size();
			//cout << "currentNumberOfTestedCell3Ds = " << currentNumberOfTestedCell3Ds << "\n";
			
			if (currentNumberOfTestedCell3Ds == previousNumberOfTestedCell3Ds) {
				break;
			}
			
			result = tmpRes;
			count += 1;
		}
		
		if (result.isPositive()) {
			//cout << "result.getClosestNeighbor()->getID() = " << result.getClosestNeighbor()->getID() << "\n";
			//cout << "if (result.isPositive())\n";
			Real radius = entity->getPosition().distanceFrom(result.getClosestNeighbor()->getPosition());
			result = closerNeighBorInCell3DsIntersectingSphere(entity, predicate, Sphere(entity->getPosition(), radius), result);
			//cout << "result.getClosestNeighbor()->getID() = " << result.getClosestNeighbor()->getID() << "\n";
			
			return result;
		} 
		
		return result;
	}
		
	Result Grid3D::closestNeighborInCell3DsIntersectingPhysicObject3D(
		SharedPtrPhysicObject3D const & entity,
		PredicateOfSharedPtrPhysicObject3D const & predicate
	) const {
		Result result;
		vector<weak_ptr<Cell3D>> cellsIntersectingPhysicObject3D = entity->getCell3Ds();
		set<SharedPtrCell3D> testedCell3Ds;
		
		for (int unsigned i = 0; i < cellsIntersectingPhysicObject3D.size(); ++i) {
			if (SharedPtrCell3D cell = cellsIntersectingPhysicObject3D.operator[](i).lock()) {
				//cout << "cell = grid(" << cell->getI() << ", " << cell->getJ() << ", " << cell->getK() << ")\n";
				Result tmpRes = cell->closestNeighborToPhysicObject3D(entity, predicate);
				
				if (tmpRes.isPositive()) {
					if (tmpRes.getDistance() < result.getDistance()) {
						result = tmpRes;
					}
				}
				
				testedCell3Ds.insert(cell);
			}
		}
		
		result.setCell3DsTested(testedCell3Ds);	
		
		return result;
	}
	
	Result Grid3D::closerNeighBorInCell3DsIntersectingSphere(
		SharedPtrPhysicObject3D const & entity, 
		PredicateOfSharedPtrPhysicObject3D const & predicate,
		Sphere const & sphere, 
		Result const & bestResult
	) const 
	{
		Real tol = 1.0e-6;
		
		if (!entity->getPosition().equalsWithTol(sphere.getCenter(), tol)) {
			throw exception();
		}
		
		Result result = bestResult;
		set<SharedPtrCell3D> testedCell3Ds = bestResult.getCell3DsTested();
		set<SharedPtrCell3D> intersectingCell3Ds = cellsIntersectingSphereExcept(sphere, testedCell3Ds);
		set<SharedPtrCell3D>::const_iterator it;
		
		for (it = intersectingCell3Ds.begin(); it != intersectingCell3Ds.end(); ++it) {
			//cout << "cell = grid(" << (*it)->getI() << ", " << (*it)->getJ() << ", " << (*it)->getK() << ")\n";
			Result tmpRes = (*it)->closestNeighborToPhysicObject3D(entity, predicate);
			
			if(tmpRes.isPositive()) {
				if (tmpRes.getDistance() < result.getDistance()) {
					result = tmpRes;
					//cout << "###result.getClosestNeighbor()->getID() = ";
					//cout << result.getClosestNeighbor()->getID() << "\n";
				}
			}
			
			testedCell3Ds.insert(*it);
		}
		
		result.setCell3DsTested(testedCell3Ds);
		
		return result;
	}
	
	std::vector<SharedPtrCell3D> Grid3D::emptyCells() const {
		std::vector<SharedPtrCell3D> emptyCells;
		
		for (int i = 0; i < numberOfPartitionsAlongXAxis(); ++i) {
			for (int j = 0; j < numberOfPartitionsAlongYAxis(); ++j) {
				for (int k = 0; k < numberOfPartitionsAlongZAxis(); ++k) {
					SharedPtrCell3D cell = getCell3D(i, j, k);
					
					if (cell->isEmpty()) {
						emptyCells.push_back(cell);
					}
				}
			}
		}
		
		return emptyCells;
	}
	
	SharedPtrCell3D Grid3D::getCell3D(int i, int j, int k) const {
		return cells.operator[](i).operator[](j).operator[](k);
	}

	int Grid3D::numberOfCells() const {
		return numberOfPartitionsAlongXAxis() * numberOfPartitionsAlongYAxis() * numberOfPartitionsAlongZAxis();
	}
	
	int Grid3D::numberOfPhysicObject3D(PredicateOfSharedPtrPhysicObject3D const & predicate) const {
		//int result = 0;
		std::set<SharedPtrPhysicObject3D> objects;
	   
		for (int i = 0; i < numberOfPartitionsAlongXAxis(); ++i) {
			for (int j = 0; j < numberOfPartitionsAlongYAxis(); ++j) {
				for (int k = 0; k < numberOfPartitionsAlongZAxis(); ++k) {
					//result += getCell3D(i, j, k)->numberOfPhysicObject3D(predicate);
					Cell3D::ConstIteratorType first = getCell3D(i, j, k)->begin();
					Cell3D::ConstIteratorType last = getCell3D(i, j, k)->end();
					Cell3D::ConstIteratorType it;
					
					for (it = first; it != last; ++it) {
						if (predicate.test(*it)) {
							objects.insert(*it);
						}
					}
				}
			}
		}
	   
		//return result;
		return objects.size();
	}

	int Grid3D::numberOfPartitionsAlongXAxis() const {
		return partitions.getXAxisPartitions();
	}

	int Grid3D::numberOfPartitionsAlongYAxis() const {
		return partitions.getYAxisPartitions();	
	}

	int Grid3D::numberOfPartitionsAlongZAxis() const {
		return partitions.getZAxisPartitions();
	}

	Indexes Grid3D::indexesOfCell3DContainingPosition(Vector3D const & position) const {
		Vector3D diff = Vector3D::sub(position, origin);
		int i = static_cast<int>(partitions.getXAxisPartitions() * diff.getX() / extents.getX());
		int j = static_cast<int>(partitions.getYAxisPartitions() * diff.getY() / extents.getY());
		int k = static_cast<int>(partitions.getZAxisPartitions() * diff.getZ() / extents.getZ());
		//std::cout << "partitions.getZAxisPartitions() * diff.getZ() = ";
		//std::cout << partitions.getZAxisPartitions() * diff.getZ() << "\n";
		//std::cout << "extents.getZ() = " << extents.getZ() << "\n";
	   
		return Indexes(i, j, k);//array<int, 3>({i, j, k});
	}

	bool Grid3D::insertRandomlyPhysicObject3DInFirstEmptyCell3D(SharedPtrPhysicObject3D & object) {
		for (int i = 0; i < numberOfPartitionsAlongXAxis(); ++i) {
			for (int j = 0; j < numberOfPartitionsAlongYAxis(); ++j) {
				for (int k = 0; k < numberOfPartitionsAlongZAxis(); ++k) {
					SharedPtrCell3D cell = getCell3D(i, j, k);
					
					if (cell->isEmpty()) {
						bool objectSetInEmptyCell = setPhysicObject3DAtRandomPositionInCell3D(object, cell);
						
						if (objectSetInEmptyCell) {
							return true;
						}
					}
				}
			}
		}
		
		return false;
	}
	
	bool Grid3D::setPhysicObject3DAtRandomPositionInCell3D(SharedPtrPhysicObject3D & object, SharedPtrCell3D & cell) {
		//std::cout << "cell_" << i << j << k << " is empty\n";
		Vector3D pos = cell->randomPosition();
		//std::cout << "cell_" << i << j << k << " = " << *cell << "\n";
		object->setPosition(pos);
		//std::cout << "pos = " << pos << "\n";
		//std::cout << "object position = " << object->getPosition() << "\n";
		bool assigned = assignIntersectingCell3DsToPhysicObject3D(object);
		//object->printCell3DsIndexes(std::cout);
		
		if (assigned) {
			//std::cout << "cell_" << i << j << k << " is still empty ?";
			//std::cout << (cell->isEmpty() ? "true": "false") << "\n";
			return true;
		} else {
			throw UnsupportedOperationException("object not inserted in first empty cell");
		}
	}
	
	bool Grid3D::insertPhysicObject3DInRandomEmptyCell3D(SharedPtrPhysicObject3D & object) {
		int nCells = numberOfCells();
		int index = util::Rand<int>::getInstance().next(0, nCells);
		int div0 = index / numberOfPartitionsAlongYAxis() * numberOfPartitionsAlongZAxis();
		int i0 = div0;
		int r0 = index - div0 * numberOfPartitionsAlongYAxis() * numberOfPartitionsAlongZAxis();
		int div1 = r0 / numberOfPartitionsAlongZAxis();
		int i1 = div1;
		int r1 = r0 - div1 * numberOfPartitionsAlongZAxis();
		int i2 = r1;
		
		for (int i = i0; i < numberOfPartitionsAlongXAxis(); ++i) {
			int j = 0;
			
			if (i == i0) {
				j = i1;	
			}
			
			for (; j < numberOfPartitionsAlongYAxis(); ++j) {
				int k = 0;
				
				if (i == i0 && j == i1) {
					k = i2;
				}
				
				for (; k < numberOfPartitionsAlongZAxis(); ++k) {
					SharedPtrCell3D cell = getCell3D(i, j, k);

					if (cell->isEmpty()) {
						bool objectSetInEmptyCell = setPhysicObject3DAtRandomPositionInCell3D(object, cell);
						
						if (objectSetInEmptyCell) {
							return true;
						}
					}
				}
			}
		}
		
		for (int i = 0; i < numberOfPartitionsAlongXAxis(); ++i) {
			for (int j = 0; j < numberOfPartitionsAlongYAxis(); ++j) {
				for (int k = 0; k < numberOfPartitionsAlongZAxis(); ++k) {
					if (i == i0 && j == i1 && k == i2) {
						break;
					}
					
					SharedPtrCell3D cell = getCell3D(i, j, k);
					
					if (cell->isEmpty()) {
						bool objectSetInEmptyCell = setPhysicObject3DAtRandomPositionInCell3D(object, cell);
						
						if (objectSetInEmptyCell) {
							return true;
						}
					}
				}
			}
		}
		
		return false;
	}
	
	set<SharedPtrCell3D> Grid3D::intersectingCell3DsWithSphereExceptCell3Ds(
		Sphere const & sphere,
		set<SharedPtrCell3D> const & cells
	) const
	{
		Indexes cellIndexes = indexesOfCell3DContainingPosition(sphere.getCenter());
	   
		for (int i = 0; i < 3; ++i) {
			if (cellIndexes.get(i) < 0 || cellIndexes.get(i) >= partitions.getAxisPartitions(i)) {
				throw exception();
			}
		}
	   
		Vector3D delta(sphere.getRadius(), sphere.getRadius(), sphere.getRadius());
		Vector3D maxPoint(sphere.getCenter());
		maxPoint.add(delta);
		Indexes maxCell3DIndexes = indexesOfCell3DContainingPosition(maxPoint);
		int max_i = min(numberOfPartitionsAlongXAxis(), maxCell3DIndexes.getI() + 1);
		int max_j = min(numberOfPartitionsAlongYAxis(), maxCell3DIndexes.getJ() + 1);
		int max_k = min(numberOfPartitionsAlongZAxis(), maxCell3DIndexes.getK() + 1);
	   
		Vector3D minPoint(sphere.getCenter());
		minPoint.sub(delta);
		Indexes minCell3DIndexes = indexesOfCell3DContainingPosition(minPoint);
		int min_i = max(0, minCell3DIndexes.getI());
		int min_j = max(0, minCell3DIndexes.getJ());
		int min_k = max(0, minCell3DIndexes.getK());

		set<SharedPtrCell3D> result;	
	   
		for (int i = min_i; i < max_i; ++i) {
			for (int j = min_j; j < max_j; ++j) {
				for (int k = min_k; k < max_k; ++k) {
					SharedPtrCell3D cell = getCell3D(i, j, k);
					bool contained = (cells.find(cell) != cells.end());
					
					if (contained) {
						continue;
					}
				   
					if ((cell->getAxisAlignedBox3D().intersectSphere(sphere)).isPositive()) {
						result.insert(cell);
					}						
				}
			}
		}
	   
		return result;
	}

	bool Grid3D::hasObjectInGridCollidingWithObject(
		SharedPtrPhysicObject3D const & object,
		PredicateOfSharedPtrPhysicObject3D const & predicate
	) const {
		if (object == nullptr) {
			throw UnsupportedOperationException("object is null");
		}
		
		std::vector<WeakPtrCell3D> objectCells = object->getCell3Ds();
		
		for (int unsigned i = 0; i < objectCells.size(); ++i) {
			if (SharedPtrCell3D cell = objectCells.operator [](i).lock()) {
				if (cell->hasAnObjectCollidingWithObject(object, predicate)) {
					return true;
				}
			}
		}
		
		return false;
	}
	
	vector<PairOfSharedPtrPhysicObject3D> 
	Grid3D::objectsCollidingAndVerifyingPredicate(PredicateOfPairOfSharedPtrPhysicObject3D const & predicate) const {
		vector<PairOfSharedPtrPhysicObject3D> result;
		set<PairOfSharedPtrPhysicObject3D> orderedResult;

		for (int i = 0; i < numberOfPartitionsAlongXAxis(); ++i) {
			for (int j = 0; j < numberOfPartitionsAlongYAxis(); ++j) {
				for (int k = 0; k < numberOfPartitionsAlongZAxis(); ++k) {
					SharedPtrCell3D cell = getCell3D(i, j, k);
					vector<PairOfSharedPtrPhysicObject3D> tmpRes = cell->objectsCollidingAndVerifyingPredicate(predicate);
					orderedResult.insert(tmpRes.begin(), tmpRes.end());
					
					/*if (!tmpRes.empty()) {
						cout << "cell" << i << j << k << " has " << tmpRes.size() << " pair of colliding objects\n"; 
					}*/
				}
			}
		}
		
		result.insert(result.end(), orderedResult.begin(), orderedResult.end());
		
		return result;
	}

	Vector3D Grid3D::randomPosition() const {
		Real ax = util::Rand<Real>::getInstance().next();
		Real x = ax * getExtents().getX();
		Real ay = util::Rand<Real>::getInstance().next();
		Real y = ay * getExtents().getY();
		Real az = util::Rand<Real>::getInstance().next();
		Real z = az * getExtents().getZ();
		Vector3D res(x, y, z);
		res.add(getOrigin());
		
		return res;
	}
	
	void Grid3D::relocateOutOfBoundsPhysicObject3D(SharedPtrPhysicObject3D & object) {
		//std::cout << "object->position = " << object->getPosition() << "\n";
		//std::cout << "object bounding sphere = " << object->getBoundingSphere() << "\n";
		Vector3D min = getOrigin();
		Vector3D max = farthestPointFromOrigin;
		//std::cout << "min = " << min << "\n";
		//std::cout << "max = " << max << "\n";
		Real minX = min.getX();
		Real maxX = max.getX();
		Real const eps = 1.0e-6;

		Vector3D position = object->getPosition();
		Vector3D newPosition = position;
		bool isPositionOutside = false;

		if (position.getX() > maxX) {
			newPosition.setX(minX + eps);
			isPositionOutside = true;
		} else if (position.getX() < minX) {
			newPosition.setX(maxX - eps);
			isPositionOutside = true;
		}

		Real minY = min.getY();
		Real maxY = max.getY();

		if (position.getY() > maxY) {
			newPosition.setY(minY + eps);
			isPositionOutside = true;
		} else if (position.getY() < minY) {
			newPosition.setY(maxY - eps);
			isPositionOutside = true;
		}

		Real minZ = min.getZ();
		Real maxZ = max.getZ();
		
		if (position.getZ() > maxZ) {
			newPosition.setZ(minZ + eps);
			isPositionOutside = true;
		} else if (position.getZ() < minZ) {
			newPosition.setZ(maxZ - eps);
			isPositionOutside = true;
		}
		
		//std::cout << "object->position = " << object->getPosition() << "\n";
		//std::cout << "isPositionOutside = " << (isPositionOutside ? "true": "false") << "\n";
		//std::cout << "newPosition = " << newPosition << "\n";
		
		if (isPositionOutside) {
			object->setPosition(newPosition);
			//std::cout << "object new position = " << object->getPosition() << "\n";
			//std::cout << "object bounding sphere = " << object->getBoundingSphere() << "\n";
			
			bool assigned = assignIntersectingCell3DsToPhysicObject3D(object);
			
			if (!assigned) {
				throw UnsupportedOperationException("object not assigned to a cell!");
			}
		}
	}
	
	void Grid3D::removePhysicObject3DFromItsCells(SharedPtrPhysicObject3D object) {
		std::vector<WeakPtrCell3D> objectCells = object->getCell3Ds();
		
		for (int unsigned i = 0; i < objectCells.size(); ++i) {
			if (SharedPtrCell3D objectCell = objectCells.operator [](i).lock()) {
				objectCell->removePhysicObject3D(object);
			}
		}
	}
}