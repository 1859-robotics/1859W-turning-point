#include "main.h"
#include "app.hpp"

void opcontrol() {
  flywheel.setTargetVel(200, [](int i){});

  pros::Task maintainVel(hc::ethane::maintain, &flywheel);

	while (true) {

		RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
		LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

		FLYWHEEL_SET(master.get_digital(DIGITAL_A) ? 127 : 0);

    std::cout << "right Motor Temperature: " << flywheelR.get_temperature() << std::endl;
    std::cout << "left Motor Temperature: " << flywheelR.get_temperature() << std::endl;

    std::cout << std::endl;

		pros::delay(20);
	}
}
