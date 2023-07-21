#ifndef MOBILE_H
#define MOBILE_H

#include <memory>
#include "Intersectable.h"
#include "Matrix3D.h"
#include "Mesh.h"
#include "Real.h"
#include "Vector.h"
#include "Vector3D.h"

namespace ngn {
	
	class RGBColor;
	class Mobile;
	std::ostream & operator <<(std::ostream & out, Mobile const & mobile);
	
	class Mobile {
	public:
		Mobile(Vector3D const & position, Real ang);

		Real getAngle() const;
		void setAngle(Real ang);
		Vector3D const & getPosition() const;
		virtual void setPosition(Vector3D const & position);
		Matrix3D const & getOrientation() const;
		virtual void print(std::ostream & out) const;
		//virtual void setColor(RGBColor const & color) = 0;
		//virtual void draw() const = 0;
		virtual Vector3D getLinearVelocity() const = 0;
		virtual SharedPtrIntersectable const & getBoundingVolume() const = 0;
		virtual Sphere const & getBoundingSphere() const = 0;
		virtual SharedPtrMesh const & getMesh() const = 0;
		virtual void steer(Vector const & inputs) = 0;
		virtual void update(Real dt) = 0;
		static void test();
		
	private:
		Vector3D position;
		Real angle;
		Matrix3D orientation;
		
		void setOrientation(Matrix3D const & orientation);
	};
	
	typedef std::shared_ptr<Mobile> SharedPtrMobile;
}

#endif // MOBILE_H