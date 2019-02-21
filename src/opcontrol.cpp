#include "main.h"
#include "robot-config.hpp"

static float round(float var) {
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

static bool withinRange(float target, float current, float error) {
  return fabs(target - current) < error;
}

void opcontrol() {
  TASK_WHILE(true, {
    int rV = master.get_analog(ANALOG_RIGHT_Y);
    int lV = master.get_analog(ANALOG_LEFT_Y);

    RIGHT_DRIVE_SET(abs(rV) > 15 ? rV : 0);
    LEFT_DRIVE_SET(abs(lV) > 15 ? lV : 0);

    bool autonOverwrite = false;

    if(master.get_digital(DIGITAL_R2)) {
			COMBINE_SET(0);
		} else {
			robot.combineSet(master.get_digital(DIGITAL_L2));
    }

    if(master.get_digital(DIGITAL_Y)) {
      FLYWHEEL_SET(127);
    } else if(master.get_digital(DIGITAL_B)) {
      OPCONTROL_FLYWHEEL_SET(480);
		} else if(master.get_digital(DIGITAL_A)) {
	    OPCONTROL_FLYWHEEL_SET(370);
    } else if(master.get_digital(DIGITAL_L1)) {
      OPCONTROL_FLYWHEEL_SET(520);
    } else if(master.get_digital(DIGITAL_X)) {
      OPCONTROL_FLYWHEEL_SET(400);
    } else {
      FLYWHEEL_SET(FLYWHEEL_IDLE);
    }

    if(!autonOverwrite) {
      if(master.get_digital(DIGITAL_UP)) {
        INTAKE_SET(-127);
      } else if(master.get_digital(DIGITAL_DOWN) || !limit.get_value()) {
        INTAKE_SET(127);
      } else {
        INTAKE_SET(0);
      }
    }
  })
}
