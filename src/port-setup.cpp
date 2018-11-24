#include "port-setup.hpp"

pros::Controller master = pros::Controller (CONTROLLER_MASTER);

pros::Motor leftDrive = pros::Motor(LEFT_DRIVE_PORT);
pros::Motor rightDrive = pros::Motor(RIGHT_DRIVE_PORT);

pros::ADIEncoder lTrackerWheel = pros::ADIEncoder(TRACKER_LEFT_PORT, TRACKER_LEFT_PORT + 1);
pros::ADIEncoder rTrackerWheel = pros::ADIEncoder(TRACKER_RIGHT_PORT, TRACKER_RIGHT_PORT + 1);
pros::ADIEncoder cTrackerWheel = pros::ADIEncoder(TRACKER_CENTER_PORT, TRACKER_CENTER_PORT + 1);

pros::ADIGyro gyro = pros::ADIGyro(GYRO_PORT);
