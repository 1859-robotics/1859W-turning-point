#include "main.h"
#include "app.hpp"

void opcontrol() {
  flywheel.setTargetVel(60, [](int i){});

  pros::Task maintainVel(hc::ethane::maintain, &flywheel);

	while (true) {

		RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
		LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

		if(master.get_digital(DIGITAL_A)) {
      flywheel.setTargetVel(100, [](int i){});
    } else {
      flywheel.setTargetVel(60, [](int i){});
    }

    std::cout << "right Motor Temperature: " << flywheelR.get_temperature() << std::endl;
    std::cout << "left Motor Temperature: " << flywheelR.get_temperature() << std::endl;

    std::cout << std::endl;

		pros::delay(20);
	}
}
