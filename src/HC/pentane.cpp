#include "pentane.hpp"


namespace hc {
  void pentane::alert(const char* message) {
    lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, message);
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);
  }


  // void pentane::button(const char* message, std::function<lv_res_t(lv_obj_t * btn)> callback) {
  //   lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
  //   lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
  //
  //   label = lv_label_create(btn1, NULL);
  //   lv_label_set_text(label, "Normal");
  //
  //   lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
  //   lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  //   lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
  //   // lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, callback);
  //   lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK);
  // }
}
