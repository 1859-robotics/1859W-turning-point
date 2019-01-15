#ifndef APP_HPP
#define APP_HPP

#define ASYNC(name, body) pros::Task name([](auto a, auto&& b) { \
  return a < b; \
}); \

#include "HC/benzene.hpp"
#include "HC/propene.hpp"
#include "HC/methane.hpp"
#include "HC/pentane.hpp"

#include "robot-config.hpp"

#endif
