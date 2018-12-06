#include "main.h"
#include "app.hpp"

void opcontrol() {
  flywheel.setTargetVel(60, [](int i){});

  pros::Task maintainVel(hc::ethane::maintain, &flywheel);

	while (true) {

		RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
		LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

		if(master.get_digital(DIGITAL_A)) {
      flywheel.setTargetVel(90, [](int i){
        master.rumble(".");
      });
    } else {
      flywheel.setTargetVel(40, [](int i){});
    }

    FLYWHEEL_SET(master.get_digital(DIGITAL_B) ? 127 : 0);

    std::cout << "right Motor Temperature: " << flywheelR.get_temperature() << std::endl;
    std::cout << "left Motor Temperature: " << flywheelR.get_temperature() << std::endl;

    std::cout << std::endl;

		pros::delay(20);
	}
}
