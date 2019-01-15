#include "main.h"
#include "app.hpp"
#include "HC/methane.hpp"

void opcontrol() {
  robot.reset();

  pros::Task track(hc::benzene::track, &posTracker);

	while (true) {
		RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
		LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

    bool autonOverwrite = false;

    if(master.get_digital(DIGITAL_X)) {
      FLYWHEEL_SET(127);
    } else if(master.get_digital(DIGITAL_A)) {
      FLYWHEEL_SET(20);
      if(withinRange(FLYWHEEL_START_B_MID, FLYWHEEL_GET_VEL, FLYWHEEL_ERR)) {
        master.rumble(".");
        robot.feedBall();
        FLYWHEEL_SET(FLYWHEEL_IDLE);
        autonOverwrite = true;
      } else if(FLYWHEEL_GET_VEL < FLYWHEEL_START_B_MID) {
        FLYWHEEL_SET(127);
      }
    } else if(master.get_digital(DIGITAL_B)) {
      FLYWHEEL_SET(20);
      if(withinRange(FLYWHEEL_START_B_HIGH, FLYWHEEL_GET_VEL, FLYWHEEL_ERR)) {
        master.rumble(".");
        robot.feedBall();
        FLYWHEEL_SET(FLYWHEEL_IDLE);
        autonOverwrite = true;
      } else if(FLYWHEEL_GET_VEL < FLYWHEEL_START_B_HIGH) {
        FLYWHEEL_SET(127);
      }
    } else if(master.get_digital(DIGITAL_Y)) {
      FLYWHEEL_SET(20);
      if(FLYWHEEL_GET_VEL > 300) {
        master.rumble(".");
        robot.feedBall();
        FLYWHEEL_SET(FLYWHEEL_IDLE);
        autonOverwrite = true;
      } else if(FLYWHEEL_GET_VEL < 300) {
        FLYWHEEL_SET(127);
      }
    } else {
      FLYWHEEL_SET(FLYWHEEL_IDLE);
    }

    if(!autonOverwrite) {
      if(master.get_digital(DIGITAL_R1)) {
        INTAKE_SET(127);
      } else if(master.get_digital(DIGITAL_R2)) {
        INTAKE_SET(-127);
      } else {
        INTAKE_SET(0);
      }
    }

    robot.combineSet(master.get_digital(DIGITAL_L1));


		pros::delay(20);
	}
}
