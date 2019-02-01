#ifndef PORT_SETUP_HPP
#define PORT_SETUP_HPP

// includes
#include "main.h"

// port defines

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

// robot config macros
#define RIGHT_DRIVE_SET(spd) rightDriveF.move(spd); rightDriveB.move(spd)
#define LEFT_DRIVE_SET(spd) leftDriveF.move(spd); leftDriveB.move(spd)

#define RIGHT_DRIVE_SET_AUTO(spd) rightDriveF.move(spd);
#define LEFT_DRIVE_SET_AUTO(spd) leftDriveF.move(spd);

#define FLYWHEEL_SET(spd) flywheelL.move(spd); flywheelR.move(spd)
#define FLYWHEEL_SET_VEL(spd) flywheelL.move_velocity(spd); flywheelR.move_velocity(spd)

#define FLYWHEEL_GET_VEL (flywheelR.get_actual_velocity() + flywheelL.get_actual_velocity()) / 2

#define INTAKE_SET(spd) intake.move(spd)
#define COMBINE_SET(spd) combine.move(spd)

// flywheel stuff
#define FLYWHEEL_IDLE 80
#define FLYWHEEL_ERR 30
#define FLYWHEEL_START_B_HIGH 390
#define FLYWHEEL_START_B_MID 410

#define OPCONTROL_FLYWHEEL_SET(speed) if(withinRange(speed, FLYWHEEL_GET_VEL, FLYWHEEL_ERR)) { \
  master.rumble("."); \
  INTAKE_SET(127); \
  FLYWHEEL_SET(FLYWHEEL_IDLE); \
  autonOverwrite = true; \
} else if(FLYWHEEL_GET_VEL < speed) { \
  FLYWHEEL_SET(127); \
} else if(FLYWHEEL_GET_VEL > speed) { \
  FLYWHEEL_SET(0); \
}


#include "HC/odom.hpp"
#include "HC/pid.hpp"
// #include "HC/robot.hpp"

// abstractions
extern w::odom::Tracker posTracker;
extern w::pid::PID mainPID;

#endif
