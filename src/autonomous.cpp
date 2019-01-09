#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"



void autonomous() {
  robot.reset();
  posTracker.setPos({ 60, 9 }, 0);
  pros::Task track(hc::benzene::track, &posTracker);

  robot.moveTo({ 60, 24 }, 0);

  // #include "./auton/first.auton"
}
