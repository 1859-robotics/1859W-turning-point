#include "main.h"
#include "app.hpp"
#include "w/robot.hpp"

void opcontrol() {
	while (true) {
		RIGHT_DRIVE_SET(master.get_analog(ANALOG_RIGHT_Y));
		LEFT_DRIVE_SET(master.get_analog(ANALOG_LEFT_Y));

    bool autonOverwrite = false;

		//if(master.get_digital(DIGITAL_UP)) {
		//	rightDriveF.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		//	rightDriveB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		//	leftDriveF.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		//	leftDriveB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		//} else {
		//	rightDriveF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		//	rightDriveB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		//	leftDriveF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		//	leftDriveB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		//}

		if(master.get_digital(DIGITAL_R2)) {
			COMBINE_SET(0);
		} else {
			robot.combineSet(master.get_digital(DIGITAL_L1));

	}

    if(master.get_digital(DIGITAL_Y)) {
      FLYWHEEL_SET(127);
    } else if(master.get_digital(DIGITAL_B)) {
      OPCONTROL_FLYWHEEL_SET(480);
		} else if(master.get_digital(DIGITAL_A)) {
	    OPCONTROL_FLYWHEEL_SET(370);
    } else if(master.get_digital(DIGITAL_L2)) {
      OPCONTROL_FLYWHEEL_SET(520);
    } else if(master.get_digital(DIGITAL_A)) {
      OPCONTROL_FLYWHEEL_SET(400);
    } else {
      FLYWHEEL_SET(FLYWHEEL_IDLE);
    }

    if(!autonOverwrite) {
      if(master.get_digital(DIGITAL_R1)) {
        INTAKE_SET(127);
      } else if(master.get_digital(DIGITAL_UP)) {
        INTAKE_SET(-127);
      } else {
        INTAKE_SET(0);
      }
    }


    if(limit.get_value()) {
      master.rumble("-");
    }



		pros::delay(20);
	}
}
