#include "SmartMineSweeper.h"
#include "Line.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "Quad.h"
#include "Sensors.h"
#include "UnsupportedOperationException.h"
#include "Vector2D.h"
#include "Vector3D.h"

namespace smrtsw {
	
	int SmartMineSweeper::NUMBER_OF_MINE_SWEEPERS = 0;
	std::shared_ptr<Sensors> SmartMineSweeper::SENSORS = std::make_shared<Sensors>(5, 25.0);
	
	SmartMineSweeper::SmartMineSweeper() {
		this->ID = getNumberOfSweepers();
		incrementNumberOfSweepers();
		brain = nullptr;
		vehicle = nullptr;
		closestMine = nullptr;
		closestMineDirection = nullptr;
		color = RGBColor::BLACK;
	}

	SmartMineSweeper::SmartMineSweeper(
		SharedPtrBrain const & brain, 
		SharedPtrMobile const & car, 
		SharedPtrMine const & closestMine
	) {
		this->ID = getNumberOfSweepers();
		incrementNumberOfSweepers();
		this->brain = brain;
		this->vehicle = car;
		this->closestMine = closestMine;
		computeAndSetClosestMineDirection();
		this->color = color;
	}

	void SmartMineSweeper::incrementNumberOfSweepers() {
		++NUMBER_OF_MINE_SWEEPERS;
	}

	int SmartMineSweeper::getNumberOfSweepers() {
		return NUMBER_OF_MINE_SWEEPERS;
	}

	
	SharedPtrIntersectable const & SmartMineSweeper::getBoundingVolume() const {
		return vehicle->getBoundingVolume();
	}

	SharedPtrVector3D const & SmartMineSweeper::getClosestMineDirection() const {
		return closestMineDirection;
	}

	RGBColor const & SmartMineSweeper::getColor() const {
		return color;
	}
	
	int SmartMineSweeper::getID() const {
		return ID;
	}

	SharedPtrMobile SmartMineSweeper::getMobile() {
		return vehicle;
	}
	
	int SmartMineSweeper::getNumberOfCollectedMines() const {
		return brain->getNumberOfCollectedMines();
	}
	
	Vector3D const & SmartMineSweeper::getPosition() const {
		return vehicle->getPosition();
	}

	Vector3D SmartMineSweeper::getLinearVelocity() const {
		return vehicle->getLinearVelocity();
	}

	SharedPtrMine const & SmartMineSweeper::getClosestMine() const {
		return closestMine;
	}

	SharedPtrMobile const & SmartMineSweeper::getVehicle() const {
		return vehicle;
	}

	void SmartMineSweeper::setColor(RGBColor const & color) {
		this->color = color;
	}

	void SmartMineSweeper::setDirectionToClosestMine(SharedPtrVector3D const & relativePositionOfMine, bool normalized) {
		if (relativePositionOfMine != nullptr) {
			if (relativePositionOfMine->equalsWithTol(Vector3D::zero(), (Real)1.0e-6)) {
				this->closestMineDirection = SharedPtrVector3D(new Vector3D(*relativePositionOfMine));
			} else if (!normalized) {
				this->closestMineDirection = SharedPtrVector3D(new Vector3D(*relativePositionOfMine));
				this->closestMineDirection->norm();
			} else {
				this->closestMineDirection = SharedPtrVector3D(new Vector3D(*relativePositionOfMine));
			}
		}
	}

	void SmartMineSweeper::setPosition(Vector3D const & position) {
		vehicle->setPosition(position);
	}

	void SmartMineSweeper::setVehicle(SharedPtrMobile const & car) {
		this->vehicle = car;
	}

	std::pair<SharedPtrReal, SharedPtrVector3D> 
	SmartMineSweeper::squaredDistanceToMine(SharedPtrMine const & mine) const {
		SharedPtrVector3D position = relativePositionOfMine(mine);
		
		if (position != nullptr) {
			SharedPtrReal distance(new Real(position->lengthSquared()));
			
			return std::make_pair(distance, position);
		} else {
			return std::make_pair(nullptr, nullptr);
		}
		
	}

	void SmartMineSweeper::setClosestMine(SharedPtrMine const & closestMine) {
		this->closestMine = closestMine;
	}

	SharedPtrVector3D SmartMineSweeper::relativePositionOfMine(SharedPtrMine const & mine) const {
		if (mine != nullptr) {
			Vector3D res = Vector3D::sub(mine->getPosition(), getPosition());

			return SharedPtrVector3D(new Vector3D(res));
		} else {
			return nullptr;
		}
	}

	void SmartMineSweeper::computeAndSetClosestMineDirection() {
		bool normalized = true;
		
		if (getClosestMine() != nullptr) {
			setDirectionToClosestMine(
					relativePositionOfMine(getClosestMine()),
					!normalized
			);
		}
	}

	void SmartMineSweeper::setNumberOfCollectedMines(int numberOfCollectedMiines) {
		brain->setNumberOfCollectedMines(numberOfCollectedMiines);
	}

	void SmartMineSweeper::applySteeringOutputs(Vector const & outputs) {
		vehicle->steer(outputs);
	}
	
	void SmartMineSweeper::steerToClosestMine(SharedPtrSteeringFunction & steeringFunction) {
		steeringFunction->steer(*this);
	}

	Vector SmartMineSweeper::processSteeringInputs(Vector const & inputs) {
		Vector outputs = brain->output(inputs);

		return outputs;
	}

	Matrix3D const & SmartMineSweeper::getOrientation() const {
		return vehicle->getOrientation();
	}

	Vector3D SmartMineSweeper::heading() const {
		return getOrientation().getCol(0);
	}

	SharedPtrBrain const & SmartMineSweeper::getBrain() const {
		return brain;
	}

	void SmartMineSweeper::update(Real dt) {
		vehicle->update(dt);
		//std::cout << "***vehicle->getPosition() = " << vehicle->getPosition() << "\n";
		//boundingSphere.setPosition(vehicle->getPosition());
		//std::cout << "%%%boundingSphere.getPosition() = " << boundingSphere.getPosition() << "\n";
	}

	void SmartMineSweeper::setBrain(SharedPtrChromosome const & chr) {
		brain = std::dynamic_pointer_cast<Brain>(chr);
	}

	void SmartMineSweeper::print(std::ostream & out) const {
		out << "Sweeper{"
			<< "\nID =" << ID
			<< "\nbrain=" << brain
			<< ", \ncar=" << vehicle
			<< ", \nclosestMine=" << closestMine
			<< "\n}";
	}

	Real SmartMineSweeper::fitness() const {
		return brain->getFitness();
	}

	void SmartMineSweeper::incrementNumberCollectedMines(int numberOfMines) {
		brain->incrementNumberOfCollectedMines(numberOfMines);
	}

	int SmartMineSweeper::numberOfCollectedMines() const {
		return brain->getNumberOfCollectedMines();
	}

	void SmartMineSweeper::draw() const {
		/*vehicle->draw(g);
		drawDistanceToClosestMine(g);
		drawInfos(g);*/
	}

	void SmartMineSweeper::drawInfos() const {
		/*Vector2D dist = new Vector2D(-getOrientation().get(0, 0), -getOrientation().get(1, 0));
		Vector2D position = Vector2D::add(getPosition(), Vector2D::mult(dist, 30.0));
		g.drawString(Integer.toString(numberOfCollectedMines()), (int) position.getX(), (int) position.getY());*/
		//String blockID = "" + getBlock().getRow() + ":" + getBlock().getColumn();
		//g.drawString(blockID, (int) position.getX() - 10, (int) position.getY() - 10);
	}

	void SmartMineSweeper::drawDistanceToClosestMine() const {
		/*g.setColor(RGBColor::BLUE);

		if (this->getClosestMineDirection() != null) {
			Util.drawVectorAtPosition(
					g,
					Vector2D::mult(this->getClosestMineDirection(), 30.0),
					this->getPosition()
			);
		} else {
			System.err.println("CLOSEST MINE POSITION TO SWEEPER IS NULL");
		}*/
	}

	bool SmartMineSweeper::isMovable() const {
		return true;
	}
	
	void SmartMineSweeper::setMovable(bool movable) {
		
	}
	
	ngn::Sphere const & SmartMineSweeper::getBoundingSphere() const {
		return vehicle->getBoundingSphere();
	}
	
	void SmartMineSweeper::setBoundingSphere(ngn::Sphere const & sphere) {
		//boundingSphere = sphere;
	}
}