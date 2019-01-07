#include "main.h"
#include "app.hpp"
#include "HC/methane.hpp"

void opcontrol() {
  robot.reset();
  // posTracker.setPos({ 60, 9 }, 0);

  pros::Task track(hc::benzene::track, &posTracker);
    lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, ("("
      + std::to_string(posTracker.x) + ", "
      + std::to_string(posTracker.y) + ")  |  "
      + std::to_string(posTracker.a)).c_str());
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

	while (true) {
		RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
		LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));
    lv_label_set_text(label, ("("
      + std::to_string(posTracker.x) + ", "
      + std::to_string(posTracker.y) + ")  |  "
      + std::to_string(posTracker.a)).c_str());

    if(master.get_digital(DIGITAL_UP)) {
      robot.turnToFace({ 0, 0 });
    }

    bool autonOverwrite = false;

		if(master.get_digital(DIGITAL_A)) {
      FLYWHEEL_SET(127);
      if(withinRange(FLYWHEEL_START_B_MID, FLYWHEEL_GET_VEL, FLYWHEEL_ERR)) {
        master.rumble(".");
        robot.feedBall();
        FLYWHEEL_SET(FLYWHEEL_IDLE);
        autonOverwrite = true;
      }
    } else if(master.get_digital(DIGITAL_B)) {
      FLYWHEEL_SET(127);
      if(withinRange(FLYWHEEL_START_B_HIGH, FLYWHEEL_GET_VEL, FLYWHEEL_ERR)) {
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
