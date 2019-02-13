#include "pid.hpp"

namespace w {
  void pid::PID::debug(std::string name) {
    std::cout << "PID: " << name << std::endl <<
      "kP: " << kP <<
    ", kI: " << kI <<
    ", kD: " << kD <<
    ", lastValue: " << lastValue <<
    ", lastSetPoint: " << lastSetPoint << std::endl << std::endl;
  }

  void pid::PID::reset() {
    lastValue = 0;
    lastTime = pros::millis();
    lastSetPoint = 0;
  }

  float pid::PID::calculate(float current, float target) {
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

  	float output = error *   kP +
                   sigma *   kI -
                   deltaPV * kD;
    // if the output is larger or smaller than the
    // maximum or minimum speed set the output to that speed
    output = ((fabs(output) > maxSpeed) ? (maxSpeed * SGN(output)) :
             ((fabs(output) < minSpeed) ? (minSpeed * SGN(output)) : output));
  	return output;
  }

  void pid::PID::config(float kP,           float kI,           float kD,
              float epsilonInner, float epsilonOuter,
              int maxSpeed = MAX_SPEED, int minSpeed = MIN_SPEED) {
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
    this->epsilonInner = epsilonInner;
    this->epsilonOuter = epsilonOuter;
    this->maxSpeed = maxSpeed;
    this->minSpeed = minSpeed;
  }

  void pid::PID::config(::w::pid::PIDConfig config) {
    this->kP = config.kP;
    this->kI = config.kI;
    this->kD = config.kD;
    this->epsilonInner = config.epsilonInner;
    this->epsilonOuter = config.epsilonOuter;
    this->maxSpeed = config.maxSpeed;
    this->minSpeed = config.minSpeed;
  }

  void pid::PID::doPID(float target, float tolerance, std::function <float()> current, std::function <void(float)> action, float kp, float ki, float kd, float epsilonInner, float epsilonOuter, int maxSpeed, int minSpeed) {
    //config(kp, ki, kd, epsilonInner, epsilonOuter, maxSpeed, minSpeed);

    bool atTargetPoint = false;
    float atTargetTime = pros::millis();
    float timer = pros::millis();
    float currentVal = current();
    while(!atTargetPoint) {
      timer = pros::millis();
      currentVal = current();
      // std::cout << currentVal << std::endl;

      float output = calculate(currentVal, target);
      action(output);

      if(fabs(target - currentVal) > tolerance) {
        atTargetTime = pros::millis();
      }
      if(pros::millis() - atTargetTime > 200) {
        atTargetPoint = true;
      }
    }
  }
}
