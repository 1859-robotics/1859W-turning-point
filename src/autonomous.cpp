#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"



void autonomous() {
  robot.reset();
  pros::Task track(hc::benzene::track, &posTracker);

  #include "auton/red-near.auton"

  //posTracker.setPos({ 0, 0 }, 0);

  //FLYWHEEL_SET(FLYWHEEL_IDLE);

  // robot.moveFor(12);
  //robot.turnToFace(100);
}
