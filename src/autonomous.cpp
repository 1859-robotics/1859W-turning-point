#include "main.h"
#include "robot-config.hpp"

void autonomous() {

  pros::Task posTracker(odom::trackTask, tracker);
  tracker->reset();
  tracker->setPos(0, 0, TORAD(90));
  

  robot.moveToTest({ 0, 9 }, TORAD(5));

  while(true) {
    pros::delay(20);
  }
}
