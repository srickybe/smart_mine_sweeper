#ifndef SMART_MINE_SWEEPER_H
#define SMART_MINE_SWEEPER_H

#include <memory>
#include "Brain.h"
#include "Chromosome.h"
#include "Intersectable.h"
#include "Mesh.h"
#include "Mine.h"
#include "Mobile.h"
#include "PhysicObject3D.h"
#include "Real.h"
#include "RGBColor.h"
#include "SteeringFunction.h"
#include "Vector3D.h"

using namespace ai;
using namespace ngn;

namespace smrtsw {
	
	class Sensors;
	class Sphere; 
	class SteeringFunction;
	
	class SmartMineSweeper: public PhysicObject3D {
	public:
		SmartMineSweeper();
		SmartMineSweeper(
			SharedPtrBrain const & brain, 
			SharedPtrMobile const & car, 
			SharedPtrMine const & closestMine//,
			//Sphere containingSphere
		);
		static void incrementNumberOfSweepers();
		static int getNumberOfSweepers();
		SharedPtrIntersectable const & getBoundingVolume() const;
		SharedPtrVector3D const & getClosestMineDirection() const;
		RGBColor const & getColor() const;
		SharedPtrMobile getMobile();
		int getNumberOfCollectedMines() const;
		int getID() const;
		Vector3D const & getPosition() const;
		Vector3D getLinearVelocity() const;
		SharedPtrMine const & getClosestMine() const;
		SharedPtrMobile const & getVehicle() const;
		void setColor(RGBColor const & color);
		void setDirectionToClosestMine(SharedPtrVector3D const & relativePositionOfMine, bool normalized);
		void setPosition(Vector3D const & position);
		void setVehicle(SharedPtrMobile const & car);
		std::pair<SharedPtrReal, SharedPtrVector3D> 
			squaredDistanceToMine(SharedPtrMine const & mine) const;
		
		void setClosestMine(SharedPtrMine const & closestMine);
		SharedPtrVector3D relativePositionOfMine(SharedPtrMine const & mine) const;
		void computeAndSetClosestMineDirection();
		void setNumberOfCollectedMines(int numberOfCollectedMiines);
		void steerToClosestMine(SharedPtrSteeringFunction & steeringFunction);
		Vector processSteeringInputs(Vector const & inputs) ;
		Matrix3D const & getOrientation() const;
		Vector3D heading() const;
		SharedPtrBrain const & getBrain() const;
		void update(Real dt);
		void setBrain(SharedPtrChromosome const & chr);
		void print(std::ostream & out) const;
		Real fitness() const;
		void incrementNumberCollectedMines(int numberOfMines);
		int numberOfCollectedMines() const;
		void draw() const;
		void drawInfos() const;
		void drawDistanceToClosestMine() const;
		bool isMovable() const;
		void setMovable(bool movable);
		ngn::Sphere const & getBoundingSphere() const;
		void setBoundingSphere(ngn::Sphere const & sphere);
		void applySteeringOutputs(Vector const & outputs);
		
	private: 
		static int NUMBER_OF_MINE_SWEEPERS;// = 0;
		int ID;
		SharedPtrBrain brain;
		SharedPtrMobile vehicle;
		SharedPtrMine closestMine;
		SharedPtrVector3D closestMineDirection;
		RGBColor color;
		static std::shared_ptr<Sensors> SENSORS; 
	};
	
	typedef std::shared_ptr<SmartMineSweeper> SharedPtrSmartMineSweeper;
}

#endif // SMART_MINE_SWEEPER_H