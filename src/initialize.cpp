#include "main.h"
#include "app.hpp"

hc::benzene::Tracker tracker(&lTrackerWheel, &rTrackerWheel, &cTrackerWheel, &gyro);

void initialize() {
	tracker.debug();
}

void disabled() {}

void competition_initialize() {}
