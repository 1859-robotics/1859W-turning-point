#include "pentane.hpp"

#define AUTON_OPTIONS_RED_A "shoot\n" \
                            "shoot & climb\n"

namespace hc {
  int pentane::selectedAuton = -1;
  int pentane::selectedTile = -1;
  void pentane::drawFeild() {
    std::cout << "hi" << std::endl;
    // draw feild base
    lv_obj_t * feildContainer;

    static lv_style_t feildBase;
    lv_style_copy(&feildBase, &lv_style_plain_color);
    feildBase.body.main_color = LV_COLOR_HEX3(0x666);
    feildBase.body.grad_color = LV_COLOR_HEX3(0x666);

    feildContainer = lv_cont_create(lv_scr_act(), NULL);

    lv_obj_set_style(feildContainer, &feildBase);
    lv_obj_set_size(feildContainer, 240, 240);
  }

  void pentane::drawTiles(std::function <void(int)> onChange) {
    // styles
    static lv_style_t redTile;
    lv_style_copy(&redTile, &lv_style_plain_color);
    redTile.body.main_color = LV_COLOR_RED;
    redTile.body.grad_color = LV_COLOR_RED;

    static lv_style_t redTilePR;
    lv_style_copy(&redTilePR, &lv_style_plain_color);
    redTilePR.body.main_color = LV_COLOR_RED;
    redTilePR.body.grad_color = LV_COLOR_RED;
    redTilePR.body.border.color = LV_COLOR_WHITE;
    redTilePR.body.border.width = 3;

    static lv_style_t blueTile;
    lv_style_copy(&blueTile, &lv_style_plain_color);
    blueTile.body.main_color = LV_COLOR_BLUE;
    blueTile.body.grad_color = LV_COLOR_BLUE;

    static lv_style_t blueTilePR;
    lv_style_copy(&blueTilePR, &lv_style_plain_color);
    blueTilePR.body.main_color = LV_COLOR_BLUE;
    blueTilePR.body.grad_color = LV_COLOR_BLUE;
    blueTilePR.body.border.color = LV_COLOR_WHITE;
    blueTilePR.body.border.width = 3;

    // apply styles
    lv_obj_t * redA = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(redA, 40, 40);
    lv_obj_set_pos(redA, 0, 80);
    lv_btn_set_style(redA, LV_BTN_STYLE_REL, &redTile);
    lv_btn_set_style(redA, LV_BTN_STYLE_PR, &redTilePR);
    lv_obj_set_free_num(redA, 1);

    lv_obj_t * redB = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(redB, 40, 40);
    lv_obj_set_pos(redB, 0, 160);
    lv_btn_set_style(redB, LV_BTN_STYLE_REL, &redTile);
    lv_btn_set_style(redB, LV_BTN_STYLE_PR, &redTilePR);
    lv_obj_set_free_num(redB, 2);

    lv_obj_t * blueA = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(blueA, 40, 40);
    lv_obj_set_pos(blueA, 200, 80);
    lv_btn_set_style(blueA, LV_BTN_STYLE_REL, &blueTile);
    lv_btn_set_style(blueA, LV_BTN_STYLE_PR, &blueTilePR);
    lv_obj_set_free_num(blueA, 3);

    lv_obj_t * blueB = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(blueB, 40, 40);
    lv_obj_set_pos(blueB, 200, 160);
    lv_btn_set_style(blueB, LV_BTN_STYLE_REL, &blueTile);
    lv_btn_set_style(blueB, LV_BTN_STYLE_PR, &blueTilePR);
    lv_obj_set_free_num(blueB, 4);
    // change active buttons

    // bind functions to output
    lv_btn_set_action(blueA, LV_BTN_ACTION_PR, [](lv_obj_t * btn) -> lv_res_t {
      hc::pentane::selectedTile = 1;
      // lv_btn_set_state(btn, LV_BTN_STATE_TGL_REL);
      std::cout << "hello from: " << hc::pentane::selectedTile << std::endl;
      return LV_RES_OK;
    });
    lv_btn_set_action(blueB, LV_BTN_ACTION_PR, [](lv_obj_t * btn) -> lv_res_t {
      hc::pentane::selectedTile = 2;
      // lv_btn_set_state(btn, LV_BTN_STATE_TGL_REL);
      std::cout << "hello from: " << hc::pentane::selectedTile << std::endl;
      return LV_RES_OK;
    });
    lv_btn_set_action(redA, LV_BTN_ACTION_PR, [](lv_obj_t * btn) -> lv_res_t {
      hc::pentane::selectedTile = 3;
      // lv_btn_set_state(btn, LV_BTN_STATE_TGL_REL);
      std::cout << "hello from: " << hc::pentane::selectedTile << std::endl;
      return LV_RES_OK;
      lv_btn_set_style(btn, LV_BTN_STYLE_REL, &blueTile);
    });
    lv_btn_set_action(redB, LV_BTN_ACTION_PR, [](lv_obj_t * btn) -> lv_res_t {
      hc::pentane::selectedTile = 4;
      // lv_btn_set_state(btn, LV_BTN_STATE_REL);
      std::cout << "hello from: " << hc::pentane::selectedTile << std::endl;
      return LV_RES_OK;
      lv_btn_set_style(btn, LV_BTN_STYLE_REL, &blueTile);
    });
  }
}
