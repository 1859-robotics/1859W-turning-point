#include "propene.hpp"

namespace hc {
  void propene::PID::debug(std::string name) {
    std::cout << "PID: " << name << std::endl <<
      "kP: " << kP <<
    ", kI: " << kI <<
    ", kD: " << kD <<
    ", lastValue: " << lastValue <<
    ", lastSetPoint: " << lastSetPoint << std::endl << std::endl;
  }

  float propene::PID::calculate(float current, float target) {
    float deltaTime = (float)(pros::millis() - lastTime) / 1000.0;
  	lastTime = pros::millis();

  	float deltaPV = 0;

  	if(deltaTime > 0) {
      deltaPV = (current - lastValue) / deltaTime;
    }

  	lastValue = current;
  	if(deltaTime > 0)
  		deltaPV = (current - lastValue) / deltaTime;

    lastValue = current;
  	float error = target - current;
  	if(fabs(error) > epsilonInner && fabs(error) < epsilonOuter) {
      sigma += error * deltaTime;
    }

  	if (fabs(error) > epsilonOuter) {
      sigma = 0;
    }

  	float output = error *     kP +
                   sigma *  kI -
                   deltaPV *   kD;

    // if the output is larger or smaller than the
    // maximum or minimum speed set the output to that speed
  	return fabs(output) > maxSpeed ? maxSpeed * SGN(output) :
           fabs(output) < minSpeed ? minSpeed * SGN(output) : output;
  }
}
