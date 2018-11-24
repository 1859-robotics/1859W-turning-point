#include "main.h"
#include "app.hpp"



void autonomous() {
  pros::Task track(hc::benzene::track, &posTracker);
}
