#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"
#include "./auton/def.hpp"

#include "runAuton"
  
void autonomous() {
  pros::Task track(w::odom::track, &posTracker);

    #include "./auton/red-near-0.auton"
    // runAuton();

  std::cout << "end" << std::endl;

  while(true) { pros::delay(20); }
}
