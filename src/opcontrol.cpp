#include "main.h"
#include "robot-config.hpp"
#include <iostream>


static float round(float var) {
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

static bool withinRange(float target, float current, float error) {
  return fabs(target - current) < error;
}

void opcontrol() {
  pros::Task posTracker(odom::trackTask, tracker);
  Logger posLogger(LV_ALIGN_CENTER, "tracker");
  tracker->reset();
  tracker->setPos(0, 0, TORAD(90));

  TASK_WHILE(true, {
    posLogger.log(("(" + std::to_string(round(tracker->getPos().pos.x)) + ","
                       + std::to_string(round(tracker->getPos().pos.y)) + ")  | " +
                         std::to_string(round(TODEG(tracker->getPos().a)))));

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

    if(partner.get_digital(DIGITAL_LEFT) || master.get_digital(DIGITAL_LEFT)) {
			flipover.move(-127);
		} else if(partner.get_digital(DIGITAL_RIGHT) || master.get_digital(DIGITAL_RIGHT)) {
			flipover.move(127);
    } else flipover.move(0);

    LOG_VAR(lTrackerWheel.get_value());
    LOG_VAR(rTrackerWheel.get_value());
    LOG_VAR(cTrackerWheel.get_value());

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
