#ifndef RANDOM_GENERATOR_OF_SWEEPERS_AND_MINES_H
#define RANDOM_GENERATOR_OF_SWEEPERS_AND_MINES_H

#include <memory>
#include <vector>
#include "Grid3D.h"
#include "Mine.h"
#include "Parameters.h"
#include "SmartMineSweeper.h"


namespace smrtsw {
	
	class RandomGeneratorOfSweepersAndMines {
	public:
		RandomGeneratorOfSweepersAndMines();
		RandomGeneratorOfSweepersAndMines(
			std::shared_ptr<Grid3D> const & grid,
			ai::Parameters const & parameters
		);
		
		std::shared_ptr<std::vector<smrtsw::SharedPtrMine>> 
		generateMines() const;
	
		SharedPtrMine generateMineAtRandomPosition() const;
		
		std::shared_ptr<std::vector<smrtsw::SharedPtrSmartMineSweeper>>
		generateSweepers() const;
	
		std::pair<
			std::shared_ptr<std::vector<smrtsw::SharedPtrSmartMineSweeper>>, 
			std::shared_ptr<std::vector<smrtsw::SharedPtrMine>>
		> generateSweepersAndMines() const;
	
		std::shared_ptr<Grid3D> getGrid() const;
		
		template <class Obj>
		Vector3D randomPosition() const;
		
		template <class PhysicObjectType>
		bool setObjectInEmptySpace(SharedPtrPhysicObject3D & object) const;
	
		template <class PhysicObjectType>
		bool setObjectAtDistanceFromOthers(SharedPtrPhysicObject3D & object) const;
		
		template <class Obj>
		void setZCoordinate(Vector3D & position) const;
		
	private:
		std::weak_ptr<Grid3D> grid_;
		ai::Parameters parameters_;
		std::vector<std::shared_ptr<std::vector<ngn::SharedPtrFunction>>> functions_;
		static int maximumTries;
		
		bool areNeighborObjectsFarEnough(SharedPtrPhysicObject3D object, Real minimumDistance) const;
		
		std::vector<std::shared_ptr<std::vector<ngn::SharedPtrFunction>>> 
		buildNeuralNetworkFunctions() const;
		
		bool objectCollidesWithObjectInArrayOfObjects(
			SharedPtrPhysicObject3D const & object,
			std::vector<SharedPtrPhysicObject3D> const & objects
		) const;
		
		SharedPtrSmartMineSweeper 
		generateSweeperAtRandomPosition() const;
		
		SharedPtrBrain generateSweeperBrain() const ;
		SharedPtrMobile generateSweeperMobile() const;
		
		template <class Obj>
		Real getMinimumDistanceBetweenObjects() const;
	};
	
}

#endif // RANDOM_GENERATOR_OF_SWEEPERS_AND_MINES_H