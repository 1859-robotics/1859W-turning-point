#include "main.h"
#include "app.hpp"

void opcontrol() {
	while (true) {

		RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
		LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

    bool autonOverwrite = false;

		if(master.get_digital(DIGITAL_A)) {
      FLYWHEEL_SET(127);
      if(FLYWHEEL_GET_VEL > 410) {
        master.rumble(".");
        robot.feedBall();
        FLYWHEEL_SET(60);
        autonOverwrite = true;
      }
    } else if(master.get_digital(DIGITAL_B)) {
      FLYWHEEL_SET(127);
      if(FLYWHEEL_GET_VEL > 300) {
        master.rumble(".");
        robot.feedBall();
        FLYWHEEL_SET(60);
        autonOverwrite = true;
      }
    } else if(master.get_digital(DIGITAL_Y)) {
      FLYWHEEL_SET(127);
      if(FLYWHEEL_GET_VEL > 300) {
        master.rumble(".");
        robot.feedBall();
        FLYWHEEL_SET(60);
        autonOverwrite = true;
      }
    } else {
      // if(FLYWHEEL_GET_VEL < 257)
        FLYWHEEL_SET(60);
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
