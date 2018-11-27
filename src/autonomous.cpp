#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"



void autonomous() {
  pros::Task track(hc::benzene::track, &posTracker);
  robot.moveTo({18, 18}, 45);

}
