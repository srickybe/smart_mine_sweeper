#include "Simulation.h"
#include "AreBothSharedPtrMovablePhysicObject3D.h"
#include "AxisAngle.h"
#include "BoundingVolumeBuilder3D.h"
#include "Cell3D.h"
#include "DefaultBrainEvolver.h"
#include "DefaultSteeringFunction.h"
#include "Sphere.h"
#include "GeneticAlgorithm.h"
#include "IsSharedPtrMine.h"
#include "IsSharedPtrPhysicObject3D.h"
#include "IsSharedPtrSmartMineSweeper.h"
#include "IsMovableNonMovablePair.h"
#include "Math.h"
#include "NotClosestObjectException.h"
#include "Sphere.h"
#include "UnsupportedOperationException.h"
#include "Tank.h"
#include "Vector2D.h"

namespace smrtsw {
	
	class IsPairOfSweeperAndMine: public PredicateOfPairOfSharedPtrPhysicObject3D {
	public:
		IsPairOfSweeperAndMine() {}
		
		bool test(PairOfSharedPtrPhysicObject3D const & objectPair) const {
			IsSharedPtrMine isMine;
			IsSharedPtrSmartMineSweeper isSweeper;
			
			if (isMine.test(objectPair.first) && isSweeper.test(objectPair.second)) {
				return true;
			}
			
			if (isMine.test(objectPair.second) && isSweeper.test(objectPair.first)) {
				return true;
			} else {
				return false;
			}
		}
	};

	Simulation::Generation::Generation(): 
		number_(0), 
		startTimeMillis_(std::chrono::system_clock::now()),
		currentTime_(0) 
	{
	}
	
	Simulation::Generation::Generation(int number): 
		number_(number), 
		startTimeMillis_(std::chrono::system_clock::now()),
		currentTime_(0) 
	{
		if (number < 0) {
			throw IllegalArgumentException("generation number is negative!\n");
		}
	}
	
	void Simulation::Generation::addBrainOfBestFit(Brain const & brain) {
		brainOfBestFits_.push_back(brain);
	}
	
	Real Simulation::Generation::elapsedTime() const {
		std::chrono::time_point<std::chrono::system_clock> currentTimeMillis;
		currentTimeMillis = std::chrono::system_clock::now();
		std::chrono::duration<Real> res = currentTimeMillis - startTimeMillis_;

		return static_cast<Real>(res.count());
	}
	
	Real Simulation::Generation::getCurrentTime() const {
		return currentTime_;
	}
	
	int Simulation::Generation::getNumber() const {
		return number_;
	}
	
	std::chrono::time_point<std::chrono::system_clock> const & 
	Simulation::Generation::getStartTimeMillis() const {
		return startTimeMillis_;
	}
	
	void Simulation::Generation::incrementTime(Real deltaTime) {
		currentTime_ += deltaTime;
	}
		
	void Simulation::Generation::setStartTimeOfCurrentGenerationMillis(
		std::chrono::time_point<std::chrono::system_clock> const & startTime
	) {
		startTimeMillis_ = startTime;
	}
	
	/*void Simulation::Generation::updateCurrentTime() {
		currentTime_ = elapsedTime();
	}*/
	
	RGBColor const 	Simulation::colorOfMinelessSweeper = RGBColor(0.3, 1.0, 1.0);
	RGBColor const 	Simulation::colorOfBestSweeper = RGBColor::RED;
	RGBColor const 	Simulation::defaultColorOfSweeper = RGBColor(0.0, 1.0, 0.3);//RGBColor::GREEN;
	RGBColor const  Simulation::colorOfMine = RGBColor::BLUE;
		
	Simulation::Simulation() {
		
	}
	
	Simulation::Simulation(
		Parameters const & params,
		Settings const & settings,
		Grid3D const & spacePartition,
		SharedArrayOfSharedSweepers const & sweepers,
		SharedArrayOfSharedMines const & mines,
		SharedPtrSteeringFunction const & steering
	) :
		parameters(params),
		GASettings(settings),
		brainEvolver(std::make_shared<DefaultBrainEvolver>(settings)),
		statistics(),
		grid(std::make_shared<Grid3D>(spacePartition)),
		sweepersAndMinesGenerator(grid, params),
		mineRadius(5.0),
		sleepTimeMillis(static_cast<int>(1000.0 / params.getPhysicsUpdateRate())),
		frameTime(1.0 / params.getPhysicsUpdateRate()),
		generations(),
		onLine(false),
		isSharedMine(new IsSharedPtrMine())
	{
		if (GASettings.getPopulationSize() != params.getNumberOfSweepers()) {
			std::string message = "population size(";
			message += std::to_string(GASettings.getPopulationSize());
			message += ") in file, ";
			message += params.getGASettingsFilePath();
			message += ", for the Genetic Algorithm solver doesn't match the number of ";
			message += "sweepers(";
			message += std::to_string(params.getNumberOfSweepers());
			message += ")\n";
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
		}
		
		if (params.getPhysicsUpdateRate() <= 0) {
			throw IllegalArgumentException("Physics update rate <= 0");
		}
		
		std::cout << "sleepTimeMillis = " << sleepTimeMillis << "\n";
		std::cout << "frameTime = " << frameTime << "\n";
		this->sweepers = sweepers;
		this->steeringFunction = steering;
		std::cout << "sweeper_0's position = " << getSweeper(0)->getPosition() << "\n";
		this->mines = mines;
		addAllMinesToSpacePartition();
		addAllSweepersToSpacePartition();
		findClosestMinesToSweepers();
		setBestSweeper(nullptr);
		this->startTimeMillis = std::chrono::system_clock::now();
		this->currentTimeMillis = this->startTimeMillis;
		this->startTimeOfCurrentGenerationMillis = this->currentTimeMillis;
		Generation generation;
		generations.push_back(generation);
		setBestFitness(0);
		//initializeGraphics();
	}

	Simulation::Simulation(
		Parameters const & params,
		SharedPtrSteeringFunction const & steering
	) :
		parameters(params),
		GASettings(readGASettingsFromFilePath(params.getGASettingsFilePath())),
		statistics(),
		mineRadius(5.0),
		sleepTimeMillis(static_cast<int>(1000.0 / params.getPhysicsUpdateRate())),
		frameTime(1.0 / params.getPhysicsUpdateRate()),
		generations(),
		onLine(false),
		isSharedMine(new IsSharedPtrMine())
	{
		std::cout << "GASettings =\n" << GASettings << "\n";

		if (GASettings.getPopulationSize() != params.getNumberOfSweepers()) {
			std::string message = "population size(";
			message += std::to_string(GASettings.getPopulationSize());
			message += ") in file, ";
			message += params.getGASettingsFilePath();
			message += ", for the Genetic Algorithm solver doesn't match the number of ";
			message += "sweepers(";
			message += std::to_string(params.getNumberOfSweepers());
			message += ")\n";
			std::cout << "message = " << message << "\n";
			throw IllegalArgumentException(message);
		}
		
		if (params.getPhysicsUpdateRate() <= 0) {
			throw IllegalArgumentException("Physic update rate <= 0");
		}
		
		std::cout << "sleepTimeMillis = " << sleepTimeMillis << "\n";
		std::cout << "frameTime = " << frameTime << "\n";
		this->steeringFunction = steering;
		this->brainEvolver = std::make_shared<DefaultBrainEvolver>(GASettings);
		this->grid = 
			std::make_shared<Grid3D>(
				spacePartitionFromOriginExtentsPartitions(
					params.getWorldOrigin(),
					params.getWorldExtents(),
					Partitions(
						params.getNumberOfRowsOfSpacePartition(),
						params.getNumberOfColumnsOfSpacePartition(),
						1
					)
				)
			);
		
		std::pair<
			SharedArrayOfSharedSweepers, 
			SharedArrayOfSharedMines
		> pairOfSweepersAndMines;
		pairOfSweepersAndMines = sweepersAndMinesGenerator.generateSweepersAndMines();
		this->sweepers = pairOfSweepersAndMines.first;
		this->mines = pairOfSweepersAndMines.second;
		IsSharedPtrMine predicate1;
		std::cout << "####number of mines = " << grid->numberOfPhysicObject3D(predicate1) << "\n";
		IsSharedPtrSmartMineSweeper predicate2;
		std::cout << "####number of sweepers = " << grid->numberOfPhysicObject3D(predicate2) << "\n";
		findClosestMinesToSweepers();
		setBestSweeper(findBestSweeper());
		this->startTimeMillis = getCurrentTimeMillis();
		this->currentTimeMillis = startTimeMillis;
		this->startTimeOfCurrentGenerationMillis = startTimeMillis;
		Generation generation;
		generations.push_back(generation);
		setBestFitness(0);
		//initializeGraphics();
	}

	void Simulation::addBrainOfBestFitsToCurrentGeneration() {
		std::vector<Brain> brains;
		int mostCollectedMines = 0;
		
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrSmartMineSweeper sweeper = getSweeper(i);
			
			if (sweeper->getNumberOfCollectedMines() > mostCollectedMines) {
				mostCollectedMines = sweeper->getNumberOfCollectedMines();
			}
		}
		
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrSmartMineSweeper sweeper = getSweeper(i);
			
			if (sweeper->getNumberOfCollectedMines() == mostCollectedMines) {
				brains.push_back(Brain(*sweeper->getBrain()));
			}
		}
		
		for (int unsigned i = 0; i < brains.size(); ++i) {
			getCurrentGeneration().addBrainOfBestFit(brains.operator [](i));
		}
	}
	
	void Simulation::addGeneration() {
		generations.push_back(Generation(getCurrentGeneration().getNumber() + 1));
		int unsigned nGens = generations.size();
		Generation const & previousGeneration = generations.operator [](nGens-2);
		Generation const & currentGeneration = generations.operator [](nGens-1);
		std::chrono::duration<Real> deltaTime = 
			currentGeneration.getStartTimeMillis() -
			previousGeneration.getStartTimeMillis();
		Real dt = static_cast<Real>(deltaTime.count());
		std::cout << "Real time duration of previous generation = ";
		std::cout << dt << "\n";
	}
	
	void Simulation::assignCell3DsToPhysicObject3D(SharedPtrPhysicObject3D & object) {
		bool assigned = grid->assignIntersectingCell3DsToPhysicObject3D(object);
		
		if (!assigned) {
			throw UnsupportedOperationException("PhysicObject3D not assigned any cell");
		}
	}
	
	bool Simulation::areAllSweeperMineCollisionsDetected(
		std::vector<PairOfSharedPtrPhysicObject3D> const & collidingPairs
	) const {
		bool result = true;
		std::set<PairOfSharedPtrPhysicObject3D> set1;
		
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrSmartMineSweeper sweeper = getSweeper(i);
			
			for (int unsigned j = 0; j < numberOfMines(); ++j) {
				SharedPtrMine mine = getMine(j);
				
				if (sweeper->boundingSpheresCollision(*mine)) {
					if (sweeper->boundingVolumesCollision(*mine)) {
						set1.insert(PairOfSharedPtrPhysicObject3D(sweeper, mine));
					}
				} else if (sweeper->boundingVolumesCollision(*mine)) {
					std::cout << "sweeper" << i << " = " << *sweeper << "\n";
					std::cout << "mine" << j << " = " << *mine << "\n";
					throw UnsupportedOperationException("sweeper and mine bounding volumes collide but not their bounding spheres");
				}
			}
		}
		
		if (set1.size() != collidingPairs.size()) {
			std::cout << "###Not all sweeper-mine collisions were detected\n";
			std::cout << "###set1.size() = " << set1.size() << " != ";
			std::cout << collidingPairs.size() << " = collidingPairs.size()\n";
			result = false;
		}
		
		IsSharedPtrMine isMine;
		IsSharedPtrSmartMineSweeper isSweeper;
		bool tests[4];
		
		for (int unsigned i = 0; i < collidingPairs.size(); ++i) {
			PairOfSharedPtrPhysicObject3D smPair = collidingPairs.operator [](i);
			tests[0] = isMine.test(smPair.first);
			tests[1] = isMine.test(smPair.second);
			tests[2] = isSweeper.test(smPair.first);
			tests[3] = isSweeper.test(smPair.second);
			
			/*if (!result) {
				if (tests[0]) {
					std::cout << "-*-The first object is of type Mine\n";
					std::cout << "-*-mine ID = " << smPair.first->getID() << "\n";
				}
				
				if (tests[1]) {
					std::cout << "-*-The second object is of type Mine\n";
					std::cout << "-*-mine ID = " << smPair.second->getID() << "\n";
				}
				
				if (tests[2]) {
					std::cout << "-*-The first object is of type SmartMineSweeper\n";
					std::cout << "-*-sweeper ID = " << smPair.first->getID() << "\n";
				}
				
				if (tests[3]) {
					std::cout << "-*-The second object is of type SmartMineSweeper\n";
					std::cout << "-*-sweeper ID = " << smPair.second->getID() << "\n";
				}
			}*/
			
			if ((tests[0] && tests[3]) || (tests[1] && tests[2])) {
				//std::cout << "(tests[0] && tests[3]) || (tests[1] && tests[2])\n";
				std::set<PairOfSharedPtrPhysicObject3D>::iterator it1; 
				it1 = set1.find(smPair);

				if (it1 == set1.end()) {
					std::set<PairOfSharedPtrPhysicObject3D>::iterator it2;
					it2 = set1.find(PairOfSharedPtrPhysicObject3D(smPair.second, smPair.first));
					
					if (it2 == set1.end()) {
						std::cout << "%%%Not all sweeper-mine collisions were detected\n";
						std::cout << "%%%pair" << i << " not found\n";
						
						if (tests[0]) {
							std::cout << "-*-mine ID = " << smPair.first->getID() << "\n";
							std::cout << "-*-sweeper ID = " << smPair.second->getID() << "\n";
						} else if (tests[1]) {
							std::cout << "-*-sweeper ID = " << smPair.first->getID() << "\n";
							std::cout << "-*-mine ID = " << smPair.second->getID() << "\n";
						}
						
						if (result) {
							result = false;
						}
					} else {
						
					}
				} else {
					
				}
			} else {
				throw UnsupportedOperationException("collision of objects of the same type!!!");
			}
			
		}
		
		/*std::set<PairOfSharedPtrPhysicObject3D>::iterator it;
		int counter = 0;
		//std::cout << "all the real collisions:\n";
		
		for (it = set1.begin(); it != set1.end(); ++it) {
			std::cout << "***counter = " << counter << "\n";
			PairOfSharedPtrPhysicObject3D smPair = *it;
			//std::cout << "first object = " << *smPair.first << "\n";
			//std::cout << "second object = " << *smPair.second << "\n";
			std::vector<ngn::WeakPtrCell3D> firstCells = smPair.first->getCell3Ds();
			std::vector<ngn::WeakPtrCell3D> secondCells = smPair.second->getCell3Ds();
			std::set<ngn::SharedPtrCell3D> tmpCells;
			tmpCells.insert(firstCells.begin(), firstCells.end());
			tmpCells.insert(secondCells.begin(), secondCells.end());
			std::set<ngn::SharedPtrCell3D> commonCells;
			std::set<ngn::SharedPtrCell3D>::iterator iter;
			
			for (iter = tmpCells.begin(); iter != tmpCells.end(); ++iter) {
				bool contained1 = false;
				
				for (int unsigned i = 0; i < firstCells.size(); ++i) {
					if (SharedPtrCell3D cell = firstCells[i].lock()) {
						if (cell == *iter) {
							contained1 = true;
							break;
						}
					}
				}
				
				bool contained2 = false;
				
				for (int unsigned j = 0; j < secondCells.size(); ++j) {
					if (SharedPtrCell3D cell = secondCells[j].lock()) {	
						if (cell == *iter) {
							contained2 = true;
							
							break;
						}
					}
				}
				
				bool contained = contained1 && contained2;
				
				if (contained) {
					commonCells.insert(*iter);
				}
			}
			
			//std::set<ngn::SharedPtrCell3D>::iterator iter;
			
			for (iter = commonCells.begin(); iter != commonCells.end(); ++iter) {
				SharedPtrCell3D cell = *iter;
				std::cout << "£££common cell = " << *cell << "\n";
				IsPairOfSweeperAndMine isSweeperMinePair;
				std::vector<PairOfSharedPtrPhysicObject3D> collisions;
				collisions = cell->objectsColliding(isSweeperMinePair);
				std::cout << "£££number of collisions = " << collisions.size() << "\n";
				
				for (int unsigned i = 0; i < collisions.size(); ++i) {
					std::cout << "£££first object ID = ";
					std::cout << collisions.operator [](i).first->getID() << "\n";
					std::cout << "£££second object ID = ";
					std::cout << collisions.operator [](i).second->getID() << "\n";
				}
			} 
		
			tests[0] = isMine.test(smPair.first);
			tests[1] = isMine.test(smPair.second);
			tests[2] = isSweeper.test(smPair.first);
			tests[3] = isSweeper.test(smPair.second);
			
			if (!result) {
				if (tests[0]) {
					std::cout << "***The first object is of type Mine\n";
				}
				
				if (tests[1]) {
					std::cout << "***The second object is of type Mine\n";
				}
				
				if (tests[2]) {
					std::cout << "***The first object is of type SmartMineSweeper\n";
				}
				
				if (tests[3]) {
					std::cout << "***The second object is of type SmartMineSweeper\n";
				}
				
				if (tests[0]) {
					std::cout << "***mine ID = " << smPair.first->getID() << "\n";
					std::cout << "***sweeper ID = " << smPair.second->getID() << "\n";
				} else if (tests[1]) {
					std::cout << "***sweeper ID = " << smPair.first->getID() << "\n";
					std::cout << "***mine ID = " << smPair.second->getID() << "\n";
				}
			}
			
			++counter;
		}*/
		
		return result;
	}
	
	void Simulation::checkNumberOfMinesInSpacePartition() const {
		if (totalNumberOfMinesInSpacePartition() != numberOfMines()) {
			std::cout << "Simulation::checkNumberOfMinesInSpacePartition() const"
				<<"\ntotalNumberOfMinesInSpacePartition = "
				<< totalNumberOfMinesInSpacePartition()
				<< " != " << numberOfMines() << " = numberOfMines";
		}
	}
	
	void Simulation::checkNumberOfSweepersInSpacePartition() const {
		if (totalNumberOfSweepersInSpacePartition() != numberOfSweepers()) {
			std::cout << "Simulation::checkNumberOfSweepersInSpacePartition() const"
				<<"\ntotalNumberOfSweepersInSpacePartition = "
				<< totalNumberOfSweepersInSpacePartition()
				<< " != " << numberOfSweepers() << " = numberOfSweepers";
		}
	}
	
	void Simulation::clearGrid() {
		grid->clearAllCell3Ds();
	}
	
	int Simulation::currentGenerationNumber() const {
		return getCurrentGeneration().getNumber();
	}
	
	Real Simulation::currentGenerationTime() const {
		return getCurrentGeneration().getCurrentTime();
	}
	
	Population Simulation::extractSweeperSBrains() const {
		Population brains;

		for(int unsigned i = 0; i < numberOfSweepers(); ++i) {
			brains.add(getSweeper(i)->getBrain());
		}

		return brains;
	}

	SharedPtrSmartMineSweeper Simulation::findBestSweeper() const {
		if (!sweepers->empty()) {
			SharedPtrSmartMineSweeper sweeper;
			Real maximumFitness;
			
			if (getBestSweeper() != nullptr) {
				sweeper = getBestSweeper();
				maximumFitness = getBestFitness();
			} else {
				sweeper = getSweeper(0);
				maximumFitness = sweeper->fitness();
			}
			
			for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
				if (getSweeper(i)->fitness() > maximumFitness) {
					sweeper = getSweeper(i);
					maximumFitness = sweeper->fitness();
				}
			}
			
			return sweeper;
		} else {
			return nullptr;
		}
	}

	SharedPtrMine Simulation::findClosestMineToSweeper(SharedPtrSmartMineSweeper const & sweeper) const {
		if (sweeper == 0) {
			std::string message = "pointer to sweeper is null";
			std::cout << "message = " << message << std::endl;
			throw IllegalArgumentException(message);
		}
		
		//std::shared_ptr<PredicateOfSharedPtrPhysicObject3D> predicate;
		//predicate = std::shared_ptr<IsSharedPtrMine>(new IsSharedPtrMine());
		Grid3D::SearchResult result = grid->closestNeighbor(sweeper, *isSharedMine);
		SharedPtrPhysicObject3D object = result.getClosestNeighbor();
		
		if (object != 0) {
			if (isSharedMine->test(object)) {
				return std::dynamic_pointer_cast<Mine>(object);
			} else {
				std::cout << "object = " << object << std::endl;
				throw UnsupportedOperationException(
					"object is not of class Mine as required by predicate"
				);
			}
		} else {
			std::cout << "object is null " << std::endl;
			std::cout << "sweeper = " << *sweeper << "\n";
			throw UnsupportedOperationException(
				"object is null therefore not of class Mine as required by predicate"
			);
		}
	}

	SharedPtrFunction Simulation::getActivationFunction() {
		return parameters.getActivationFunction();
	}

	SharedPtrSmartMineSweeper const & Simulation::getBestSweeper() const {
		return bestSweeper;
	}

	RGBColor Simulation::getColorOfMinelessSweeper() {
		return colorOfMinelessSweeper;
	}

	RGBColor Simulation::getColorOfBestSweeper() {
		return colorOfBestSweeper;
	}

	RGBColor Simulation::getDefaultColorOfSweeper() {
		return defaultColorOfSweeper;
	}

	Simulation::Generation const & Simulation::getCurrentGeneration() const {
		return generations.operator [](generations.size() - 1);
	}
	
	Simulation::Generation & Simulation::getCurrentGeneration() {
		return generations.operator [](generations.size() - 1);
	}
	
	Real Simulation::getFrameTime() const {
		return frameTime;
	}

	int Simulation::getGenerationDurationInSeconds() {
		return parameters.getGenerationDurationInSeconds();
	}

	long Simulation::getInitialClosestMineUpdateDelay() {
		return 0;
	}

	long Simulation::getClosestMineUpdatePeriod() {
		return 1000 / (long) parameters.getPhysicsUpdateRate();
	}

	SharedPtrMine const & Simulation::getMine(int i) const {
		return mines->operator[](i);
	}

	SharedPtrMine & Simulation::getMine(int i) {
		return mines->operator[](i);
	}
	
	int Simulation::getNumberOfGenerationsOffline() const {
		return parameters.getNumberOfGenerationsOffline();
	}

	Parameters Simulation::getParameters() const {
		return parameters;
	}

	std::chrono::time_point<std::chrono::system_clock> const & 
	Simulation::getStartTimeOfCurrentGenerationMillis() const {
		return startTimeOfCurrentGenerationMillis;
	}

	bool Simulation::isOnLine() const {
		return onLine;
	}
	
	void Simulation::incrementCurrentGenerationTime(Real deltaTime) {
		getCurrentGeneration().incrementTime(deltaTime);
	}
	
	/*void Simulation::launchPhysicsThread() {
		physicsThread = std::thread(&Simulation::physicsThreadFunction, this);
		physicsThread.join();
	}*/

	/*void Simulation::launchGraphicsThread() {
		graphics.start();
		graphicsThread = std::thread(&Simulation::graphicsThreadFunction, this);
		graphicsThread.join();
	}*/

	void Simulation::func() {
		if (isOnLine()) {
			//std::cout << "...running online...\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMillis));
		}
		
		findClosestMinesToSweepers();
		steerSweepersToClosestMines();
		Real dt = elapsedTime();
		//std::cout << "dt = " << dt << "\n";
		incrementCurrentGenerationTime(dt);
		updateSweepersPositions(dt);
		updateCollectedMines();
		updateSweepersColors();
		relocateOutOfBoundsSweepers();
		updateBlockOfSweepers();
		checkNumberOfMinesInSpacePartition();
		checkNumberOfSweepersInSpacePartition();

		Real generationTime = currentGenerationTime();
		bool isNewGeneration = false;
		
		if (generationTime >= parameters.getGenerationDurationInSeconds()) {
			isNewGeneration = true;
			std::cout << "currentGenerationNumber = " << getCurrentGeneration().getNumber() << "\n"; 
			std::cout << "generationTime = " << generationTime << "\n";
			addCurrentStatistics();
			std::cout << "stats =\n" << statistics.operator[](statistics.size() - 1) << "\n";
			std::vector<Population> brains = evolveBrains();
			replaceSweepersBrains(brains);
			resetSweepersNumberOfCollectedMines();
			setBestSweeper(nullptr);
			setBestFitness(0);
			resetSweepersColors(getColorOfMinelessSweeper());

			if (shouldSweepersAndMinesPositionBeReset()) {
				std::cout << "####MINES AND SWEEPERS REPOSITIONED!!!\n";
				clearGrid();
				resetSweepersPosition();
				resetMinesPosition();
			}

			checkNumberOfMinesInSpacePartition();
			checkNumberOfSweepersInSpacePartition();
			std::cout << "end of generation " << currentGenerationNumber() << "\n";
			addBrainOfBestFitsToCurrentGeneration();
			addGeneration();
		}
		
		if (!areObjectsValid()) {
			std::cout << "Is new generation ? " << (isNewGeneration ? "true": "false") << "\n";
			throw UnsupportedOperationException("There is at least a non valid object");
		}
	}
	
	void Simulation::func2(Real dt) {
		findClosestMinesToSweepers();
		steerSweepersToClosestMines();
		incrementCurrentGenerationTime(dt);
		updateSweepersPositions(dt);
		updateCollectedMines();
		updateSweepersColors();
		relocateOutOfBoundsSweepers();
		updateBlockOfSweepers();
		checkNumberOfMinesInSpacePartition();
		checkNumberOfSweepersInSpacePartition();

		Real generationTime = currentGenerationTime();
		bool isNewGeneration = false;
		
		if (generationTime >= parameters.getGenerationDurationInSeconds()) {
			isNewGeneration = true;
			std::cout << "currentGenerationNumber = " << getCurrentGeneration().getNumber() << "\n"; 
			std::cout << "generationTime = " << generationTime << "\n";
			addCurrentStatistics();
			std::cout << "stats =\n" << statistics.operator[](statistics.size() - 1) << "\n";
			std::vector<Population> brains = evolveBrains();
			replaceSweepersBrains(brains);
			resetSweepersNumberOfCollectedMines();
			setBestSweeper(nullptr);
			setBestFitness(0);
			resetSweepersColors(getColorOfMinelessSweeper());

			if (shouldSweepersAndMinesPositionBeReset()) {
				std::cout << "####MINES AND SWEEPERS REPOSITIONED!!!\n";
				clearGrid();
				resetSweepersPosition();
				resetMinesPosition();
			}

			checkNumberOfMinesInSpacePartition();
			checkNumberOfSweepersInSpacePartition();
			std::cout << "end of generation " << currentGenerationNumber() << "\n";
			addBrainOfBestFitsToCurrentGeneration();
			addGeneration();
		}
		
		if (!areObjectsValid()) {
			std::cout << "Is new generation ? " << (isNewGeneration ? "true": "false") << "\n";
			throw UnsupportedOperationException("There is at least a non valid object");
		}
	}
	
	void Simulation::printStats(std::ostream & out) {
		for (int unsigned i = 0; i < statistics.size(); ++i) {
			std::cout << i << ": ";
			statistics.operator[](i).print(out);
			out << "\n";
		}
	}

	void Simulation::replaceSweepersBrains(std::vector<Population> const & populations) {
		if (populations.size() >= 1) {
			std::shared_ptr<std::vector<SharedPtrChromosome>> chrs;
			chrs = populations.operator[](0).toArrayList();
			std::vector<SharedPtrBrain> brains = convertChromosomesIntoBrains(*chrs);

			for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
				SharedPtrSmartMineSweeper sweeper = getSweeper(i);

				if (sweeper->fitness() < getBestFitness()) {
					sweeper->setBrain(brains.operator[](i));
				} else {
					SharedPtrChromosome brainCopy = sweeper->getBrain()->copy();
					sweeper->setBrain(brainCopy);
				}
			}
		} else {
			throw UnsupportedOperationException("");
		}
	}

	void Simulation::copy(Simulation sim) {
		parameters = sim.parameters;
		sweepers = sim.sweepers;
		bestSweeper = sim.bestSweeper;
		mines = sim.mines;
		GASettings = sim.GASettings;
		currentTimeMillis = sim.currentTimeMillis;
		bestFitness = sim.bestFitness;
		statistics = sim.statistics;
	}

	Vector3D Simulation::randomMinePosition() const {
		Vector3D position = grid->randomPosition();
		position.setZ(grid->getOrigin().getZ() + parameters.getMineRadius());
		
		return position;
	}
	
	Vector3D Simulation::randomSweeperPosition() const {
		Vector3D position = grid->randomPosition();
		position.setZ(grid->getOrigin().getZ() + parameters.getSweeperHeight() / 2.0);
		
		return position;
	}

	void Simulation::writeSweepersInFile(std::string filePath) {
		/*PrintWriter printWriter;

		try {
			printWriter = new PrintWriter(filePath + "." + LocalDateTime.now(), "UTF-8");

			for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
				printWriter.println("i = " + i);
				printWriter.println(getSweeper(i)->toString());
			}

			printWriter.close();
		} catch (IOException e) {
			std::cout << "An error occurred.");
			std::cout << e.getMessage());
		}*/
	}

	void Simulation::writeBestSweeperInFile(std::string filePath) {
		/*PrintWriter printWriter;

		try {
			printWriter = new PrintWriter(filePath, "UTF-8");

			if (getBestSweeper() != nullptr) {
				printWriter.println(getBestSweeper().toString());
			}

			printWriter.close();
		} catch (IOException e) {
			std::cout << "An error occurred.");
			std::cout << e.getMessage());
		}*/
	}

	void Simulation::setBestSweeper(SharedPtrSmartMineSweeper const & sweeper) {
		bestSweeper = sweeper;
	}

	void Simulation::setBrainEvolver(SharedPtrBrainEvolver const & param) {
		if (param == nullptr) {
			throw IllegalArgumentException("param is nullptr");
		}
		
		brainEvolver = param;
	}
	
	void Simulation::setOnLine(bool isOnLine) {
		onLine = isOnLine;
	}
	
	void Simulation::setPositionOfMine(int i, Vector3D position) {
		getMine(i)->setPosition(position);
	}

	void Simulation::setBestFitness(Real value) {
		bestFitness = value;
	}

	void Simulation::steerSweepersToClosestMines() {
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			getSweeper(i)->steerToClosestMine(steeringFunction);
		}
	}
	
	void Simulation::print(std::ostream & out) const {
		out << "Simulation{"
				<< "\nparameters=" << parameters
				//<< ", \nsweepers=" << sweepers
				<< ", \nbestSweeper=" << bestSweeper
				//<< ", \nmines=" << mines
				<< ", \nGASettings=" << GASettings
				//<< ", \nworld=" << world
				//<< ", \ncurrentTimeMillis=" << currentTimeMillis
				<< ", \nmostCollectedMines=" << bestFitness
				//<< ", \nstatistics=" << statistics
				//<< ", \ncurrentGenerationNumber=" << currentGenerationNumber
				<< ", \ncolorOfMinelessSweeper=" << colorOfMinelessSweeper
				<< ", \ncolorOfBestSweeper=" << colorOfBestSweeper
				<< ", \ndefaultColorOfSweeper=" << defaultColorOfSweeper
				<< '}';
	}

	void Simulation::updateSweepersPositions(Real elapsedTime) {
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			getSweeper(i)->update(elapsedTime);
		}
	}

	void Simulation::writeResultsInFile(std::string filePath) {
	}

	void Simulation::main(/*String[] args*/) /*throws FileNotFoundException*/ {
		//test();
		util::Rand<Real>::getInstance().setSeed(-1);
		util::Rand<int>::getInstance().setSeed(-1);
		std::string parametersFilePath = "/home/john/Documents/Programming/SmartSweepersV2/params.ini";
		Parameters parameters(parametersFilePath);
		SharedPtrSteeringFunction steering;
		steering = std::make_shared<DefaultSteeringFunction>();
		Simulation simulation(parameters, steering);
		std::cout << "parameters =\n" << parameters << "\n";
		//simulation.start();
	}

	void Simulation::test() /*throws FileNotFoundException*/ {
		std::string parametersFilePath = "/home/john/Documents/SmartSweepersV2/params_example.ini";
		Parameters parameters(parametersFilePath);
		Settings GASettings = readGASettingsFromFilePath(parameters.getGASettingsFilePath());

		if (GASettings.getPopulationSize() != parameters.getNumberOfSweepers()) {
			std::string message = "population size in ";
			message += "Genetic Algorithm solver doesn't match the number of ";
			message += "sweepers\n";
			throw IllegalArgumentException(message);
		}

		Grid3D spacePartition = 
			spacePartitionFromOriginExtentsPartitions(
				parameters.getWorldOrigin(),
				parameters.getWorldExtents(),
				Partitions(
					parameters.getNumberOfRowsOfSpacePartition(),
					parameters.getNumberOfColumnsOfSpacePartition(),
					1
				)
			);

		Vector3D minePosition = spacePartition.randomPosition();
		SharedPtrIntersectable volume(new ngn::Sphere(minePosition, 20));
		SharedPtrMine mine(new Mine(minePosition, volume));

		class MySweeper: public SmartMineSweeper {
		public:
			MySweeper(SharedPtrBrain brain, SharedPtrMobile car, SharedPtrMine closestMine) :
				SmartMineSweeper(brain, car, closestMine/*, ngn::Sphere(car->getPosition(), (ngn::Real)1.0)*/),
				sphere(Vector3D(car->getPosition()), 1.0)
			{
			}

			void steerToClosestMine() {
				if (getClosestMine() != nullptr) {
					computeAndSetClosestMineDirection();
					Real angle = Math<Real>::acos(getClosestMineDirection()->dot(Vector3D::x_axis()) / getClosestMineDirection()->length());
					getVehicle()->setAngle(angle);
				}
			}
			
			ngn::Sphere const & getBoundingSphere() const {
				return sphere;
			}
			
			bool isMovable() const {
				return true;
			}
			
			void setBoundingSphere(ngn::Sphere const & sphere) {
				
			}
			
			void setMovable(bool movable) {
				
			}
			
		private:
			ngn::Sphere sphere;
		};

		int nInputs = parameters.getNumberOfInputs();
		std::vector<int> nNeuronsbyLayer = parameters.getNumberOfNeuronsByNeuralNetworkLayer();
		SharedPtrFunction function = parameters.getActivationFunction();
		Real minimumWeight = -1.0;
		Real maximumWeight = 1.0;
		Range weightRange(minimumWeight, maximumWeight);
		std::vector<std::shared_ptr<std::vector<ngn::SharedPtrFunction>>> functions;
		
		for (int unsigned i = 0; i < nNeuronsbyLayer.size(); ++i) {
			std::shared_ptr<std::vector<ngn::SharedPtrFunction>> layerFunctions;
			layerFunctions = std::make_shared<std::vector<ngn::SharedPtrFunction>>();
			int nNeurons = nNeuronsbyLayer.operator [](i);
			
			for (int j = 0; j < nNeurons; ++j) {
				layerFunctions->push_back(function);
			}
			
			functions.push_back(layerFunctions);
		}
		
		NeuralNetwork cnn = NeuralNetwork::random(nInputs, nNeuronsbyLayer, weightRange, functions);
		int numberOfCollectedMines = 0;
		SharedPtrBrain brain(new Brain(cnn, numberOfCollectedMines));

		Vector3D sweeperPosition = spacePartition.randomPosition();//new Vector3D(125, 125);
		Vector3D dist = Vector3D::sub(minePosition, sweeperPosition);
		Real angle = Math<Real>::acos(dist.dot(Vector3D::x_axis()) / dist.length());//dist.angle();
		Real leftTrack = 40.0;
		Real rightTrack = 40.0;
		Real maximumTrackSpeed = leftTrack + rightTrack;
		Real maximumTurnRate = 0.0;
		Real halfWheelBase = 10.0;
		Real halfWidth = 7.0;
		Real halfHeight = 1.5;
		sweeperPosition.setZ(halfHeight);
		Vector3D extents(halfWheelBase, halfWidth, halfHeight);
		Matrix3D orientation = Matrix3D::fromAxisAngle(AxisAngle(Vector3D::z_axis(), angle));
		SharedPtrIntersectable boundingVolume = 
			std::make_shared<OrientedBox3D>(
				sweeperPosition,
				orientation,
				extents
			);
		Real radius = Math<Real>::sqrt(halfWheelBase * halfWheelBase + halfWidth * halfWidth + halfHeight * halfHeight);
		ngn::Sphere boundingSphere(sweeperPosition, radius);
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

		SharedPtrSmartMineSweeper sweeper(new MySweeper(brain, tank, mine));
		SharedArrayOfSharedSweepers sweepers;
		sweepers->push_back(sweeper);

		SharedArrayOfSharedMines mines;
		mines->push_back(mine);
		int nMines = 1;

		for (int i = 1; i < nMines; ++i) {
			minePosition = spacePartition.randomPosition();
			mines->push_back(
				SharedPtrMine(
					new Mine(
						minePosition, 
						SharedPtrIntersectable(
							new ngn::Sphere(minePosition, 20)
						)
					)
				)
			);//new Mine(new Vector3D(140, 140)));
			//minePosition = world.randomMinePosition();
			//mines->push_back(new Mine(minePosition, new ngn::Sphere(minePosition, 20)));//new Vector3D(120, 150)));
		}

		SharedPtrSteeringFunction steering = std::make_shared<DefaultSteeringFunction>();
		Simulation simulation(
				parameters,
				GASettings,
				spacePartition,
				sweepers,
				mines,
				steering
		);

		//simulation.start();
	}
		
	Grid3D Simulation::spacePartitionFromOriginExtentsPartitions(
			Vector3D const & worldOrigin,
			Vector3D const & worldExtents,
			Partitions const & partitions
	) {
		return Grid3D::fromOriginExtentsPartitions(
				worldOrigin,
				worldExtents,
				partitions
		);
	}
	
	void Simulation::addAllMinesToSpacePartition() {
		std::vector<SharedPtrPhysicObject3D> objects;
		
		for (int unsigned i = 0; i < numberOfMines(); ++i) {
			objects.push_back(getMine(i));
		}
		
		std::pair<bool, std::set<int unsigned>> result;
		result = grid->assignIntersectingCell3DsToArrayOfPhysicObject3Ds(objects);
		
		if (!result.first) {
			std::cout << "some mines were not added to the grid !\n";
			std::cout << "These are:\n";
			std::set<int unsigned>::const_iterator it;
			
			for (it = result.second.begin(); it != result.second.end(); ++it) {
				std::cout << "mine" << *it << "\n";
			} 
			
			throw UnsupportedOperationException("Some mines were not added");
		}
	}

	void Simulation::addAllSweepersToSpacePartition() {
		std::vector<SharedPtrPhysicObject3D> objects;
		
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			objects.push_back(getSweeper(i));
		}
		
		std::pair<bool, std::set<int unsigned>> result;
		result = grid->assignIntersectingCell3DsToArrayOfPhysicObject3Ds(objects);
		
		if (!result.first) {
			std::cout << "some sweepers were not added to the grid !\n";
			std::cout << "These are:\n";
			std::set<int unsigned>::const_iterator it;
			
			for (it = result.second.begin(); it != result.second.end(); ++it) {
				std::cout << "sweeper" << *it << "\n";
			} 
			
			throw UnsupportedOperationException("Some sweepers were not added");
		}
	}
	
	void Simulation::addCurrentStatistics() {
		//std::cout << "getBestFitness() = " << getBestFitness() << "\n";
		Real averageFitness = Simulation::averageFitness();
		std::shared_ptr<int> sweeperID
				= getBestSweeper() != nullptr
						? std::shared_ptr<int>(new int(getBestSweeper()->getID()))
						: nullptr;

		statistics.push_back(
				Statistics(
					getBestFitness(),
					averageFitness,
					fitnessStandardDeviation(averageFitness),
					pourcentageOfMinelessSweepers(),
					totalNumberOfCollectedMines(),
					sweeperID
				)
		);
	}

	bool Simulation::areObjectsValid() const {
		bool result = true;
		
		for (int unsigned i = 0; i < numberOfMines(); ++i) {
			SharedPtrPhysicObject3D object = getMine(i);
			
			if (!isObjectValid(object)) {
				std::cout << "mine" << i << " not valid\n";
				
				if (result) {
					result = false;
					
					return result;
				}
			}
		}
		
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrPhysicObject3D object = getSweeper(i);
			
			if (!isObjectValid(object)) {
				std::cout << "sweeper" << i << " not valid\n";
				
				if (result) {
					result = false;
					
					return result;
				}
			}
		}
		
		return result;
	}
	
	bool Simulation::isObjectValid(SharedPtrPhysicObject3D const & object) const {
		std::vector<SharedPtrCell3D> intersectingCells; 
		intersectingCells = grid->findCell3DsIntersectingPhysicObject3D(object);
		std::vector<WeakPtrCell3D> objectCells;
		objectCells = object->getCell3Ds();
		std::set<SharedPtrCell3D> tmpCells_1;
		std::set<SharedPtrCell3D> tmpCells_2;
		
		for (int unsigned i = 0; i < intersectingCells.size(); ++i) {
			//std::cout << "+i = " << i << "\n";
			tmpCells_1.insert(intersectingCells.operator [](i));
		}
		
		for (int unsigned i = 0; i < objectCells.size(); ++i) {
			//std::cout << "++i = " << i << "\n";
			if (SharedPtrCell3D cell = objectCells.operator [](i).lock()) {
				tmpCells_2.insert(cell);
			}
		}
		
		if (tmpCells_1 != tmpCells_2) {
			return false;
		}
		
		for (int unsigned i = 0; i < intersectingCells.size(); ++i) {
			//std::cout << "+++i = " << i << "\n";
			SharedPtrCell3D cell = intersectingCells.operator [](i);
			
			if (cell == nullptr) {
				throw UnsupportedOperationException("cell ptr is null");
			}
			
			if (!cell->contains(object)) {
				return false;
			}
		}
		
		return true;
	}
	
	bool Simulation::areSweepersValid() const {
		int count = 0;

		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrSmartMineSweeper sweeper = getSweeper(i);

			if (sweeper == nullptr) {
				++count;
			} else if (!isSweeperInsideGrid(*sweeper)) {
				++count;
			}

			for (int unsigned j = i + 1; j < numberOfSweepers(); ++j) {
				if (sweeper != nullptr && getSweeper(j) != nullptr) {
					if (sweeper == getSweeper(j)) {
						return false;
					}
				}
			}
		}

		return count == 0;
	}
	
	Real Simulation::averageFitness() const {
		Real res = 0;
		int count = 0;

		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrSmartMineSweeper sweeper = getSweeper(i);

			if (sweeper != nullptr) {
				res += sweeper->fitness();
				count += 1;
			} else {
				throw UnsupportedOperationException("SWEEPER NULL IN AVERAGE FITNESS FUNCTION");
			}
		}

		if (count != 0) {
			res /= count;
		} else {
			throw UnsupportedOperationException("COUNT OF SWEEPERS IS EQUAL TO ZERO IN AVERAGE FITNESS FUNCTION");
		}

		return res;
	}
	
	std::vector<SharedPtrBrain> 
	Simulation::convertChromosomesIntoBrains(std::vector<SharedPtrChromosome> const & chrs) {
		std::vector<SharedPtrBrain> brains;

		for (int unsigned i = 0; i < chrs.size(); ++i) {
			SharedPtrBrain brain = convertChromosomeIntoBrain(chrs.operator[](i));
			brains.push_back(brain);
		}

		return brains;
	}
	
	SharedPtrBrain 
	Simulation::convertChromosomeIntoBrain(SharedPtrChromosome const & chr) {
		SharedPtrBrain brain = std::dynamic_pointer_cast<Brain>(chr);
		
		if (brain == nullptr) {
			throw UnsupportedOperationException("Chromosome not converted into brain");
		}
		
		return brain;
	}
	
	Real Simulation::squaredDistanceBetweenSweeperAndMine(
		SharedPtrSmartMineSweeper const & sweeper, 
		SharedPtrMine const & mine
	) const {
		Vector3D pos1 = sweeper->getPosition();
		Vector3D pos2 = mine->getPosition();
		Real squaredDistance = Vector3D::squaredDistanceFrom(pos1, pos2);
			
		return squaredDistance;
	}
		
	Real Simulation::elapsedTime() {
		if (isOnLine()) {
			std::chrono::time_point<std::chrono::system_clock> previousTimeMillis = currentTimeMillis;
			currentTimeMillis = std::chrono::system_clock::now();
			std::chrono::duration<Real> res = currentTimeMillis - previousTimeMillis;
			
			return static_cast<Real>(res.count());
		} else {
			return frameTime;
		}
	}

	Real Simulation::elapsedTime(
		std::chrono::time_point<std::chrono::system_clock> begin,
		std::chrono::time_point<std::chrono::system_clock> end
	) const {
		std::chrono::duration<Real> res = end - begin;
		
		return static_cast<Real>(res.count());
	}
	
	std::vector<Population> Simulation::evolveBrains() {
		std::vector<Population> populations;
		populations.push_back(extractSweeperSBrains());
		std::vector<Population> result = brainEvolver->evolveBrains(populations);

		return result;
	}

	void Simulation::findClosestMinesToSweepers() const {
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			//std::cout << "##########sweeper_" << i << std::endl;
			SharedPtrSmartMineSweeper const & sweeper = getSweeper(i);
			SharedPtrMine closestMine = findClosestMineToSweeper(sweeper);
			
			//if (closestMine == nullptr) {
				//std::string message = "UnsupportedOperationException():\n";
				//message += "Simulation::findClosestMinesToSweepers() const:\n";
				//message += "closestMine == nullptr\n";
				//throw UnsupportedOperationException("message");
			//}
			
			sweeper->setClosestMine(closestMine);
			//std::pair<bool, SharedPtrMine> res = isMineClosestToSweeper(closestMine, sweeper);
			
			//if(!res.first) {
				//throw NotClosestObjectException(sweeper, closestMine, res.second, getCurrentGenerationNumber());
			//}
		}
	}

	Real Simulation::fitnessStandardDeviation(Real averageFitness) const {
		Real squareSum = 0.0;

		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			Real fitness = getSweeper(i)->fitness();
			squareSum += Math<Real>::pow(fitness, 2.0);
		}

		Real squareAverage = squareSum / numberOfSweepers();
		Real res = Math<Real>::sqrt(squareAverage - Math<Real>::pow(averageFitness, 2.0));

		return res;
	}
	
	std::string Simulation::formatElapsedTime(Real elapsedTime) const {
		int p1 = (int) elapsedTime % 60;
		int p2 = (int) elapsedTime / 60;
		int p3 = p2 % 60;
		int p4 = p2 / 60;
		std::string sp1 = std::to_string(p1);
		std::string sp3 = std::to_string(p3);
		std::string sp4 = std::to_string(p4);
		
		std::string time = (p4 >= 10 ? sp4 : "0" + sp4) + "h"
				+ (p3 >= 10 ? sp3 : "0" + sp3) + "'"
				+ (p1 >= 10 ? sp1 : "0" + sp1);

		return time;
	}
	
	Real Simulation::getMinimumDistanceBetweenMines() const {
		return parameters.getMinimumDistanceBetweenMines();
	}

	Real Simulation::getMinimumDistanceBetweenSweepers() const {
		return parameters.getMinimumDistanceBetweenSweepers();
	}

	int Simulation::getNumberOfGenerationsRealTime() const {
		return parameters.getNumberOfGenerationsOnline();
	}
	
	Real Simulation::getPhysicsUpdateRate() const {
		return parameters.getPhysicsUpdateRate();
	}

	int Simulation::getSleepTimeMillis() const {
		return sleepTimeMillis;
	}
	
	SharedPtrSmartMineSweeper Simulation::getSweeper(int i) const {
		return sweepers->operator[](i);
	}

	Real Simulation::getBestFitness() const {
		if (getBestSweeper() != nullptr) {
			return getBestSweeper()->fitness();
		} else {
			return 0;
		}
	}

	int Simulation::indexOfMine(SharedPtrMine const & mine) const {
		for (int unsigned i = 0; i < mines->size(); ++i) {
			if (getMine(i) == mine) {
				return static_cast<int>(i);
			}
		}
		
		return mines->size();
	}
	
	std::pair<bool, SharedPtrMine> 
	Simulation::isMineClosestToSweeper(
		SharedPtrMine const & mine, 
		SharedPtrSmartMineSweeper const & sweeper
	) const {
		Real minimimSquaredDistance = std::numeric_limits<Real>::max();
		SharedPtrMine closestMine = nullptr;

		for (int unsigned i = 0; i < numberOfMines(); ++i) {
			Real squaredDistance = 
				squaredDistanceBetweenSweeperAndMine(
					sweeper, 
					getMine(i)
				);

			if (squaredDistance < minimimSquaredDistance) {
				minimimSquaredDistance = squaredDistance;
				closestMine = getMine(i);
			}
		}
		//it may happen that two different mines are located at the same distance from sweeper
		if (closestMine != mine) {
			Real squaredDistance = 
				squaredDistanceBetweenSweeperAndMine(
					sweeper, 
					mine
				);
			Real diff = squaredDistance - minimimSquaredDistance;
			Real const EPS = 1.0e-3;
			
			if (Math<Real>::abs(diff) <= EPS) {
				return std::make_pair(true, closestMine);
			} else {
				return std::make_pair(false, closestMine);
			}
		}
		
		return std::make_pair(true, closestMine);
	}
	
	bool Simulation::isSweeperInsideGrid(SmartMineSweeper const & sweeper) const {
		return grid->containsPosition(sweeper.getPosition());
	}

	int unsigned Simulation::numberOfMines() const {
		return mines->size();
	}

	int unsigned Simulation::numberOfSweepers() const {
		return sweepers->size();
	}

	Real Simulation::pourcentageOfMinelessSweepers() const {
		int count = 0;

		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrSmartMineSweeper sweeper = getSweeper(i);

			if (sweeper != nullptr) {
				if (sweeper->numberOfCollectedMines() == 0) {
					count += 1;
				}
			}
		}

		return 100.0 * (Real) count / (Real) numberOfSweepers();
	}

	Settings Simulation::readGASettingsFromFilePath(std::string filePath) {
		Settings settings(filePath);

		return settings;
	}

	void Simulation::relocateOutOfBoundsSweepers() {
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrPhysicObject3D object = getSweeper(i);
			grid->relocateOutOfBoundsPhysicObject3D(object);
		}
	}
	
	template <class PhysicObjectType>
	void Simulation::setPositionOfPhysicObject3D(SharedPtrPhysicObject3D & object) {
		Vector3D position = sweepersAndMinesGenerator.randomPosition<PhysicObjectType>();
		object->setPosition(position);
		assignCell3DsToPhysicObject3D(object);
		/*bool setInEmptySpace =
			sweepersAndMinesGenerator.setObjectInEmptySpace<PhysicObjectType>(object);
			
		if (!setInEmptySpace) {
			std::cout << "PhysicObject3D not set in an empty space!\n";
		}*/
		
		bool succeed = 
			sweepersAndMinesGenerator.setObjectAtDistanceFromOthers<PhysicObjectType>(object);
		
		if (!succeed) {
			std::cout << "PhysicObject3D not set sufficiently away from others of the same type!\n";
		}
	}
	
	void Simulation::setPositionOfMineRandomly(SharedPtrMine & mine) {
		SharedPtrPhysicObject3D object = mine;
		setPositionOfPhysicObject3D<Mine>(object);
	}
	
	void Simulation::setPositionOfMinesRandomly() {
		for (int unsigned i = 0; i < numberOfMines(); ++i) {
			setPositionOfMineRandomly(getMine(i));
		}
	}

	void Simulation::resetMinesPosition() {
		setPositionOfMinesRandomly();
	}

	void Simulation::resetSweepersColors(RGBColor const & color) {
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			getSweeper(i)->setColor(color);
		}
	}

	void Simulation::resetSweepersNumberOfCollectedMines() {
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			getSweeper(i)->setNumberOfCollectedMines(0);
		}
	}

	void Simulation::resetSweepersPosition() {
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrPhysicObject3D object = getSweeper(i);
			setPositionOfPhysicObject3D<SmartMineSweeper>(object);
		}
	}

	void Simulation::setStartTimeOfCurrentGenerationMillis(
		std::chrono::time_point<std::chrono::system_clock> const & timeMillis
	) {
		startTimeOfCurrentGenerationMillis = timeMillis;
	}
	
	bool Simulation::shouldSweepersAndMinesPositionBeReset() {
		int nGen = parameters.getNumberOfGenerationsBeforePositionReset();
		bool test = (currentGenerationNumber() % nGen == (nGen - 1));
				
		return test;
	}

	std::pair<SharedPtrSmartMineSweeper, SharedPtrMine> 
	Simulation::sweeperAndMineFromPhysicObjectPair(
			PairOfSharedPtrPhysicObject3D const & objectPair
	) const {
		SharedPtrPhysicObject3D object1 = objectPair.first;
		SharedPtrPhysicObject3D object2 = objectPair.second;
		SharedPtrMine mine = std::dynamic_pointer_cast<Mine>(object1);
		
		if (mine != nullptr) {
			SharedPtrSmartMineSweeper sweeper = std::dynamic_pointer_cast<SmartMineSweeper>(object2);
			
			if (sweeper != nullptr) {
				return std::make_pair(sweeper, mine);
			} else {
				throw UnsupportedOperationException(
					"objectPair.first is a pointer to a Mine && objectPair.second is not a pointer to a SmartMineSweeper"
				);
			}
		} else {
			mine = std::dynamic_pointer_cast<Mine>(object2);
			
			if (mine != nullptr) {
				SharedPtrSmartMineSweeper sweeper = std::dynamic_pointer_cast<SmartMineSweeper>(object1);
				
				if (sweeper != nullptr) {
					return std::make_pair(sweeper, mine);
				} else {
					throw UnsupportedOperationException(
						"objectPair.second is a pointer to a Mine && objectPair.first is not a pointer to a SmartMineSweeper"
					);
				}
			} else {
				throw UnsupportedOperationException(
					"objectPair.first is not a pointer to a Mine && objectPair.second is not a pointer to a Mine"
				);
			}
		}
	}

	int unsigned Simulation::totalNumberOfCollectedMines() const {
		int res = 0;

		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			res += getSweeper(i)->numberOfCollectedMines();
		}

		return res;
	}

	int unsigned Simulation::totalNumberOfMinesInSpacePartition() const {
		std::shared_ptr<PredicateOfSharedPtrPhysicObject3D> predicate(new IsSharedPtrMine());
		return grid->numberOfPhysicObject3D(*predicate);
	}

	int unsigned Simulation::totalNumberOfSweepersInSpacePartition() const {
		std::shared_ptr<PredicateOfSharedPtrPhysicObject3D> predicate(new IsSharedPtrSmartMineSweeper());
		return grid->numberOfPhysicObject3D(*predicate);
	}

	void Simulation::updateBlockOfSweepers() {
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrPhysicObject3D sweeper = getSweeper(i);
			bool assigned = grid->assignIntersectingCell3DsToPhysicObject3D(sweeper);
			
			if (!assigned) {
				//std::cout << "current generation = " << getCurrentGenerationNumber() << "\n";
				std::cout << "elapsed time = " << elapsedTime() << "\n";
				std::cout << "sweeper_" << i << " is out of the grid\n";
				std::cout << "sweeper's position = " << sweeper->getPosition() << "\n";
				throw new UnsupportedOperationException("Update of cell of sweeper failed !");
			}
		}
	}

	void Simulation::updateCollectedMines() {
		std::set<SharedPtrMine> collectedMines;
		std::vector<PairOfSharedPtrPhysicObject3D> collidingPairs;
		std::shared_ptr<PredicateOfPairOfSharedPtrPhysicObject3D> predicate(
			new IsPairOfSweeperAndMine()
		);
		collidingPairs = grid->objectsCollidingAndVerifyingPredicate(*predicate);
		//std::cout << "number of collisions = " << collidingPairs.size() << "\n";
		//bool test = areAllSweeperMineCollisionsDetected(collidingPairs);
		
		//if (!test) {
			//throw UnsupportedOperationException("Some collisions are missing!");
		//}

		for (int unsigned i = 0; i < collidingPairs.size(); ++i) {
			PairOfSharedPtrPhysicObject3D objectPair = collidingPairs.operator[](i);
			std::pair<SharedPtrSmartMineSweeper, SharedPtrMine> pair = sweeperAndMineFromPhysicObjectPair(objectPair);
			SharedPtrMine mine = pair.second;
			SharedPtrSmartMineSweeper sweeper = pair.first;
			bool isMineFoundInCollectedMines; 
			isMineFoundInCollectedMines = (collectedMines.find(mine) != collectedMines.end());

			if (!isMineFoundInCollectedMines) {
				bool isMineInsertedInCollectedMines;
				isMineInsertedInCollectedMines = collectedMines.insert(mine).second;
				
				if (!isMineInsertedInCollectedMines) {
					throw UnsupportedOperationException("Mine has not been inserted in the set of collected mines");
				}
				
				//std::cout << "sweeper->getNumberOFCollectedMines() = ";
				sweeper->incrementNumberCollectedMines(1);
				//std::cout << sweeper->getNumberOfCollectedMines() << "\n";

				if (sweeper->fitness() > getBestFitness()) {
					setBestFitness(sweeper->fitness());
					setBestSweeper(sweeper);
				}
			}
		}
		
		std::set<int> ints;
		std::set<SharedPtrMine>::iterator it;

		for (it = collectedMines.begin(); it != collectedMines.end(); ++it) {
			SharedPtrMine mine = *it;
			int index = indexOfMine(mine);

			if (index >= 0) {
				bool isIndexFoundInSetOfIndexesOfMines;
				isIndexFoundInSetOfIndexesOfMines = (ints.find(index) != ints.end());
				
				if (isIndexFoundInSetOfIndexesOfMines) {
					throw UnsupportedOperationException("Index of mine already inside the set of indexes of mines");
				} else {
					bool isIndexInsertedInSetOfIndexesOfMine;
					isIndexInsertedInSetOfIndexesOfMine = ints.insert(index).second;
					
					if (!isIndexInsertedInSetOfIndexesOfMine) {
						throw UnsupportedOperationException("Index of mine not inserted in the set of indexes of mines");
					}
				}
				
				//std::cout << "Before update mine's position = " << mine->getPosition() << "\n";
				setPositionOfMineRandomly(mine);
				//std::cout << "mine's position = " << mine->getPosition() << "\n";
				SharedPtrPhysicObject3D object = mine;//std::dynamic_pointer_cast<PhysicObject3D>(mine);
				assignCell3DsToPhysicObject3D(object);
			} else {
				throw UnsupportedOperationException("IndexOutOfBounds: " + index);
			}
		}
	}

	void Simulation::updateSweepersColors() {
		int mostCollectedMines = 0;
		
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrSmartMineSweeper sweeper = getSweeper(i);
			int collectedMines = sweeper->numberOfCollectedMines();
			
			if (collectedMines > mostCollectedMines) {
				mostCollectedMines = collectedMines;
			}
		}
		
		if (mostCollectedMines < 0) {
			throw UnsupportedOperationException("mostCollectedMines < 0");
		}
		
		if (mostCollectedMines != getBestFitness()) {
			throw UnsupportedOperationException("mostCollectedMines != getBestFitness()");
		}
		
		for (int unsigned i = 0; i < numberOfSweepers(); ++i) {
			SharedPtrSmartMineSweeper sweeper = getSweeper(i);
			int collectedMines = sweeper->numberOfCollectedMines();
			
			if (collectedMines > mostCollectedMines) {
				throw UnsupportedOperationException("collectedMines > mostCollectedMines");
			}
			
			if (collectedMines > 0) {
				if (collectedMines != mostCollectedMines) {
					sweeper->setColor(Simulation::defaultColorOfSweeper);
				} else {
					sweeper->setColor(Simulation::colorOfBestSweeper);
				}
			} else { // collectedMines == 0
				sweeper->setColor(Simulation::colorOfMinelessSweeper);
			}
		}
	}

	std::chrono::time_point<std::chrono::system_clock> Simulation::getCurrentTimeMillis() const {
		return std::chrono::system_clock::now();
	}
}