#include "Result.h"
#include <limits>

namespace ngn {
	Result::Result() :
		positive_(false),
		closestNeighbor_(),
		distance_(std::numeric_limits<double>::max()),
		cellsTested_()
	{
		
	}

	Result::Result(
		bool positive,
		SharedPtrPhysicObject3D const & closestNeighbor,
		double distance,
		std::set<SharedPtrCell3D> cellsTested
	) :
		positive_(positive),
		closestNeighbor_(closestNeighbor),
		distance_(distance),
		cellsTested_(cellsTested)
	{
		
	}

	bool Result::isPositive() const {
		return positive_;
	}

	void Result::setPositive(bool positive) {
		positive_ = positive;
	}

	SharedPtrPhysicObject3D const & Result::getClosestNeighbor() const {
		return closestNeighbor_;
	}

	void Result::setClosestNeighbor(SharedPtrPhysicObject3D const & closestNeighbor) {
		closestNeighbor_ = closestNeighbor;
	}

	double Result::getDistance() const {
		return distance_;
	}

	void Result::setDistance(double distance) {
		distance_ = distance;
	}

	std::set<SharedPtrCell3D> Result::getCell3DsTested() const {
		return cellsTested_;
	}

	void Result::setCell3DsTested(std::set<SharedPtrCell3D> const & cells) {
		cellsTested_ = cells;
	}

	void Result::addtestedCell3D(SharedPtrCell3D const & cell) {
		cellsTested_.insert(cell);
	}
}