//***************************************************************************
//
// Advanced CodeColony Camera
// Philipp Crocoll, 2003
//
//***************************************************************************


#include <GL/glu.h>		// Need to include it here because the GL* types are required
#include "Vector3D.h"

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

namespace ngn {
	
	class Camera {	
	public:
		static Camera fromViewRightUpPositionXYZAngles(
			Vector3D const & view,
			Vector3D const & right,
			Vector3D const & up,
			Vector3D const & position,
			Real XAngle, 
			Real YAngle, 
			Real ZAngle
		);
		
		Camera();				//inits the values (position: (0|0|0) Target: (0|0|-1) )
		Camera(
			Vector3D const & view,
			Vector3D const & right,
			Vector3D const & up,
			Vector3D const & position,
			Real XAngle, 
			Real YAngle, 
			Real ZAngle
		);
		void render ();	//executes some glRotates and a glTranslate command
								//Note: You should call glLoadIdentity before using Render

		void move (Vector3D const & direction);
		void rotateX (Real angle);
		void rotateY (Real angle);
		void rotateZ (Real angle);

		void moveForward (Real distance);
		void moveUpward (Real distance);
		void strafeRight (Real distance);
		
	private:
		Vector3D view;
		Vector3D right;	
		Vector3D up;
		Vector3D position;

		Real XAngle, YAngle, ZAngle;
	};
}

