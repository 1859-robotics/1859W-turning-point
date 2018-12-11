#ifndef ETHANE_HPP
#define ETHANE_HPP

#include <functional>



#define GET_VEL (flywheelMotor.get_actual_velocity())

#define VEL_ERR 0
#define IDLE_VEL 60
#define IDLE_SPD 60

namespace hc {
  namespace ethane {
    class Flywheel {
    private:
      bool overwrite;
      float idleVel;
      float targetVel;
    public:
      Flywheel(bool overwrite, float idleVel = IDLE_VEL) :
        overwrite(overwrite), idleVel(idleVel) {};
      void setTargetVel(float vel, std::function<void(float)>callback);
      void maintainTargetVel();
      bool atTargetVel(float vel);
      bool atTargetVel();
      bool shouldMaintain();
      float getTargetVel();
    };
    void maintain(void *ptr);
  }
}

#endif
