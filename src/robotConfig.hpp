#pragma once

#include "main.h"
#include "jctc/jctc-lib.hpp"

// ports
#define LEFT_DRIVE_BACK_PORT 11
#define LEFT_DRIVE_FRONT_PORT 2

#define RIGHT_DRIVE_BACK_PORT 20
#define RIGHT_DRIVE_FRONT_PORT 10

#define LEFT_FLYWHEEL_PORT 1
#define RIGHT_FLYWHEEL_PORT 4
#define INTAKE_PORT 3
#define COMBINE_PORT 8

#define TRACKER_LEFT_PORT 5
#define TRACKER_RIGHT_PORT 7
#define TRACKER_CENTER_PORT 3

#define LIMIT_PORT 1

// components

extern pros::Controller master;

extern pros::Motor leftDriveF;
extern pros::Motor rightDriveF;
extern pros::Motor leftDriveB;
extern pros::Motor rightDriveB;

extern pros::Motor flywheelL;
extern pros::Motor flywheelR;

extern pros::Motor intake;
extern pros::Motor combine;

extern pros::ADIEncoder lTrackerWheel;
extern pros::ADIEncoder rTrackerWheel;
extern pros::ADIEncoder cTrackerWheel;

extern pros::ADIDigitalIn limit;

// program
extern odom::Tracker posTracker;
extern PID distPid;
extern PID turnPid;
