#ifndef APP_HPP
#define APP_HPP

#define ASYNC(name, body) pros::Task name([]() { \
  body \
  name.remove(); \
});

#include "HC/benzene.hpp"
#include "HC/propene.hpp"
#include "HC/methane.hpp"
#include "HC/pentane.hpp"

#include "robot-config.hpp"

#endif
