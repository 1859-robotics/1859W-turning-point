#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"
#include "./auton/def.hpp"

#include "runAuton"

void autonomous() {
  pros::Task track(w::odom::track, &posTracker);

  //#include "./auton/skills-20.auton"
  //#include "./auton/test2.auton"
  runAuton();

  while(true) { pros::delay(20); }
}
