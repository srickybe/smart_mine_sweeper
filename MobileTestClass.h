#ifndef MOBILE_TEST_CLASS_H
#define MOBILE_TEST_CLASS_H

#include "Mobile.h"
#include "UnsupportedOperationException.h"

namespace ngn {
	
	class MobileTestClass: public Mobile {
	public:
		MobileTestClass(Vector3D const & position, Real angle) :
			Mobile(position, angle)
		{
			
		}
		
		void setColor(RGBColor const & color) {
			throw UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
		}
		
		
		void draw() const {
			throw UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
		}
		
		
		Vector3D getLinearVelocity() const {
			throw UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
		}
		
		
		SharedPtrIntersectable const & getBoundingVolume() const {
			throw UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
		}
		
		Sphere const & getBoundingSphere() const {
			throw UnsupportedOperationException("Not supported yet.");
		}
		
		SharedPtrMesh const & getMesh() const {
			throw UnsupportedOperationException("Not supported yet.");
		}
		
		void steer(Vector const & inputs) {
			throw UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
		}
		
		
		void update(Real dt) {
			throw UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
		}
	};
}

#endif // MOBILE_TEST_CLASS_H