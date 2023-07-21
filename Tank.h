#ifndef TANK_H
#define TANK_H

#include <vector>
#include "Intersectable.h"
#include "RGBColor.h"
#include "Mobile.h"
#include "OrientedBox3D.h"
#include "Real.h"
#include "Sphere.h"
#include "Vector3D.h"

namespace smrtsw {
	
	class Tank: public ngn::Mobile {
	public:
		Tank();
		
		Tank
		(
			ngn::SharedPtrIntersectable const & boundingVolume, 
			ngn::Sphere const & boundingSphere, 
			ngn::Real angle
		);
		
		Tank
		(
			ngn::SharedPtrIntersectable const & boundingVolume, 
			ngn::Sphere const & boundingSphere,
			ngn::Real angle,
			ngn::Real leftTrackSpeed,
			ngn::Real rightTrackSpeed,
			ngn::Real maximumTrackSpeed,
			ngn::Real maximumTurnRate
		);

		//RGBColor const & getRGBColor() const;
		ngn::Real getLeftTrackSpeed() const;
		ngn::Vector3D getLookAt() const;
		ngn::Real getMaximumTrackSpeed() const;
		ngn::Real getMaximumTurnRate() const;
		//Vector3D const & getPoint(int i) const;
		ngn::Real getRightTrackSpeed() const;
		ngn::Real getSpeed() const;
		//void setColor(RGBColor const & color);
		void setLeftTrackSpeed(ngn::Real leftTrackSpeed);
		void setRightTrackSpeed(ngn::Real rightTrackSpeed);
		void update(ngn::Real dt);
		ngn::Vector3D getLinearVelocity() const;
		ngn::SharedPtrIntersectable const & getBoundingVolume() const;
		ngn::SharedPtrMesh const & getMesh() const;
		ngn::Sphere const & getBoundingSphere() const;
		void setPosition(ngn::Vector3D const & pos);
		void steer(ngn::Vector const & inputs);
		void print(std::ostream & out) const;
		
	private:
		ngn::Vector3D lookAt;
		ngn::Real speed;
		ngn::Real leftTrackSpeed;
		ngn::Real rightTrackSpeed;
		ngn::Real maximumTrackSpeed;
		ngn::Real maximumTurnRate;
		ngn::SharedPtrIntersectable boundingVolume_;
		ngn::Sphere boundingSphere_;
		/*static Real wheelBase;
		static Real width;
		static Real height;
		static Real radius;*/
		void setLookAt(ngn::Vector3D vector);
		void computeSpeed();
		ngn::Real computeRotationForce(ngn::Real dt);
		ngn::Real clampRotationForce(ngn::Real rotForce) const;
		
		static ngn::SharedPtrMesh mesh;
		//static Sphere sphere;
		bool areBoundingVolumeAndSphereValid(
			ngn::SharedPtrIntersectable const & boundingVolume,
			ngn::Sphere const & boundingSphere
		) const;
		
		void throwIfBoundingVolumeAndSphereNotInValidState() const;
	};

}

#endif // TANK_H