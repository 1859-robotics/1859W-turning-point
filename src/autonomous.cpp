#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"


void autonomous() {
  robot.reset();
  pros::Task track(hc::benzene::track, &posTracker);

      #include "auton/red-far-1.auton"
}
