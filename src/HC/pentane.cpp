#include "pentane.hpp"


namespace hc {
  void pentane::drawFeild() {
    lv_obj_t * feildContainer;

    static lv_style_t style;
    lv_style_copy(&style, &lv_style_plain_color);
    style.body.main_color = LV_COLOR_HEX3(0x666);
    style.body.grad_color = LV_COLOR_HEX3(0x666);
    style.body.padding.hor = 5;
    style.body.padding.ver = 5;

    feildContainer = lv_cont_create(lv_scr_act(), NULL);

    lv_obj_set_style(feildContainer, &style);
    lv_obj_set_size(feildContainer, 230, 230);
  }
}
