#include "main.h"
#include "app.hpp"

static lv_res_t list_action(lv_obj_t *ddlist) {
  uint8_t id = lv_obj_get_free_num(ddlist);

  std::cout << id << std::endl;

  char sel_str[32];
  lv_ddlist_get_selected_str(ddlist, sel_str);

  hc::pentane::selectedAuton = sel_str;

  std::cout << sel_str << std::endl;
  return LV_RES_OK;
}


void init() {
  flywheelL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  flywheelR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  posTracker.reset();
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void initialize() {
  init();
  hc::pentane::drawFeild();
  hc::pentane::init();

  static lv_style_t list_style;
  lv_style_copy(&list_style, &lv_style_plain);
  list_style.body.radius = 0;

  lv_obj_set_style(hc::pentane::list, &list_style);
  lv_obj_set_pos(hc::pentane::list, 260, 20);
  lv_ddlist_set_action(hc::pentane::list, list_action);

  hc::pentane::drawTiles([=](int output) {
    hc::pentane::selectedTile = output;
  });
}

void disabled() {}

void competition_initialize() {
  init();
}
