#include "main.h"
#include "app.hpp"

void opcontrol() {
	while (true) {

		RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
		LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

		FLYWHEEL_SET(master.get_digital(DIGITAL_A) ? 127 : 0);

		pros::delay(20);
	}
}
