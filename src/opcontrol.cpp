#include "main.h"
#include "app.hpp"

void opcontrol() {
	while (true) {

		RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
		LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

    bool autonOverwrite = false;

		if(master.get_digital(DIGITAL_A)) {
      FLYWHEEL_SET(127);
      if(FLYWHEEL_GET_VEL > FLYWHEEL_START_B_MID) {
        master.rumble(".");
        robot.feedBall();
        FLYWHEEL_SET(FLYWHEEL_IDLE);
        autonOverwrite = true;
      }
    } else if(master.get_digital(DIGITAL_B)) {
      FLYWHEEL_SET(127);
      if(FLYWHEEL_GET_VEL > FLYWHEEL_START_B_HIGH) {
        master.rumble(".");
        robot.feedBall();
        FLYWHEEL_SET(FLYWHEEL_IDLE);
        autonOverwrite = true;
      }
    } else if(master.get_digital(DIGITAL_Y)) {
      FLYWHEEL_SET(127);
      if(FLYWHEEL_GET_VEL > 300) {
        master.rumble(".");
        robot.feedBall();
        FLYWHEEL_SET(FLYWHEEL_IDLE);
        autonOverwrite = true;
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


		pros::delay(20);
	}
}
