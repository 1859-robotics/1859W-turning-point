#include "main.h"
#include "robot-config.hpp"

void autonomous() {
  pros::Task posTracker(odom::trackTask, tracker);

  tracker->reset();
  tracker->setPos({ 0, 0, PI / 2 });

  robot.driveTo({ 9, 9 }, 2.5, 0, 5);
}
