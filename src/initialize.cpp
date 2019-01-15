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
  static lv_style_t list_style;
  lv_style_copy(&list_style, &lv_style_plain);
  list_style.body.radius = 0;

  lv_obj_set_style(hc::pentane::list, &list_style);
  lv_obj_set_pos(hc::pentane::list, 260, 20);


  hc::pentane::drawTiles([=](int output) {
    hc::pentane::selectedTile = output;
  });
}

void disabled() {}

void competition_initialize() {
  init();
}
