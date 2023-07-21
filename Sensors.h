#ifndef SENSORS_H
#define SENSORS_H

#include <vector>
#include "LineSegment.h"

namespace smrtsw {
	
	class Sensors {
	public:
		Sensors();
		Sensors(int numberOfLineSegments, ngn::Real length);
		
	private:
		std::vector<ngn::LineSegment> lineSegments;
	};
}

#endif // SENSORS_H