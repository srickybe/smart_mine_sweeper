#include "Box.h"
#include <iostream>
#include "Sphere.h"

using namespace std;

namespace ngn{
	Box::Box() :
		center_(0.0, 0.0, 0.0),
		orientation_(Matrix3D::identity()),
		halfExtents_(0.0, 0.0, 0.0)
	{
	   
	}

	Box::Box(Vector3D const & pstn, Vector3D const & hlfXtnts) :
		center_(pstn),
		orientation_(Matrix3D::identity()),
		halfExtents_(hlfXtnts)
	{
	   
	}

	Box::Box(Vector3D const & pstn, Matrix3D const & ornttn, Vector3D const & hlfXtnts) :
		center_(pstn),
		orientation_(ornttn),
		halfExtents_(hlfXtnts)
	{
	   
	}

	Vector3D const & Box::getCenter() const {
		return center_;
	}


	void Box::setCenter(Vector3D const & center) {
		this->center_ = center;
	}


	Matrix3D const & Box::getOrientation() const {
		return orientation_;
	}


	void Box::setOrientation(Matrix3D const & orientation) {
		this->orientation_ = orientation;
	}


	Vector3D const & Box::getHalfExtents() const {
		return halfExtents_;
	}


	void Box::setHalfExtents(Vector3D const & halfExtents) {
		for (int i = 0; i < 3; ++i) {
			if (halfExtents.get(i) < 0.0) {
				cout << "halfExtents coordinate is inferior or equal to zero\n";
				throw exception();
			}
		}

		this->halfExtents_ = halfExtents;
	}

	bool Box::intersects(Sphere const & sphere) const {
		return boxIntersectsSphere(*this, sphere);
	}

	bool boxIntersectsSphere(Box const & box1, Sphere const & sphere2) {
		Vector3D dist = Vector3D::sub(sphere2.getCenter(), box1.getCenter());
		Vector3D localDist = Matrix3D::transp(box1.getOrientation()).mult(dist);

		for (int i = 0; i < 3; ++i) {
			if (abs(localDist.get(i)) > box1.getHalfExtents().get(i) + sphere2.getRadius()) {
				return false;
			}
		}

		return true;
	}
}