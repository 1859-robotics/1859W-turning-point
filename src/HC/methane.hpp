#ifndef METHANE_HPP
#define METHANE_HPP

#include "main.h"
#include "benzene.hpp"


namespace hc {
  namespace methane {
    class Robot { // this class handles all of the auton functions
    private:
      ::hc::benzene::Tracker *tracker;

    public:
      Robot(::hc::benzene::Tracker *tracker) : tracker(tracker) {};
      // void moveTo(json point); // moves to a point
      // void moveFor(float length); // moves for a distance
      // void turnToFace(json point); // turns to face a point
      // void turnToFace(int angle); // turns to face an angle


    };
  }
}

#endif
