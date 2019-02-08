#ifndef PID_HPP
#define PID_HPP

#include "main.h"
#include <functional>

#define SGN(in) (in == 0 ? 0 : (in > 0 ? 1 : -1))

#define MIN_SPEED 20
#define MAX_SPEED 127

namespace w {
  namespace pid {
    typedef struct {
      float kP;
      float kI;
      float kD;
      float maxSpeed = MAX_SPEED;
      float minSpeed = MIN_SPEED;
      float epsilonInner = 0.001;
      float epsilonOuter = 0.001;
    } PIDConfig;

    class PID {
    private:

      float lastValue;
    	std::uint32_t lastTime;
      float lastSetPoint;

      int maxSpeed;
      int minSpeed;
    public:
      float kP;
      float kI;
      float kD;

      float epsilonInner;
      float epsilonOuter;

      float sigma;
      PID(float kP,           float kI,           float kD,
          float epsilonInner, float epsilonOuter,
          int maxSpeed = MAX_SPEED,       int minSpeed = MIN_SPEED) :
          kP(kP),             kI(kI),             kD(kD),
          epsilonInner(epsilonInner),             epsilonOuter(epsilonOuter),
          sigma(0),           lastTime(pros::millis()), lastValue(0),
          maxSpeed(maxSpeed), minSpeed(minSpeed) {};

      PID(PIDConfig config,
          float epsilonInner, float epsilonOuter) :
          kP(config.kP),             kI(config.kI),             kD(config.kD),
          epsilonInner(epsilonInner),             epsilonOuter(epsilonOuter),
          sigma(0),           lastTime(pros::millis()), lastValue(0),
          maxSpeed(config.maxSpeed), minSpeed(config.minSpeed) {};

      void config(float kP, float kI, float kD, float epsilonInner, float epsilonOuter, int maxSpeed, int minSpeed);
      void config(::w::pid::PIDConfig config);
      void doPID(float target, float tolerance, std::function <float()> current, std::function <void(float)> action, float kp = 3, float ki = 0, float kd = 0.15, float epsilonInner = 3, float epsilonOuter = 30, int maxSpeed = MAX_SPEED, int minSpeed = MIN_SPEED);
      void debug(std::string name);
      void reset();
      PID *clone() { return new PID(*this); }
      float calculate(float target, float current);
    };

    pid::PID *deepCopy(::w::pid::PID *pid);
  }
}

#endif
