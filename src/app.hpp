#ifndef APP_HPP
#define APP_HPP

#define SKILLS_MODE true

#define ASYNC(name, body) pros::Task name([](void*) body);


#include "HC/benzene.hpp"
#include "HC/propene.hpp"
#include "HC/methane.hpp"
#include "HC/pentane.hpp"

#include "robot-config.hpp"

#endif
