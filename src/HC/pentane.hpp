#ifndef PENTANE_HPP
#define PENTANE_HPP

#include "main.h"
#include "../auton/def.hpp"
#include <functional>

namespace hc {
  namespace pentane {
    extern std::string selectedAuton;
    extern int selectedTile;
    extern lv_obj_t* list;
    extern lv_obj_t* titleBar;
    void drawFeild();
    void drawTiles(std::function <void(int)> onChange);
  }
}

#endif
