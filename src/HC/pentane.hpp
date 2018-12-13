#ifndef PENTANE_HPP
#define PENTANE_HPP

#define STYLE(name) static lv_style_t style; lv_style_copy(&style, &lv_style_plain)

#include "main.h"
#include <functional>

namespace hc {
  namespace pentane {
    void alert(const char* message);
    // void button(const char* message, std::function<lv_res_t(lv_obj_t * btn)> callback);
  }
}

#endif
