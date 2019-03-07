#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"
#include "./auton/def.hpp"

#include "runAuton"

void autonomous() {
  pros::Task track(w::odom::track, &posTracker);

  // posTracker.setPos({ 0, 0 }, 180); //sets the starting position of the robot
  // robot.turnToFace(90);
  // robot.moveFor(30);
  // robot.turnToFace(180);

  #include "./auton/skills-NEW.auton"
  //#include "./auton/test2.auton"
  // runAuton();

  while(true) { pros::delay(20); }
}
