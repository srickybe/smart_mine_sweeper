#ifndef BOX_H
#define BOX_H

#include "Matrix3D.h"
#include "Vector3D.h"

namespace ngn {
	class Sphere;

	class Box {
	public:
		Box();
		Box(Vector3D const & pstn, Vector3D const & hlfXtnts);
		Box(Vector3D const & pstn, Matrix3D const & ornttn, Vector3D const & hlfXtnts);
		Vector3D const & getCenter() const;
		void setCenter(Vector3D const & center);
		Matrix3D const & getOrientation() const;
		void setOrientation(Matrix3D const & orientation);
		Vector3D const & getHalfExtents() const;
		void setHalfExtents(Vector3D const & halfExtents);
		bool intersects(Sphere const & sphere) const;

	private:
		Vector3D center_;
		Matrix3D orientation_;
		Vector3D halfExtents_;
	};

	bool boxIntersectsSphere(Box const & box1, Sphere const & sphere2);
}

#endif // BOX_H
