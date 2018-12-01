#include "main.h"
#include "app.hpp"

void init() {
  flywheelL.set_brake_mode(E_MOTOR_BRAKE_COAST );
  flywheelR.set_brake_mode(E_MOTOR_BRAKE_COAST );
}

void initialize() {
	posTracker.debug();
  init();
}

void disabled() {}

void competition_initialize() {}
