#ifndef RESULT_H
#define RESULT_H

#include <memory>
#include <set>
#include "SharedPtrCell3D.h"
#include "SharedPtrPhysicObject3D.h"


namespace ngn {
	class Result {
	public:
		Result();
		Result(
			bool positive,
			SharedPtrPhysicObject3D const & closestNeighbor,
			double squaredDistance,
			std::set<SharedPtrCell3D> cellsTested
		);
		bool isPositive() const;
		void setPositive(bool positive);
		SharedPtrPhysicObject3D const & getClosestNeighbor() const;
		void setClosestNeighbor(SharedPtrPhysicObject3D const & closestNeighbor);
		double getDistance() const;
		void setDistance(double squaredDistance);
		std::set<SharedPtrCell3D> getCell3DsTested() const;
		void setCell3DsTested(std::set<SharedPtrCell3D> const & cells);
		void addtestedCell3D(SharedPtrCell3D const & cell);
		
	private:
		bool positive_;
		SharedPtrPhysicObject3D closestNeighbor_;
		double distance_;
		std::set<SharedPtrCell3D> cellsTested_;
	};
}

#endif // RESULT_H