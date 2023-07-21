#include "Camera.h"
#include <iostream>
#include "Math.h"

namespace ngn {

	Camera::Camera()
	{
		//Init with standard OGL values:
		position = Vector3D (100.0, 100.0, 100.0);
		view = Vector3D( 0.0, 0.0, -1.0);
		right = Vector3D (1.0, 0.0, 0.0);
		up = Vector3D (0.0, 1.0, 0.0);

		//Only to be sure:
		XAngle = YAngle = ZAngle = 0.0;
	}

	Camera::Camera(
		Vector3D const & pView,
		Vector3D const & pRight,
		Vector3D const & pUp,
		Vector3D const & pPosition,
		Real pXAngle, 
		Real pYAngle, 
		Real pZAngle
	):
		view(pView),
		right(pRight),
		up(pUp),
		position(pPosition),
		XAngle(pXAngle),
		YAngle(pYAngle),
		ZAngle(pZAngle)
	{
		
	}
		
	Camera Camera::fromViewRightUpPositionXYZAngles(
		Vector3D const & view,
		Vector3D const & right,
		Vector3D const & up,
		Vector3D const & position,
		Real XAngle, 
		Real YAngle, 
		Real ZAngle
	)
	{
		return Camera(view, right, up, position, XAngle, YAngle, ZAngle);
	}
		
	void Camera::move (Vector3D const & direction)
	{
		position.add(direction);
	}

	void Camera::rotateX (Real angle)
	{
		XAngle += angle;
		
		//Rotate viewdir around the right vector:
		Vector3D tmp = 
			Vector3D::add(
				Vector3D::mult(view, Math<Real>::cos(angle)),
				Vector3D::mult(up, Math<Real>::sin(angle))
			);
			
		view = Vector3D::norm(tmp);

		//now compute the new up (by cross product)
		up = Vector3D::mult(Vector3D::cross(view, right), -1.0);		
	}

	void Camera::rotateY (Real angle)
	{
		YAngle += angle;
		
		//Rotate viewdir around the up vector:
		Vector3D tmp =
			Vector3D::add(
				Vector3D::mult(view, Math<Real>::cos(angle)),
				Vector3D::mult(right, -Math<Real>::sin(angle))
			);
			
		view = Vector3D::norm(tmp);

		//now compute the new right (by cross product)
		right = Vector3D::cross(view, up);
	}

	void Camera::rotateZ (Real angle)
	{
		ZAngle += angle;
		
		//Rotate viewdir around the right vector:
		Vector3D tmp = 
			Vector3D::add(
				Vector3D::mult(right, Math<Real>::cos(angle)),
				Vector3D::mult(up, Math<Real>::sin(angle))
			);
		right = Vector3D::norm(tmp);

		//now compute the new up (by cross product)
		up = Vector3D::mult(Vector3D::cross(view, right), -1.0);
	}

	void Camera::render()
	{

		//The point at which the camera looks:
		Vector3D ViewPoint = Vector3D::add(position, view);

		//as we know the up vector, we can easily use gluLookAt:
		gluLookAt(	position.getX(),position.getY(),position.getZ(),
					ViewPoint.getX(),ViewPoint.getY(),ViewPoint.getZ(),
					up.getX(),up.getY(),up.getZ());

	}

	void Camera::moveForward(Real distance)
	{
		position.add(Vector3D::mult(view, -distance));
	}

	void Camera::strafeRight (Real distance)
	{
		position.add(Vector3D::mult(right, distance));
	}

	void Camera::moveUpward(Real distance)
	{
		position.add(Vector3D::mult(up, distance));
	}
}