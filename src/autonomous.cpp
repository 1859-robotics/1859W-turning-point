#include "main.h"
#include "robot-config.hpp"

void autonomous() {
  pros::Task posTracker(odom::trackTask, tracker);
  Logger posLogger(LV_ALIGN_CENTER, "tracker");

  tracker->reset();
  tracker->setPos(0, 0, TORAD(90));

  robot.reset();

  robot.moveToTest({ 9, 9 }, 5);

  while(true) {
    posLogger.log(("(" + std::to_string(round(tracker->getPos().pos.x)) + ","
                       + std::to_string(round(tracker->getPos().pos.y)) + ")  | " +
                         std::to_string(round(TODEG(tracker->getPos().a)))));
  }
}
