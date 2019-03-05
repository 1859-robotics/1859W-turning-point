#include "main.h"
#include "robot-config.hpp"

void autonomous() {
  robot.reset();
  tracker->reset();
  tracker->setPos(0, 0, TORAD(0));
  pros::delay(500);
  pros::Task posTracker(odom::trackTask, tracker);

  // robot.turnToFace({ 10, 10 });
  // std::cout << "after" << std::endl;

  robot.moveToSimple({ 10, 10 });
  pros::delay(2000);
  robot.moveToSimple({ 10, 10 });

  while(true) {
    pros::delay(20);
  }
}
