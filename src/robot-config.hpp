#ifndef PORT_SETUP_HPP
#define PORT_SETUP_HPP

// includes
#include "main.h"

// port defines
#define LEFT_DRIVE_PORT 11
#define RIGHT_DRIVE_PORT 12

#define LEFT_FLYWHEEL_PORT 2
#define RIGHT_FLYWHEEL_PORT 1
#define INTAKE_PORT 10
#define COMBINE_PORT 9
#define NONO_PORT 20

#define TRACKER_LEFT_PORT 5
#define TRACKER_RIGHT_PORT 7
#define TRACKER_CENTER_PORT 3

#define LIMIT_PORT 1

// components

extern pros::Controller master;

extern pros::Motor leftDrive;
extern pros::Motor rightDrive;
extern pros::Motor flywheelL;
extern pros::Motor flywheelR;

extern pros::Motor intake;
extern pros::Motor combine;
extern pros::Motor nono;

extern pros::ADIEncoder lTrackerWheel;
extern pros::ADIEncoder rTrackerWheel;
extern pros::ADIEncoder cTrackerWheel;

extern pros::ADIDigitalIn limit;

// robot config macros
#define RIGHT_DRIVE_SET(spd) rightDrive.move(spd)
#define LEFT_DRIVE_SET(spd) leftDrive.move(spd)

#define FLYWHEEL_SET(spd) flywheelL.move(spd); flywheelR.move(spd)
#define FLYWHEEL_SET_VEL(spd) flywheelL.move_velocity(spd); flywheelR.move_velocity(spd)

#define FLYWHEEL_GET_VEL (flywheelR.get_actual_velocity() + flywheelL.get_actual_velocity()) / 2

#define INTAKE_SET(spd) intake.move(spd)
#define COMBINE_SET(spd) combine.move(spd)
#define NONO_SET(spd) nono.move(spd)

// flywheel stuff
#define FLYWHEEL_IDLE 60
#define FLYWHEEL_ERR 30
#define FLYWHEEL_START_B_HIGH 390
#define FLYWHEEL_START_B_MID 410

#define OPCONTROL_FLYWHEEL_SET(speed) FLYWHEEL_SET(20); \
if(withinRange(speed, FLYWHEEL_GET_VEL, FLYWHEEL_ERR)) { \
  master.rumble("."); \
  INTAKE_SET(127); \
  FLYWHEEL_SET(FLYWHEEL_IDLE); \
  autonOverwrite = true; \
} else if(FLYWHEEL_GET_VEL < speed) { \
  FLYWHEEL_SET(127); \
} \


#include "HC/benzene.hpp"
#include "HC/propene.hpp"
// #include "HC/methane.hpp"

// abstractions
extern hc::benzene::Tracker posTracker;
extern hc::propene::PID mainPID;

#endif
