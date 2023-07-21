#include "Sensors.h"
#include "IllegalArgumentException.h"
#include "Math.h"
#include "Vector3D.h"

using namespace ngn;

namespace smrtsw {
	
	Sensors::Sensors() :
		Sensors(5, 25.0)
	{

	}
	
	Sensors::Sensors(int numberOfLineSegments, Real length) {
		if (numberOfLineSegments < 1 || numberOfLineSegments % 2 == 0) {
			throw IllegalArgumentException("bad number of sensors");
		}
		
		lineSegments.resize(numberOfLineSegments);
		Vector3D center(Vector3D::zero());
		Real angle = 0.0;
		
		if (numberOfLineSegments > 1) {
			Real dAngle = Math<Real>::PI / (numberOfLineSegments - 1);
			
			for (int i = 0; i < numberOfLineSegments; ++i) {
				Vector3D direction(
					Math<Real>::cos(angle), 
					Math<Real>::sin(angle),
					0.0
				);
				lineSegments.push_back(LineSegment(center, direction, length));
				angle += dAngle;
			}
		} else {
			Real angle = Math<Real>::PI / 2;
			Vector3D direction(
				Math<Real>::cos(angle), 
				Math<Real>::sin(angle),
				0.0
			);
			lineSegments.push_back(LineSegment(center, direction, length));
		}
	}
}