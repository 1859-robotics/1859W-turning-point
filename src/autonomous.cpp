#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"



void autonomous() {
  robot.reset();
  posTracker.setPos({ 60, 9 }, 0);
  pros::Task track(hc::benzene::track, &posTracker);
  robot.moveTo({ 69, 18 }, 0);

  robot.turnToFace({ 60, 9 });


  // robot.moveTo({ 0, 36 }, 0);
  // ::hc::pentane::alert("end auton");
}
