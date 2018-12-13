#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"



void autonomous() {
  robot.reset();

  pros::Task track(hc::benzene::track, &posTracker);

  // robot.moveTo({18, 18}, 45);

}
