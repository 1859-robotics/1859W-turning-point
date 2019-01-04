#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"



void autonomous() {
  robot.reset();
  posTracker.setPos({ 60, 9 }, 0);
  pros::Task track(hc::benzene::track, &posTracker);
  // robot.turnToFace(90);

  // robot.turnToFace({1, 1});


  // robot.moveTo({ 0, 36 }, 0);
  // ::hc::pentane::alert("end auton");
}
