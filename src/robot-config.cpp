#include "robot-config.hpp"

pros::Controller master = pros::Controller (CONTROLLER_MASTER);

pros::Motor leftDrive = pros::Motor(LEFT_DRIVE_PORT);
pros::Motor rightDrive = pros::Motor(RIGHT_DRIVE_PORT);

pros::ADIEncoder lTrackerWheel = pros::ADIEncoder(TRACKER_LEFT_PORT, TRACKER_LEFT_PORT + 1);
pros::ADIEncoder rTrackerWheel = pros::ADIEncoder(TRACKER_RIGHT_PORT, TRACKER_RIGHT_PORT + 1);
pros::ADIEncoder cTrackerWheel = pros::ADIEncoder(TRACKER_CENTER_PORT, TRACKER_CENTER_PORT + 1);

pros::ADIGyro gyro = pros::ADIGyro(GYRO_PORT);

hc::propene::PID rPID = hc::propene::PID(5.2, 0.0, 0.10, 3.0, 30.0, MIN_SPEED, MAX_SPEED);
hc::propene::PID tPID = hc::propene::PID(1.5, 0.0, 0.25, 3.0, 30.0, MIN_SPEED, MAX_SPEED);
hc::benzene::Tracker posTracker = hc::benzene::Tracker(&lTrackerWheel, &rTrackerWheel, &cTrackerWheel, &gyro);
hc::methane::Robot robot = hc::methane::Robot(&posTracker, &rPID, &tPID);
