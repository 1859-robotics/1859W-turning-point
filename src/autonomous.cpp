#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"



void autonomous() {
  robot.reset();
  pros::Task track(hc::benzene::track, &posTracker);

  posTracker.setPos({ 0, 0 }, 0);

  robot.moveFor(12);
  robot.turnToFace(100);
}
