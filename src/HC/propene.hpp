#ifndef PROPENE_HPP
#define PROPENE_HPP

#include "main.h"
#include <functional>

#define SGN(in) (in == 0 ? 0 : (in > 0 ? 1 : -1))

#define MIN_SPEED 10
#define MAX_SPEED 127

namespace hc {
  namespace propene {
    class PID {
    private:
      float kP;
    	float kI;
    	float kD;

      float epsilonInner;
    	float epsilonOuter;

      float sigma;

      float lastValue;
    	std::uint32_t lastTime;
      float lastSetPoint;

      int maxSpeed;
      int minSpeed;
    public:
      PID(float kP,           float kI,           float kD,
          float epsilonInner, float epsilonOuter,
          int maxSpeed,       int minSpeed) :
          kP(kP),             kI(kI),             kD(kD),
          epsilonInner(epsilonInner),             epsilonOuter(epsilonOuter),
          sigma(0),           lastTime(pros::millis()), lastValue(0),
          maxSpeed(maxSpeed), minSpeed(minSpeed) {};

      void config(float kP, float kI, float kD, float epsilonInner, float epsilonOuter, int maxSpeed, int minSpeed);
      void doPID(float target, float tolerance, std::function <float()> current, std::function <void(float)> action, float kp = 3, float ki = 0, float kd = 0.15, float epsilonInner = 3, float epsilonOuter = 30, int maxSpeed = MAX_SPEED, int minSpeed = MIN_SPEED);
      void debug(std::string name);
      float calculate(float target, float current);
    };

  }
}

#endif
