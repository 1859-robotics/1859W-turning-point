#include "main.h"
#include "robot-config.hpp"


void opcontrol() {
  pros::Task posTracker(odom::trackTask, tracker);

  while(true) {
    RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
    LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

    pros::delay(20);
  }
}
