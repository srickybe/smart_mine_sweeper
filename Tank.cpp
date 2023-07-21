#include "Tank.h"
#include "BoundingVolumeBuilder3D.h"
#include "Math.h"
#include "Matrix2D.h"
//#include "MeshBuilder.h"
#include "Mesh.h"
#include "UnsupportedOperationException.h"

namespace smrtsw {
	
	ngn::SharedPtrMesh Tank::mesh = std::make_shared<ngn::Mesh>();
	
	Tank::Tank() :
		ngn::Mobile(ngn::Vector3D::zero(), ngn::Real(0.0))
	{
		lookAt = ngn::Vector3D::zero();
		speed = 0;
		leftTrackSpeed = 0;
		rightTrackSpeed = 0;
		maximumTrackSpeed = 0;
		maximumTurnRate = 0;
		this->boundingVolume_ = 
			std::make_shared<ngn::OrientedBox3D>(
				getPosition(), 
				ngn::Matrix3D::identity(), 
				ngn::Vector3D::zero()
			);
		this->boundingSphere_ = ngn::Sphere(getPosition(), 0.0); 
		throwIfBoundingVolumeAndSphereNotInValidState();
	}

	Tank::Tank
	(
		ngn::SharedPtrIntersectable const & boundingVolume,
		ngn::Sphere const & boundingSphere,
		ngn::Real angle
	) :
		ngn::Mobile(boundingVolume->getPosition(), angle),
		boundingVolume_(boundingVolume),
		boundingSphere_(boundingSphere)
	{
		throwIfBoundingVolumeAndSphereNotInValidState();
		this->speed = 0.0;
		this->leftTrackSpeed = 0.0;
		this->rightTrackSpeed = 0.0;
		this->maximumTrackSpeed = 40.0;
		this->maximumTurnRate = 0.1;
	}

	Tank::Tank(
		ngn::SharedPtrIntersectable const & boundingVolume,
		ngn::Sphere const & boundingSphere,
		ngn::Real angle,
		ngn::Real leftTrackSpeed,
		ngn::Real rightTrackSpeed,
		ngn::Real maximumTrackSpeed,
		ngn::Real maximumTurnRate
	) : Tank(boundingVolume, boundingSphere, angle)
	{
		this->leftTrackSpeed = leftTrackSpeed;
		this->rightTrackSpeed = rightTrackSpeed;
		this->maximumTrackSpeed = maximumTrackSpeed;
		this->maximumTurnRate = maximumTurnRate;
		this->lookAt = ngn::Vector3D(ngn::Math<ngn::Real>::cos(angle), ngn::Math<ngn::Real>::sin(angle), 0.0);
	}

	bool Tank::areBoundingVolumeAndSphereValid(
		ngn::SharedPtrIntersectable const & boundingVolume,
		ngn::Sphere const & boundingSphere
	) const {
		ngn::Real tolerance = (ngn::Real)1.0e-6;
		
		return boundingVolume->getPosition().equalsWithTol(boundingSphere.getPosition(), tolerance);
	}
	
	void Tank::throwIfBoundingVolumeAndSphereNotInValidState() const {
		if (!areBoundingVolumeAndSphereValid(boundingVolume_, boundingSphere_)) {
			std::cout << "boundingVolume_->getPosition() = ";
			std::cout << boundingVolume_->getPosition() << "\n";
			std::cout << "boundingSphere_.getPosition() = ";
			std::cout << boundingSphere_.getPosition() << "\n";
			throw UnsupportedOperationException("position of bounding volume different from bounding sphere");
		}
	}
	
	ngn::Real Tank::getLeftTrackSpeed() const {
		return leftTrackSpeed;
	}

	ngn::Vector3D Tank::getLookAt() const {
		return lookAt;
	}

	ngn::Real Tank::getMaximumTrackSpeed() const {
		return maximumTrackSpeed;
	}

	ngn::Real Tank::getMaximumTurnRate() const {
		return maximumTurnRate;
	}

	ngn::Real Tank::getRightTrackSpeed() const {
		return rightTrackSpeed;
	}

	ngn::Real Tank::getSpeed() const {
		return speed;
	}

	void Tank::setLeftTrackSpeed(ngn::Real leftTrackSpeed) {
		this->leftTrackSpeed = leftTrackSpeed;
	}

	void Tank::setRightTrackSpeed(ngn::Real rightTrackSpeed) {
		this->rightTrackSpeed = rightTrackSpeed;
	}
	
	void Tank::update(ngn::Real dt) {
		ngn::Real rotForce = computeRotationForce(dt);
		Mobile::setAngle(getAngle() + rotForce);
		computeSpeed();
		setLookAt(getOrientation().getCol(0));
		//std::cout << "position = " << getPosition() << "\n";
		Tank::setPosition(ngn::Vector3D::add(getPosition(), ngn::Vector3D::mult(getLookAt(), getSpeed() * dt)));
		//std::cout << "%%%After update: position = " << getPosition() << "\n";ngn::
		//std::cout << "rotForce = " << rotForce << "\n";
		//std::cout << "getAngle() = " << getAngle() << "\n";
	}		

	ngn::Vector3D Tank::getLinearVelocity() const {
		ngn::Vector3D res = ngn::Vector3D::mult(getLookAt(), speed);

		return res;
	}

	
	ngn::SharedPtrIntersectable const & Tank::getBoundingVolume() const {
		return boundingVolume_;
	}

	ngn::SharedPtrMesh const & Tank::getMesh() const {
		return Tank::mesh;
	}
	
	ngn::Sphere const & Tank::getBoundingSphere() const {
		return boundingSphere_;
	}
		
	void Tank::setPosition(ngn::Vector3D const & pos) {
		ngn::Mobile::setPosition(pos);
		getBoundingVolume()->setPosition(getPosition());
		getBoundingVolume()->setOrientation(ngn::Mobile::getOrientation());
		boundingSphere_.setPosition(getPosition());
	}
	
	void Tank::steer(ngn::Vector const & inputs) {
		leftTrackSpeed = inputs.getElem(0) * getMaximumTrackSpeed();
		rightTrackSpeed = inputs.getElem(1) * getMaximumTrackSpeed();
	}

	
	void Tank::print(std::ostream & out) const {
		out << "TankV2{\n";
		ngn::Mobile::print(out);
		out << "\nlookAt=" << lookAt
			<< ", \nspeed=" << speed
			<< ", \nleftTrackSpeed=" << leftTrackSpeed
			<< ", \nrightTrackSpeed=" << rightTrackSpeed
			<< ", \nmaximumTrackSpeed=" << maximumTrackSpeed
			<< ", \nmaximumTurnRate=" << maximumTurnRate
			<< ", \nboundingVolume_=" << boundingVolume_
			<< "\n}";
	}
	
	void Tank::setLookAt(ngn::Vector3D vector) {
		lookAt = vector;
	}
	
	void Tank::computeSpeed() {
		speed = getLeftTrackSpeed() + getRightTrackSpeed();
	}

	ngn::Real Tank::computeRotationForce(ngn::Real dt) {
		ngn::Real rotForce = (getRightTrackSpeed() - getLeftTrackSpeed()) * dt;
		rotForce = clampRotationForce(rotForce);

		return rotForce;
	}

	ngn::Real Tank::clampRotationForce(ngn::Real rotForce) const {
		ngn::Real res = rotForce;

		if (rotForce > getMaximumTurnRate()) {
			res = getMaximumTurnRate();
		} else if (rotForce < -getMaximumTurnRate()) {
			res = -getMaximumTurnRate();
		}

		return res;
	}
}