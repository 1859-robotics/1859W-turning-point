#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"



void autonomous() {
  robot.reset();
  posTracker.setPos(0, 0, 0);
  pros::Task track(hc::benzene::track, &posTracker);
  // robot.turnToFace(90);
  // robot.turnToFace({1, 1});

  robot.moveTo({ 18, 18 }, 45);
}
