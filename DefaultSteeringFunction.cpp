#include "DefaultSteeringFunction.h"
#include "Math.h"
#include "Real.h"
#include "SmartMineSweeper.h"
#include "Vector2D.h"

namespace smrtsw {
	
	DefaultSteeringFunction::DefaultSteeringFunction(){}
	
	void DefaultSteeringFunction::steer(SmartMineSweeper & sweeper) {
		if (sweeper.getClosestMine() != nullptr) {
			Vector3D heading = sweeper.heading();
			sweeper.computeAndSetClosestMineDirection();

			//Vector inputs(4);
			//inputs.setElem(0, getClosestMineDirection()->getX());
			//inputs.setElem(1, getClosestMineDirection()->getY());
			//inputs.setElem(2, heading.getX());
			//inputs.setElem(3, heading.getY());
			
			Vector inputs(1);
			Vector2D v1(
				sweeper.getClosestMineDirection()->getX(), 
				sweeper.getClosestMineDirection()->getY()
			);
			Vector2D v2(heading.getX(), heading.getY());
			Real deltaAngle = (v1.angle() - v2.angle()) / (Math<Real>::PI);
			inputs.setElem(0, deltaAngle);

			Vector outputs = sweeper.processSteeringInputs(inputs);
			sweeper.applySteeringOutputs(outputs);
		}
	}
}