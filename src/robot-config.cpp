#include "robot-config.hpp"

pros::Controller master = pros::Controller (CONTROLLER_MASTER);

pros::Motor leftDrive = pros::Motor(LEFT_DRIVE_PORT, E_MOTOR_GEARSET_18);
pros::Motor rightDrive = pros::Motor(RIGHT_DRIVE_PORT, E_MOTOR_GEARSET_18, 1);

pros::Motor flywheelR = pros::Motor(RIGHT_FLYWHEEL_PORT, E_MOTOR_GEARSET_06);
pros::Motor flywheelL = pros::Motor(LEFT_FLYWHEEL_PORT, E_MOTOR_GEARSET_06, 1);

pros::ADIEncoder lTrackerWheel = pros::ADIEncoder(TRACKER_LEFT_PORT, TRACKER_LEFT_PORT + 1);
pros::ADIEncoder rTrackerWheel = pros::ADIEncoder(TRACKER_RIGHT_PORT, TRACKER_RIGHT_PORT + 1);
pros::ADIEncoder cTrackerWheel = pros::ADIEncoder(TRACKER_CENTER_PORT, TRACKER_CENTER_PORT + 1);

hc::propene::PID mainPID = hc::propene::PID(3.0, 0.0, 0.15, 3.0, 30.0, MAX_SPEED, MIN_SPEED);
hc::benzene::Tracker posTracker = hc::benzene::Tracker(&lTrackerWheel, &rTrackerWheel, &cTrackerWheel);
