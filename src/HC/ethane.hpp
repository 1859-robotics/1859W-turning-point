#ifndef ETHANE_HPP
#define ETHANE_HPP

#include <functional>



#define GET_VEL (flywheelL.get_actual_velocity() + flywheelR.get_actual_velocity()) / 2

#define VEL_ERR 2

namespace hc {
  namespace ethane {
    class Flywheel {
    private:
      bool overwrite;
      float idleVel;
      float targetVel;
    public:
      Flywheel(bool overwrite, float idleVel) :
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
