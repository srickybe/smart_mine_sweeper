#ifndef STEERING_FUNCTION_H
#define STEERING_FUNCTION_H

#include <memory>

namespace smrtsw {
	
	class SmartMineSweeper;
	
	class SteeringFunction {
	public:
		virtual void steer(SmartMineSweeper & sweeper) = 0;
	};
	
	typedef std::shared_ptr<SteeringFunction> SharedPtrSteeringFunction;
}

#endif // STEERING_FUNCTION_H