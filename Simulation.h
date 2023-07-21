#ifndef SIMULATION_H
#define SIMULATION_H

#include <chrono>
#include <memory>
#include <thread>
#include <vector>
#include "Brain.h"
#include "BrainEvolver.h"
#include "Chromosome.h"
#include "Graphics.h"
#include "Grid3D.h"
#include "Parameters.h"
#include "Partitions.h"
#include "Population.h"
#include "PredicateOfSharedPtrPhysicObject3D.h"
#include "PredicateOfPairOfSharedPtrPhysicObject3D.h"
#include "RandomGeneratorOfSweepersAndMines.h"
#include "Real.h"
#include "Renderer.h"
#include "RGBColor.h"
#include "Settings.h"
#include "SharedArrayOfSharedMines.h"
#include "SharedArrayOfSharedSweepers.h"
#include "SmartMineSweeper.h"
#include "Statistics.h"
#include "SteeringFunction.h"
//#include "World.h"

using namespace ai;
using namespace ngn;

namespace smrtsw {
	
	class Simulation {
	public:
		
		class Generation {
		public:
			Generation();
			Generation(int number);
			void addBrainOfBestFit(Brain const & brain);
			Real elapsedTime() const;
			Real getCurrentTime() const;
			int getNumber() const;
			std::chrono::time_point<std::chrono::system_clock> const & 
			getStartTimeMillis() const;
			void incrementTime(Real deltaTime);
			void setStartTimeOfCurrentGenerationMillis(
				std::chrono::time_point<std::chrono::system_clock> const & startTime
			);
			//void updateCurrentTime();
			
		private:
			int number_;
			std::chrono::time_point<std::chrono::system_clock> startTimeMillis_;
			Real currentTime_;
			std::vector<Brain> brainOfBestFits_;
		};
		
		Simulation();
		Simulation(
			Parameters const & params,
			Settings const & settings,
			Grid3D const & spacePartition,
			SharedArrayOfSharedSweepers const & sweepers,
			SharedArrayOfSharedMines const & mines,
			SharedPtrSteeringFunction const & steeringFunction
		);
			
		Simulation(
			Parameters const & params, 
			SharedPtrSteeringFunction const & steeringFunction
		);

		void func();
		void func2(Real dt);
		Population extractSweeperSBrains() const;
		SharedPtrSmartMineSweeper findBestSweeper() const;
		SharedPtrMine findClosestMineToSweeper(SharedPtrSmartMineSweeper const & sweeper) const;
		void generateNotIntersectingSweepersAndMines();
		SharedPtrFunction getActivationFunction();
		SharedPtrSmartMineSweeper const & getBestSweeper() const;
		RGBColor getColorOfMinelessSweeper();
		RGBColor getColorOfBestSweeper();
		Generation const & getCurrentGeneration() const;
		Generation & getCurrentGeneration();
		RGBColor getDefaultColorOfSweeper();
		Real getFrameTime() const;
		int getGenerationDurationInSeconds();
		long getInitialClosestMineUpdateDelay();
		long getClosestMineUpdatePeriod();
		SharedPtrMine const & getMine(int i) const;
		SharedPtrMine & getMine(int i);
		int getNumberOfGenerationsOffline() const;
		int getNumberOfGenerationsRealTime() const;
		Parameters getParameters() const;
		//int getCurrentGenerationNumber() const;
		int getSleepTimeMillis() const;
		std::chrono::time_point<std::chrono::system_clock> const & 
			getStartTimeOfCurrentGenerationMillis() const;
		SharedPtrSmartMineSweeper getSweeper(int i) const;
		void graphicsThreadFunction();
		void incrementCurrentGenerationTime(Real deltaTime);
		bool isOnLine() const;
		void launchGraphicsThread();
		void launchPhysicsThread();
		void launchTimerThread();
		int unsigned numberOfMines() const;
		int unsigned numberOfSweepers() const;
		void paintComponent();
		//void physicsThreadFunction();
		void printStats(std::ostream & out);
		void replaceSweepersBrains(std::vector<Population> const & populations);
		void copy(Simulation sim);
		Vector3D randomMinePosition() const;
		Vector3D randomSweeperPosition() const;
		void run();
		//void runOffline();
		//void runInRealTime();
		void writeSweepersInFile(std::string filePath);
		void writeBestSweeperInFile(std::string filePath);
		void setBestSweeper(SharedPtrSmartMineSweeper const & sweeper);
		void setBrainEvolver(SharedPtrBrainEvolver const & brainEvolver);
		void setBestFitness(Real value);
		void setOnLine(bool isOnLine);
		void setPositionOfMine(int i, Vector3D position);
		void start();
		void steerSweepersToClosestMines();
		void print(std::ostream & out) const;
		void updateSweepersPositions(Real elapsedTime);
		void updateSweepersColors();
		void writeResultsInFile(std::string filePath);
		void main();
		void test();
		Grid3D spacePartitionFromOriginExtentsPartitions(
				Vector3D const & worldOrigin,
				Vector3D const & worldExtents,
				Partitions const & partitions
		);
		
	private:
		Parameters parameters;
		Settings GASettings;
		SharedPtrBrainEvolver brainEvolver;
		std::vector<Statistics> statistics;
		std::shared_ptr<Grid3D> grid;
		RandomGeneratorOfSweepersAndMines sweepersAndMinesGenerator;
		SharedArrayOfSharedSweepers sweepers;
		SharedPtrSteeringFunction steeringFunction;
		SharedPtrSmartMineSweeper bestSweeper;
		Real bestFitness;
		SharedArrayOfSharedMines mines;
		ngn::Real mineRadius;
		int sleepTimeMillis;
		Real frameTime;
		std::chrono::time_point<std::chrono::system_clock> startTimeMillis;
		std::chrono::time_point<std::chrono::system_clock> currentTimeMillis;
		std::chrono::time_point<std::chrono::system_clock> startTimeOfCurrentGenerationMillis;
		//int currentGenerationNumber;
		std::vector<Generation> generations;
		//std::thread graphicsThread;
		//std::thread physicsThread;
		static RGBColor const colorOfMinelessSweeper;
		static RGBColor const colorOfBestSweeper;
		static RGBColor const defaultColorOfSweeper;
		static RGBColor const colorOfMine;
		bool onLine;
		std::shared_ptr<PredicateOfSharedPtrPhysicObject3D> isSharedMine;	
		
		void addAllMinesToSpacePartition();
		void addAllSweepersToSpacePartition();
		void addBrainOfBestFitsToCurrentGeneration();
		void addCurrentStatistics();
		void addGeneration();
		void assignCell3DsToPhysicObject3D(SharedPtrPhysicObject3D & object);
		bool areAllSweeperMineCollisionsDetected(
			std::vector<PairOfSharedPtrPhysicObject3D> const & collidingPairs
		) const;
		bool areSweepersValid() const;
		bool areObjectsValid() const;
		Real averageFitness() const;
		void checkNumberOfMinesInSpacePartition() const;
		void checkNumberOfSweepersInSpacePartition() const;
		void clearGrid();
		std::vector<SharedPtrBrain> 
		convertChromosomesIntoBrains(std::vector<SharedPtrChromosome> const & chrs);
		SharedPtrBrain convertChromosomeIntoBrain(SharedPtrChromosome const & chr);
		int currentGenerationNumber() const;
		Real currentGenerationTime() const;
		Real squaredDistanceBetweenSweeperAndMine(
			SharedPtrSmartMineSweeper const & sweeper, 
			SharedPtrMine const & mine
		) const;
		Real elapsedTime();
		Real elapsedTime(
			std::chrono::time_point<std::chrono::system_clock> begin,
			std::chrono::time_point<std::chrono::system_clock> end
		) const;
		std::vector<Population> evolveBrains();
		void findClosestMinesToSweepers() const;
		Real fitnessStandardDeviation(Real averageFitness) const;
		std::string formatElapsedTime(Real elapsedTime) const;
		Real getMinimumDistanceBetweenMines() const;
		Real getMinimumDistanceBetweenSweepers() const;
		int getNumberOfGenerations() const;
		Real getPhysicsUpdateRate() const;
		//SharedPtrSmartMineSweeper getSweeper(int i) const;
		Real getBestFitness() const;
		//void incrementCurrentGenerationNumber();
		int indexOfMine(SharedPtrMine const & mine) const;
		void initializeGraphics();
		std::pair<bool, SharedPtrMine> isMineClosestToSweeper(
			SharedPtrMine const & mine, 
			SharedPtrSmartMineSweeper const & sweeper
		) const;
		bool isObjectValid(SharedPtrPhysicObject3D const & object) const;
		bool isSweeperInsideGrid(SmartMineSweeper const & sweeper) const;
		Real pourcentageOfMinelessSweepers() const;
		Settings readGASettingsFromFilePath(std::string filePath);
		void relocateOutOfBoundsSweepers();
		void setPositionOfMineRandomly(SharedPtrMine & mine);
		void setPositionOfMinesRandomly();
		
		template <class PhysicObjectType>
		void setPositionOfPhysicObject3D(SharedPtrPhysicObject3D & object);
		
		void resetMinesPosition();
		void resetSweepersColors(RGBColor const & color);
		void resetSweepersNumberOfCollectedMines();
		void resetSweepersPosition();
		//void setCurrentGenerationNumber(int currentGenerationNumber);
		void setStartTimeOfCurrentGenerationMillis(
			std::chrono::time_point<std::chrono::system_clock> const & timeMillis
		);
		bool shouldSweepersAndMinesPositionBeReset();
		std::pair<SharedPtrSmartMineSweeper, SharedPtrMine> 
			sweeperAndMineFromPhysicObjectPair(
				PairOfSharedPtrPhysicObject3D const & objectPair
		) const;
		int unsigned totalNumberOfCollectedMines() const;
		int unsigned totalNumberOfMinesInSpacePartition() const;
		int unsigned totalNumberOfSweepersInSpacePartition() const;
		void updateBlockOfMines();
		void updateBlockOfSweepers();
		void updateCollectedMines();
		void updateGraphicObjects();
		std::chrono::time_point<std::chrono::system_clock> getCurrentTimeMillis() const;
	};
}

#endif // SIMULATION_H