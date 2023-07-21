#include "RandomGeneratorOfSweepersAndMines.h"
#include "AxisAngle.h"
#include "BoundingVolumeBuilder3D.h"
#include "IsSharedPtrMine.h"
#include "IsSharedPtrPhysicObject3D.h"
#include "IsSharedPtrSmartMineSweeper.h"
#include "PredicateOfPairOfSharedPtrPhysicObject3D.h"
#include "Sphere.h"
#include "Tank.h"
#include "UnsupportedOperationException.h"
#include "Vector3D.h"

namespace smrtsw {
	
	int RandomGeneratorOfSweepersAndMines::maximumTries = 30;
	
	template <class Obj>
	Real RandomGeneratorOfSweepersAndMines::getMinimumDistanceBetweenObjects() const {
		throw UnsupportedOperationException("FUNCTION NOT DEFINED!");
	}
	
	template <>
	Real RandomGeneratorOfSweepersAndMines::getMinimumDistanceBetweenObjects<Mine>() const {
		return parameters_.getMinimumDistanceBetweenMines();
	}
	
	template <>
	Real RandomGeneratorOfSweepersAndMines::getMinimumDistanceBetweenObjects<SmartMineSweeper>() const {
		return parameters_.getMinimumDistanceBetweenSweepers();
	}
	
	template <class Obj>
	void RandomGeneratorOfSweepersAndMines::setZCoordinate(Vector3D & position) const {
		throw UnsupportedOperationException("FUNCTION NOT DEFINED!");
	}
	
	template <>
	void RandomGeneratorOfSweepersAndMines::setZCoordinate<Mine>(Vector3D & position) const {
		position.setZ(parameters_.getMineRadius() + getGrid()->getOrigin().getZ());
	}
	
	template <>
	void RandomGeneratorOfSweepersAndMines::setZCoordinate<SmartMineSweeper>(Vector3D & position) const {
		position.setZ(getGrid()->getOrigin().getZ() + parameters_.getSweeperHeight() / 2.0);
	}
	
	template <class Obj>
	Vector3D RandomGeneratorOfSweepersAndMines::randomPosition() const {
		throw UnsupportedOperationException("FUNCTION NOT DEFINED!");
	}
	
	template <>
	Vector3D RandomGeneratorOfSweepersAndMines::randomPosition<Mine>() const {
		Vector3D position = getGrid()->randomPosition();
		setZCoordinate<Mine>(position);
		
		return position;
	}
	
	template <>
	Vector3D RandomGeneratorOfSweepersAndMines::randomPosition<SmartMineSweeper>() const {
		Vector3D position = getGrid()->randomPosition();
		setZCoordinate<SmartMineSweeper>(position);
		
		return position;
	}
	
	class AreObjectsOfTheSameType {
	public:
		AreObjectsOfTheSameType() {}
		
		bool test(
			SharedPtrPhysicObject3D const & object1, 
			SharedPtrPhysicObject3D const & object2
		) const {
			IsSharedPtrMine isMine;
			IsSharedPtrSmartMineSweeper isSweeper;
			
			bool test1 = isMine.test(object1) && isMine.test(object2);
			
			if (test1) {
				return true;
			}
			
			bool test2 = isSweeper.test(object1) && isSweeper.test(object2);
			
			return test2; 
		}
	};
	
	class IsNotFarEnoughFromObject: public PredicateOfSharedPtrPhysicObject3D {
	public:
		IsNotFarEnoughFromObject(
			SharedPtrPhysicObject3D const & object,
			Real dist
		) : 
		object_(object),
		squaredDistance_(dist * dist) {}
		
		bool test(SharedPtrPhysicObject3D const & object) const {
			if (object_ == object) {
				return false;
			}

			AreObjectsOfTheSameType predicate;
			
			if (!predicate.test(object_, object)) {
				return false;
			}
			
			Real sqrD = object_->squaredDistanceBetweenCenters(*object);
			bool result = sqrD <= squaredDistance_;
			
			return result;
		}
		
	private:
		SharedPtrPhysicObject3D object_;
		Real squaredDistance_;
	};
	
////////////////////////////////////////////////////////////////////////////////

	RandomGeneratorOfSweepersAndMines::RandomGeneratorOfSweepersAndMines() {
	}
	
	RandomGeneratorOfSweepersAndMines::RandomGeneratorOfSweepersAndMines(
		std::shared_ptr<Grid3D> const & grid,
		ai::Parameters const & parameters
	) :
		grid_(grid),
		parameters_(parameters),
		functions_(buildNeuralNetworkFunctions())
	{
		
	}
		
	std::shared_ptr<std::vector<smrtsw::SharedPtrMine>> 
	RandomGeneratorOfSweepersAndMines::generateMines() const
	{
		std::shared_ptr<std::vector<smrtsw::SharedPtrMine>> mines;
		mines = std::make_shared<std::vector<smrtsw::SharedPtrMine>>();
		int failedAttempts = 0;
		
		for (int i = 0; i < parameters_.getNumberOfMines(); ++i) {
			SharedPtrMine mine = generateMineAtRandomPosition();
			SharedPtrPhysicObject3D object = mine;
			/*bool insertedInEmptySpace = setObjectInEmptySpace<Mine>(object);
			
			if (!insertedInEmptySpace) {
				++failedAttempts;
			}*/
			
			bool succeed = setObjectAtDistanceFromOthers<Mine>(object);
			
			if (!succeed) {
				++failedAttempts;
			}
			
			mines->push_back(mine);			
		}
		
		std::cout << "number of failedAttempts = " << failedAttempts << "\n";
		
		return mines;
	}
	
	template<class PhysicObjectType>
	bool RandomGeneratorOfSweepersAndMines::setObjectInEmptySpace(
		SharedPtrPhysicObject3D & object
	) const {
		std::shared_ptr<Grid3D> grid = getGrid();
		IsSharedPtrPhysicObject3D isSharedPtrPhysicObject3D;
		int counter = 0;
		
		while (true) {
			++counter;
			bool assigned = grid->assignIntersectingCell3DsToPhysicObject3D(object);
			
			if (!assigned) {
				throw UnsupportedOperationException("");
			}			
			
			bool collided = 
				grid->hasObjectInGridCollidingWithObject(
					object, 
					isSharedPtrPhysicObject3D
				);
				
			if (!collided) {
				return true;
			}
			
			if (counter == maximumTries) {
				return false;
			}
			
			Vector3D position = randomPosition<PhysicObjectType>();
			object->setPosition(position);
		}
	}
	
	template <class PhysicObjectType>
	bool RandomGeneratorOfSweepersAndMines::setObjectAtDistanceFromOthers(
		SharedPtrPhysicObject3D & object
	) const {
		std::shared_ptr<Grid3D> grid = getGrid();
		IsNotFarEnoughFromObject isNotFarEnoughFromObject(
			object,
			parameters_.getMinimumDistanceBetweenMines()
		);
		bool allObjectsAreFarEnough = 
			areNeighborObjectsFarEnough(
				object, 
				getMinimumDistanceBetweenObjects<PhysicObjectType>()
			);
		int counter = 0;
		
		while (!allObjectsAreFarEnough && counter < maximumTries) {
			Vector3D position = randomPosition<PhysicObjectType>();
			object->setPosition(position);
			bool assigned = grid->assignIntersectingCell3DsToPhysicObject3D(object);
			
			if (!assigned) {
				throw UnsupportedOperationException("");
			}
			
			allObjectsAreFarEnough = 
				areNeighborObjectsFarEnough(
					object,
					getMinimumDistanceBetweenObjects<PhysicObjectType>()
				);
			++counter;
		}
		
		return allObjectsAreFarEnough;
		/*IsSharedPtrPhysicObject3D isSharedPtrPhysicObject3D;
		
		if (allObjectsAreFarEnough) {
			return true;
		} else {
			bool inserted = grid->insertRandomlyPhysicObject3DInFirstEmptyCell3D(object);
			
			if (inserted) {
				Vector3D position = object->getPosition();
				setZCoordinate<PhysicObjectType>(position);
				object->setPosition(position);
				bool collided = 
					grid->hasObjectInGridCollidingWithObject(
						object, 
						isSharedPtrPhysicObject3D
					);
				
				return collided;
			} else {
				std::cout << "Object not inserted in first empty cell\n";
				
				return false;
			}
		}*/
	}
		
	SharedPtrMine RandomGeneratorOfSweepersAndMines::generateMineAtRandomPosition() const {
		Vector3D position = randomPosition<Mine>();
		ngn::SharedPtrIntersectable sphere;
		sphere = std::make_shared<ngn::Sphere>(position, parameters_.getMineRadius());
		SharedPtrMine mine;
		mine = std::make_shared<Mine>(position, sphere);
		
		return mine;
	}
	
	std::shared_ptr<std::vector<smrtsw::SharedPtrSmartMineSweeper>>
	RandomGeneratorOfSweepersAndMines::generateSweepers() const
	{
		std::shared_ptr<std::vector<smrtsw::SharedPtrSmartMineSweeper>> sweepers;
		sweepers = std::make_shared<std::vector<smrtsw::SharedPtrSmartMineSweeper>>();
		int failedAttempts = 0;
		
		for (int i = 0; i < parameters_.getNumberOfSweepers(); ++i) {
			SharedPtrSmartMineSweeper sweeper = generateSweeperAtRandomPosition();
			SharedPtrPhysicObject3D object = sweeper;
			/*bool insertedInEmptySpace = setObjectInEmptySpace<SmartMineSweeper>(object);
			
			if (!insertedInEmptySpace) {
				++failedAttempts;
			}*/
			
			bool succeed = setObjectAtDistanceFromOthers<SmartMineSweeper>(object);
			
			if (!succeed) {
				++failedAttempts;
			}
			
			sweepers->push_back(sweeper);			
		}
		
		std::cout << "number of failedAttempts = " << failedAttempts << "\n";
		
		return sweepers;
	}
	
	bool RandomGeneratorOfSweepersAndMines::areNeighborObjectsFarEnough(
		SharedPtrPhysicObject3D object,
		Real minimumDistance
	) const {
		IsNotFarEnoughFromObject isNotFarEnoughFromObject(
			object,
			minimumDistance
		);
		std::set<SharedPtrPhysicObject3D> objectsInCells = object->objectsInCells();
		std::set<SharedPtrPhysicObject3D>::const_iterator start = objectsInCells.begin();
		std::set<SharedPtrPhysicObject3D>::const_iterator stop = objectsInCells.end();
		std::set<SharedPtrPhysicObject3D>::const_iterator it;
		
		for (it = start; it != stop; ++it) {
			if (isNotFarEnoughFromObject.test(*it)) {
				return false;
			}
		}
		
		return true;
	}
	
	std::pair<
		std::shared_ptr<std::vector<smrtsw::SharedPtrSmartMineSweeper>>, 
		std::shared_ptr<std::vector<smrtsw::SharedPtrMine>>
	> 
	RandomGeneratorOfSweepersAndMines::generateSweepersAndMines() const
	{
		return std::pair<
					std::shared_ptr<std::vector<smrtsw::SharedPtrSmartMineSweeper>>, 
					std::shared_ptr<std::vector<smrtsw::SharedPtrMine>>
				> (generateSweepers(), generateMines());
	}
	
	std::vector<std::shared_ptr<std::vector<ngn::SharedPtrFunction>>> 
	RandomGeneratorOfSweepersAndMines::buildNeuralNetworkFunctions() const {
		std::vector<std::shared_ptr<std::vector<ngn::SharedPtrFunction>>> functions;
		SharedPtrFunction function = parameters_.getActivationFunction();
		std::vector<int> nNeuronsbyLayer = parameters_.getNumberOfNeuronsByNeuralNetworkLayer();
		
		for (int unsigned i = 0; i < nNeuronsbyLayer.size(); ++i) {
			std::shared_ptr<std::vector<ngn::SharedPtrFunction>> layerFunctions;
			layerFunctions = std::make_shared<std::vector<ngn::SharedPtrFunction>>();
			int nNeurons = nNeuronsbyLayer.operator [](i);
			
			for (int j = 0; j < nNeurons; ++j) {
				layerFunctions->push_back(function);
			}
			
			functions.push_back(layerFunctions);
		}
		
		return functions;
	}
	
	SharedPtrSmartMineSweeper 
	RandomGeneratorOfSweepersAndMines::generateSweeperAtRandomPosition() const {
		//std::cout << "generateSweeperAtRandomPosition(...)\n";
		SharedPtrBrain brain = generateSweeperBrain();
		SharedPtrMobile car = generateSweeperMobile();
		SharedPtrMine closestMine = nullptr;
		SharedPtrSmartMineSweeper sweeper;
		sweeper = std::make_shared<SmartMineSweeper>(brain, car, closestMine);
		
		return sweeper;
	}
	
	SharedPtrBrain RandomGeneratorOfSweepersAndMines::generateSweeperBrain() const {
		int nInputs = parameters_.getNumberOfInputs();
		std::vector<int> nNeuronsbyLayer = parameters_.getNumberOfNeuronsByNeuralNetworkLayer();
		Real minimumWeight = -1.0;
		Real maximumWeight = 1.0;
		Range weightRange(minimumWeight, maximumWeight);
		NeuralNetwork cnn = NeuralNetwork::random(nInputs, nNeuronsbyLayer, weightRange, functions_);
		int numberOfCollectedMines = 0;
		SharedPtrBrain brain = std::make_shared<Brain>(cnn, numberOfCollectedMines);

		return brain;
	}
	
	SharedPtrMobile RandomGeneratorOfSweepersAndMines::generateSweeperMobile() const {
		Real leftTrack = 0.0;
		Real rightTrack = 0.0;
		Real maximumTrackSpeed = parameters_.getMaximumTrackSpeed();
		Real maximumTurnRate = parameters_.getMaximumTurnRate();
		Real halfWheelBase = parameters_.getSweeperWheelBase() / 2.0;
		Real halfWidth = parameters_.getSweeperWidth() / 2.0;
		Real halfHeight = parameters_.getSweeperHeight() / 2.0;
		Vector3D extents(halfWheelBase, halfWidth, halfHeight);
		/*Real radius = 
			Math<Real>::sqrt(
				halfWheelBase * halfWheelBase + 
				halfWidth * halfWidth + 
				halfHeight * halfHeight
			);*/
		Vector3D position = randomPosition<SmartMineSweeper>();
		Real angle = util::Rand<Real>::getInstance().next() * Math<Real>::PI * 2.0;
		Matrix3D orientation = Matrix3D::fromAxisAngle(AxisAngle(Vector3D::z_axis(), angle));
		SharedPtrIntersectable boundingVolume = 
			std::make_shared<OrientedBox3D>(
				position,
				orientation,
				extents
			);
		
		//ngn::Sphere boundingSphere(position, radius);
		ngn::BoundingVolumeBuilder3D builder;
		Real tol = 1.0e-6;
		std::shared_ptr<OrientedBox3D> box = std::dynamic_pointer_cast<OrientedBox3D>(boundingVolume);
		std::vector<Vector3D> corners = box->corners();
		ngn::Sphere boundingSphere(builder.computeSmallestBoundingSphere(corners, tol));
		//Real dist = Vector3D::distanceFrom(boundingSphere.getCenter(), boundingVolume->getPosition());
		Real scale = 1.10;
		boundingSphere = 
			ngn::Sphere(
				boundingVolume->getPosition(),
				boundingSphere.getRadius() * scale
			);
		SharedPtrMobile tank(
			new Tank(
				boundingVolume,
				boundingSphere,
				angle,
				leftTrack,
				rightTrack,
				maximumTrackSpeed,
				maximumTurnRate
			)
		);
		
		return tank;
	}
	
	std::shared_ptr<Grid3D> RandomGeneratorOfSweepersAndMines::getGrid() const {
		std::shared_ptr<Grid3D> grid = grid_.lock();
		
		if (grid == nullptr) {
			throw UnsupportedOperationException("grid is nullptr");
		}
		
		return grid;
	}
	
	bool RandomGeneratorOfSweepersAndMines::objectCollidesWithObjectInArrayOfObjects(
		SharedPtrPhysicObject3D const & object,
		std::vector<SharedPtrPhysicObject3D> const & objects
	) const {
		for (int unsigned i = 0; i < objects.size(); ++i) {
			SharedPtrPhysicObject3D otherObject = objects.operator [](i);
			
			if (object->boundingSpheresCollision(*(otherObject))) {
				return true;
			}
		}
		
		return false;
	}
}