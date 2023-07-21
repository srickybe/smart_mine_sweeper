#ifndef DEFAULT_STEERING_FUNCTION_H
#define DEFAULT_STEERING_FUNCTION_H

#include "SteeringFunction.h"

namespace smrtsw {
	
	class SmartMineSweeper;
	
	class DefaultSteeringFunction: public SteeringFunction {
	public:
		DefaultSteeringFunction();
		
		void steer(SmartMineSweeper & sweeper);
	};
}

#endif // DEFAULT_STEERING_FUNCTION_H