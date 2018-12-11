#include "main.h"
#include "app.hpp"
#include "HC/ethane.hpp"

void opcontrol() {
  // flywheel.setTargetVel(IDLE_VEL, [](int i){});
  //
  // pros::Task maintainVel(hc::ethane::maintain, &flywheel);

	while (true) {

		RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
		LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

		if(master.get_digital(DIGITAL_A)) {
      // flywheel.setTargetVel(95, [](int i){
      //   master.rumble(".");
      // });
      FLYWHEEL_SET(127);
    } else {
      // flywheel.setTargetVel(IDLE_VEL, [](int i){});
      FLYWHEEL_SET(0);

    }

    // FLYWHEEL_SET(master.get_digital(DIGITAL_B) ? 127 : 0);

		pros::delay(20);
	}
}
