#include "main.h"
#include "robot-config.hpp"

float round(float var) {
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

void opcontrol() {
  pros::Task posTracker(odom::trackTask, tracker);
  Logger posLogger(LV_ALIGN_CENTER, "tracker");

  tracker->reset();
  tracker->setPos({ 0, 0, PI / 2 });

  // robot.

  while(true) {
    RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
    LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

    posLogger.log(("(" + std::to_string(round(tracker->getPos().pos.x)) + ","
                       + std::to_string(round(tracker->getPos().pos.y)) + ")  | " +
                         std::to_string(round(TODEG(tracker->getPos().a)))));
    pros::delay(20);
  }
}
