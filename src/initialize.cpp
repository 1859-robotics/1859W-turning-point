#include "main.h"
#include "app.hpp"

void init() {
  flywheelL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  flywheelR.set_brake_mode(E_MOTOR_BRAKE_COAST);
  posTracker.reset();
  intake.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void initialize() {
  init();
}

void disabled() {}

void competition_initialize() {
  init();
}
