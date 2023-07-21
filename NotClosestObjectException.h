#ifndef NOT_CLOSEST_OBJECT_EXCEPTION_H
#define NOT_CLOSEST_OBJECT_EXCEPTION_H

#include "SharedPtrPhysicObject3D.h"

namespace ngn {
	
	class NotClosestObjectException: std::exception {
	public:
		NotClosestObjectException(
			SharedPtrPhysicObject3D const & object,
			SharedPtrPhysicObject3D const & objectFound,
			SharedPtrPhysicObject3D const & closestObject,
			int generation
		);
	
		SharedPtrPhysicObject3D const & getObject() const;
		SharedPtrPhysicObject3D const & getObjectFound() const;
		SharedPtrPhysicObject3D const & getClosestObject() const;
		int getGeneration() const;
		char const * what() const throw();
		
	private:
		SharedPtrPhysicObject3D object_;
		SharedPtrPhysicObject3D objectFound_;
		SharedPtrPhysicObject3D closestObject_;
		int generation_;
	};
}

#endif // NOT_CLOSEST_OBJECT_EXCEPTION_H