#ifndef PROPENE_HPP
#define PROPENE_HPP

#include "main.h"

#define SGN(in) (in == 0 ? 0 : (in > 0 ? 1 : -1))


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

      void debug(std::string name);
      float calculate(float target, float current);
    };

  }
}

#endif
