#include "ethane.hpp"

#include <functional>
#include "main.h"
#include "../robot-config.hpp"



namespace hc {
  bool ethane::Flywheel::atTargetVel(float vel) {
    return withinRange(vel, GET_VEL, VEL_ERR);
  }
  bool ethane::Flywheel::atTargetVel() {
    return withinRange(targetVel, GET_VEL, VEL_ERR);
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
      if(!flywheel->atTargetVel() && !flywheel->shouldMaintain()) {
        flywheel->setTargetVel(flywheel->getTargetVel(), [](int i){
          FLYWHEEL_SET(0);
        });
      }
      pros::delay(20);
    }
  }
}
