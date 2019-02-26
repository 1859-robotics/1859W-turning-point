#include "robot-config.hpp"

pros::Controller master = pros::Controller (CONTROLLER_MASTER);
pros::Controller partner = pros::Controller (pros::E_CONTROLLER_PARTNER);

pros::Motor leftDriveB = pros::Motor(LEFT_DRIVE_BACK_PORT, pros::E_MOTOR_GEARSET_18);
pros::Motor rightDriveB = pros::Motor(RIGHT_DRIVE_BACK_PORT, pros::E_MOTOR_GEARSET_18, -1);
pros::Motor leftDriveF = pros::Motor(LEFT_DRIVE_FRONT_PORT, pros::E_MOTOR_GEARSET_18);
pros::Motor rightDriveF = pros::Motor(RIGHT_DRIVE_FRONT_PORT, pros::E_MOTOR_GEARSET_18, -1);

pros::Motor flywheelR = pros::Motor(RIGHT_FLYWHEEL_PORT, pros::E_MOTOR_GEARSET_06);
pros::Motor flywheelL = pros::Motor(LEFT_FLYWHEEL_PORT, pros::E_MOTOR_GEARSET_06, 1);
pros::Motor intake = pros::Motor(INTAKE_PORT, pros::E_MOTOR_GEARSET_18);
pros::Motor combine = pros::Motor(COMBINE_PORT, pros::E_MOTOR_GEARSET_06);

pros::ADIEncoder lTrackerWheel = pros::ADIEncoder(TRACKER_LEFT_PORT, TRACKER_LEFT_PORT + 1);
pros::ADIEncoder rTrackerWheel = pros::ADIEncoder(TRACKER_RIGHT_PORT, TRACKER_RIGHT_PORT + 1);
pros::ADIEncoder cTrackerWheel = pros::ADIEncoder(TRACKER_CENTER_PORT, TRACKER_CENTER_PORT + 1);

pros::ADIDigitalIn limit = pros::ADIDigitalIn(LIMIT_PORT);

// abstractions
w::pid::PID mainPID = w::pid::PID(2.0, 0.0, 0.15, 3.0, 30.0, MAX_SPEED, MIN_SPEED);
w::odom::Tracker posTracker = w::odom::Tracker(&lTrackerWheel, &rTrackerWheel, &cTrackerWheel);
