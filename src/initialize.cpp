#include "main.h"
#include "app.hpp"

Tracker tracker(&lTrackerWheel, &rTrackerWheel, &cTrackerWheel, &gyro);

void initialize() {

	tracker.debug();
}

void disabled() {}

void competition_initialize() {}
