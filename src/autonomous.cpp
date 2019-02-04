#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"
#include "./auton/def.hpp"

#include "runAuton"

void autonomous() {
  robot.reset();
  pros::Task track(w::odom::track, &posTracker);

  #include "./auton/test.auton"
        
              // runAuton();

  std::cout << "end" << std::endl;

  while(true) { pros::delay(20); }
}
