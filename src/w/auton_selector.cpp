#include "auton_selector.hpp"


namespace w {
  lv_obj_t* auton_selector::feildContainer = lv_cont_create(lv_scr_act(), NULL);

  std::string auton_selector::selectedAuton = "";
  int auton_selector::selectedTile = -1;
  lv_obj_t * auton_selector::list = lv_ddlist_create(lv_scr_act(), NULL);

  lv_obj_t *auton_selector::redA = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_t *auton_selector::redB = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_t *auton_selector::blueA = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_t *auton_selector::blueB = lv_btn_create(lv_scr_act(), NULL);

  lv_style_t auton_selector::redTile = {};
  lv_style_t auton_selector::redTileActive = {};
  lv_style_t auton_selector::blueTile = {};
  lv_style_t auton_selector::blueTileActive = {};
  lv_style_t auton_selector::activeTile = {};

  void auton_selector::drawFeild() {
    static lv_style_t feildBase;

    lv_style_copy(&feildBase, &lv_style_plain_color);
    feildBase.body.main_color = LV_COLOR_HEX3(0x666);
    feildBase.body.grad_color = LV_COLOR_HEX3(0x666);

    lv_obj_set_style(feildContainer, &feildBase);
    lv_obj_set_size(feildContainer, 240, 240);
  }

  void auton_selector::init() {
    // style init
    lv_style_copy(&redTile, &lv_style_plain_color);
    redTile.body.main_color = LV_COLOR_RED;
    redTile.body.grad_color = LV_COLOR_RED;

    lv_style_copy(&redTileActive, &lv_style_plain_color);
    redTileActive.body.main_color = LV_COLOR_RED;
    redTileActive.body.grad_color = LV_COLOR_RED;
    redTileActive.body.border.color = LV_COLOR_WHITE;
    redTileActive.body.border.width = 3;

    lv_style_copy(&blueTile, &lv_style_plain_color);
    blueTile.body.main_color = LV_COLOR_BLUE;
    blueTile.body.grad_color = LV_COLOR_BLUE;

    lv_style_copy(&blueTileActive, &lv_style_plain_color);
    blueTileActive.body.main_color = LV_COLOR_BLUE;
    blueTileActive.body.grad_color = LV_COLOR_BLUE;
    blueTileActive.body.border.color = LV_COLOR_WHITE;
    blueTileActive.body.border.width = 3;

    lv_style_copy(&activeTile, &lv_style_plain_color);
    activeTile.body.main_color = LV_COLOR_MAGENTA;
    activeTile.body.grad_color = LV_COLOR_MAGENTA;

    lv_obj_set_size(redA, 40, 40);
    lv_obj_set_pos(redA, 0, 80);
    lv_btn_set_style(redA, LV_BTN_STYLE_REL, &redTile);
    lv_btn_set_style(redA, LV_BTN_STYLE_PR, &redTileActive);
    lv_obj_set_free_num(redA, 1);

    lv_obj_set_size(redB, 40, 40);
    lv_obj_set_pos(redB, 0, 160);
    lv_btn_set_style(redB, LV_BTN_STYLE_REL, &redTile);
    lv_btn_set_style(redB, LV_BTN_STYLE_PR, &redTileActive);
    lv_obj_set_free_num(redB, 2);

    lv_obj_set_size(blueA, 40, 40);
    lv_obj_set_pos(blueA, 200, 80);
    lv_btn_set_style(blueA, LV_BTN_STYLE_REL, &blueTile);
    lv_btn_set_style(blueA, LV_BTN_STYLE_PR, &blueTileActive);
    lv_obj_set_free_num(blueA, 3);

    lv_obj_set_size(blueB, 40, 40);
    lv_obj_set_pos(blueB, 200, 160);
    lv_btn_set_style(blueB, LV_BTN_STYLE_REL, &blueTile);
    lv_btn_set_style(blueB, LV_BTN_STYLE_PR, &blueTileActive);
    lv_obj_set_free_num(blueB, 4);
  }

  void auton_selector::setActiveTile(lv_obj_t *active) {
    lv_btn_set_style(redA, LV_BTN_STYLE_REL, &redTile);
    lv_btn_set_style(redB, LV_BTN_STYLE_REL, &redTile);
    lv_btn_set_style(blueA, LV_BTN_STYLE_REL, &blueTile);
    lv_btn_set_style(blueB, LV_BTN_STYLE_REL, &blueTile);

    lv_btn_set_style(active, LV_BTN_STYLE_REL, &activeTile);
  }

  void auton_selector::drawTiles(std::function <void(int)> onChange) {
    // bind functions to output
    lv_btn_set_action(blueA, LV_BTN_ACTION_PR, [](lv_obj_t * btn) -> lv_res_t {
      w::auton_selector::selectedTile = TILE_BLUE_A;

      lv_ddlist_set_options(w::auton_selector::list, AUTON_OPTIONS_BLUE_A);
      lv_btn_set_style(btn, LV_BTN_STYLE_PR, &blueTileActive);
      w::auton_selector::setActiveTile(btn);
      return LV_RES_OK;
    });

    lv_btn_set_action(blueB, LV_BTN_ACTION_PR, [](lv_obj_t * btn) -> lv_res_t {
      w::auton_selector::selectedTile = TILE_BLUE_B;

      lv_ddlist_set_options(w::auton_selector::list, AUTON_OPTIONS_BLUE_B);
      lv_btn_set_style(btn, LV_BTN_STYLE_PR, &blueTileActive);
      w::auton_selector::setActiveTile(btn);
      return LV_RES_OK;
    });

    lv_btn_set_action(redA, LV_BTN_ACTION_PR, [](lv_obj_t * btn) -> lv_res_t {
      w::auton_selector::selectedTile = TILE_RED_A;
      lv_ddlist_set_options(w::auton_selector::list, AUTON_OPTIONS_RED_A);
      lv_btn_set_style(btn, LV_BTN_STYLE_REL, &redTile);
      lv_btn_set_style(btn, LV_BTN_STYLE_PR, &redTileActive);
      w::auton_selector::setActiveTile(btn);
      return LV_RES_OK;
    });

    lv_btn_set_action(redB, LV_BTN_ACTION_PR, [](lv_obj_t * btn) -> lv_res_t {
      w::auton_selector::selectedTile = TILE_RED_B;
      lv_ddlist_set_options(w::auton_selector::list, AUTON_OPTIONS_RED_B);
      lv_btn_set_style(btn, LV_BTN_STYLE_REL, &redTile);
      lv_btn_set_style(btn, LV_BTN_STYLE_PR, &redTileActive);
      w::auton_selector::setActiveTile(btn);
      return LV_RES_OK;
    });
  }
}
