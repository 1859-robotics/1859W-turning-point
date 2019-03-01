#include "main.h"
#include "app.hpp"

static lv_res_t list_action(lv_obj_t *ddlist) {
  uint8_t id = lv_obj_get_free_num(ddlist);

  char sel_str[32];
  lv_ddlist_get_selected_str(ddlist, sel_str);

  w::auton_selector::selectedAuton = sel_str;

  return LV_RES_OK;
}


void init() {
  posTracker.reset();

  flywheelL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  flywheelR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  flipover.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	rightDriveF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightDriveB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	leftDriveF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	leftDriveB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  // leftDriveF.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  // leftDriveB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  // rightDriveF.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  // rightDriveB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

}

void initialize() {
  init();
  w::auton_selector::drawFeild();
  w::auton_selector::init();

  static lv_style_t list_style;
  lv_style_copy(&list_style, &lv_style_plain);
  list_style.body.radius = 0;

  lv_obj_set_style(w::auton_selector::list, &list_style);
  lv_obj_set_pos(w::auton_selector::list, 260, 20);
  lv_ddlist_set_action(w::auton_selector::list, list_action);

  w::auton_selector::drawTiles([=](int output) {
    w::auton_selector::selectedTile = output;
  });
}

void disabled() {}

void competition_initialize() {
  init();
}
