#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"

void runAuton() {
  if(hc::pentane::selectedAuton == -1) {
    std::cout << "did not run auton" << std::endl;
    return;
  }
  #include "./auton/red-far-1.auton"
}

void autonomous() {
  robot.reset();
  pros::Task track(hc::benzene::track, &posTracker);

  runAuton();
}
