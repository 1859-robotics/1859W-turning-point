#ifndef PORT_SETUP_HPP
#define PORT_SETUP_HPP

// util macros:


// includes
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

// robot config
#define RIGHT_DRIVE_SET(spd) rightDrive.move(spd)
#define LEFT_DRIVE_SET(spd) leftDrive.move(spd)

#include "HC/benzene.hpp"
#include "HC/propene.hpp"
#include "HC/methane.hpp"

// abstractions
extern hc::benzene::Tracker posTracker;
extern hc::methane::Robot robot;
extern hc::propane::rPID;
extern hc::propane::tPID;


#endif
