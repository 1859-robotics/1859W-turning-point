#include "main.h"
#include "hydrocarbon.hpp"

void opcontrol() {
	while (true) {

		leftDrive.move(master.get_analog(ANALOG_LEFT_Y));
		rightDrive.move(master.get_analog(ANALOG_RIGHT_Y));

		pros::delay(20);
	}
}
