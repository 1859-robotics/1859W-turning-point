#include "main.h"
#include "app.hpp"

void opcontrol() {
	while (true) {

		RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
		LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

		if(master.get_digital(DIGITAL_A)) {
      FLYWHEEL_SET_VEL(430);
    } else if(master.get_digital(DIGITAL_B)) {
      FLYWHEEL_SET_VEL(405);
    } else {
      if(FLYWHEEL_GET_VEL < 257)
        FLYWHEEL_SET_VEL(257);
    }

    if(master.get_digital(DIGITAL_UP)) {
      INTAKE_SET(127);
    } else {
      INTAKE_SET(0);
    }

		pros::delay(20);
	}
}
