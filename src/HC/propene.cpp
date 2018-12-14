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
  	return ((fabs(output) > maxSpeed) ? (maxSpeed * SGN(output)) :
           ((fabs(output) < minSpeed) ? (minSpeed * SGN(output)) : output));
  }

  void propene::PID::config(float kP,           float kI,           float kD,
              float epsilonInner, float epsilonOuter,
              int maxSpeed = MAX_SPEED, int minSpeed = MIN_SPEED) {
    kP = kP;
    kI = kI;
    kD = kD;
    epsilonInner = epsilonInner;
    epsilonOuter = epsilonOuter;
    maxSpeed = maxSpeed;
    minSpeed = minSpeed;
  }

  void propene::PID::doPID(float target, float tolerance, std::function <float()> current, std::function <void(float)> action, float kp, float ki, float kd, float epsilonInner, float epsilonOuter, int maxSpeed, int minSpeed) {
    config(kp, ki, kd, epsilonInner, epsilonOuter, maxSpeed, minSpeed);

    bool atSetPoint = false;
    float atTargetTime = pros::millis();
    float timer = pros::millis();
    float currentVal = current();
    while(!atSetPoint) {
      timer = pros::millis();
      currentVal = current();
      // std::cout << currentVal << std::endl;

      float output = calculate(currentVal, target);
      action(output);

      if(fabs(target - currentVal) > tolerance) {
        atTargetTime = pros::millis();
      }
      if(pros::millis() - atTargetTime > 350) {
        atSetPoint = true;
      }
    }
  }

  propene::PID *deepCopy(::hc::propene::PID *pid) {
    return new propene::PID(pid->kP, pid->kI, pid->kD, pid->epsilonInner, pid->epsilonOuter);
  }
}
