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
  hc::pentane::drawFeild();
  std::cout << "hello from init" << std::endl;
  
  lv_obj_t * hecker = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(hecker, NULL, LV_ALIGN_CENTER, 0, 20);
  hc::pentane::drawTiles([=](int output) {
    lv_label_set_text(hecker, (std::to_string(output)).c_str());
    hc::pentane::selectedTile = output;
  });
}

void disabled() {}

void competition_initialize() {
  init();
}
