#include "pentane.hpp"


namespace hc {
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
    static lv_style_t redTile;
    lv_style_copy(&redTile, &lv_style_plain_color);
    redTile.body.main_color = LV_COLOR_RED;
    redTile.body.grad_color = LV_COLOR_RED;

    lv_obj_t * redA = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(redA, 40, 40);
    lv_obj_set_pos(redA, 0, 80);
    lv_obj_set_style(redA, &redTile);

    lv_obj_t * redB = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(redB, 40, 40);
    lv_obj_set_pos(redB, 0, 160);
    lv_obj_set_style(redA, &redTile);
  }
}
