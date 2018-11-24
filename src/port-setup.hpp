#ifndef PORT_SETUP_HPP
#define PORT_SETUP_HPP

#include "main.h"

// port defines
#define LEFT_DRIVE_PORT 1
#define RIGHT_DRIVE_PORT 10

#define TRACKER_LEFT_PORT 1
#define TRACKER_RIGHT_PORT 3
#define TRACKER_CENTER_PORT 5
#define GYRO_PORT 8

// components
extern pros::Controller master;

extern pros::Motor leftDrive;
extern pros::Motor rightDrive;

extern pros::ADIEncoder lTrackerWheel;
extern pros::ADIEncoder rTrackerWheel;
extern pros::ADIEncoder cTrackerWheel;
extern pros::ADIGyro gyro;

#endif
