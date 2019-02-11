#pragma once

#include "main.h"
#include <functional>

class Burtrum : public Chassis {
public:
  void reset();
  void flyUp(int rpm, std::function <void(float)> action);
  void combineSet(bool rev);
  void feedBall(float exit = 10000);
  bool hasBall();
};
