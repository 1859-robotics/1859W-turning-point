#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"



void autonomous() {
  pros::Task track(hc::benzene::track, &posTracker);
  robot.moveAlong(new hc::benzene::Point[3]{{2, 2}, {3, 2}, {4, 2}}, 3, 45);

}
