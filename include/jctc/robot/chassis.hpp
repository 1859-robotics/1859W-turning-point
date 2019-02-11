#pragma once
#include "main.h"

#include "../odom/position.hpp"
#include "../odom/tracker.hpp"
#include "../pid/pid.hpp"


namespace jctc {
  class Cassis {
  private:
    odom::Tracker tracker;
    PID turnPid;
    PID distPid;

  public:
    Cassis(odom::Tracker tracker, PID turnPid, PID distPid)
      : tracker(tracker), turnPid(turnPid), distPid(distPid) {};

    virtual void driveVector(float trans, float rot);

    void tankSeek(odom::Point); // TODO: implement other seeking algs
    odom::Position getPosition();
  };
}
