#include "ethane.hpp"

#include <functional>
#include "main.h"
#include "../robot-config.hpp"

bool withinErr(float target, float current, float error) {
  return abs(target - current) < error;
}

namespace hc {
  bool ethane::Flywheel::atTargetVel(float vel) {
    return withinErr(vel, GET_VEL, VEL_ERR);
  }
  bool ethane::Flywheel::atTargetVel() {
    return withinErr(targetVel, GET_VEL, VEL_ERR);
  }
  bool ethane::Flywheel::shouldMaintain() { return overwrite; }
  float ethane::Flywheel::getTargetVel(){ return targetVel; }
  void ethane::Flywheel::setTargetVel(float vel, std::function<void(float)>callback) {
    targetVel = vel;
    while(!atTargetVel(vel)) {
      if (vel - GET_VEL > 0) {
        FLYWHEEL_SET(127);
      } else if(vel - GET_VEL < 0) {
        FLYWHEEL_SET(0);
      }
    }
    callback(vel);
  }

  void ethane::maintain(void *ptr) {
    ethane::Flywheel* flywheel = static_cast<ethane::Flywheel*>(ptr);
    while(true) {
      if(!flywheel->shouldMaintain()) {
        flywheel->setTargetVel(flywheel->getTargetVel(), [](int i){
          FLYWHEEL_SET(10);
        });
      }
      pros::delay(20);
    }
  }
}
