#ifndef APP_HPP
#define APP_HPP

#define SKILLS_MODE true

#define ASYNC(name, body) pros::Task name([](void*) body);

#define REMOVE_TASK(name) name.remove(); while(name.get_state() != TASK_STATE_DELETED) {}

#include "w/odom.hpp"
#include "w/pid.hpp"
#include "w/robot.hpp"
#include "w/auton_selector.hpp"

#include "robot-config.hpp"

#endif
