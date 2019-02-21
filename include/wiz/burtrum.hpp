#pragma once

#include "main.h"
#include <functional>
#include <algorithm>

namespace wiz {
  class Burtrum : public Chassis {
  public:
    Burtrum(odom::Tracker tracker, PID rPID, PID tPID)
      : Chassis(tracker, rPID, tPID) {};
    void reset();
    virtual void driveVector(float forward, float turn) const;
    void flyUp(int rpm, std::function <void(float)> action);
    void combineSet(bool rev);
    void feedBall(float exit = 10000);
    bool hasBall();
  };
}
