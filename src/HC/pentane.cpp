#include "pentane.hpp"


namespace hc {
  void pentane::alert(const char* message) {
    STYLE(style);

    lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, message);
    lv_obj_set_style(label, &style);
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);
  }


  void pentane::button(const char* message, std::function<void()> callback) {
    STYLE(style);

    lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, message);
    lv_obj_set_style(label, &style);
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);
  }
}
