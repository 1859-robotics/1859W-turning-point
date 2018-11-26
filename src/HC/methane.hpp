#ifndef METHANE_HPP
#define METHANE_HPP

#include "main.h"
#include "benzene.hpp"
#include "propene.hpp"
#include "../robot-config.hpp"

// robot specification macros
#define MIN_SPEED 10
#define ZERO_SPEED 10
#define MAX_SPEED 127
#define A_ERR 5
#define P_ERR 3.5

namespace hc {
  namespace methane {
    class Robot { // this class handles all of the auton functions
    private:
      ::hc::benzene::Tracker *tracker;
      ::hc::propene::PID *rPid;
      ::hc::propene::PID *tPid;

    public:
      Robot(::hc::benzene::Tracker *tracker,
            ::hc::propene::PID *rPID,
            ::hc::propene::PID *tPID) :
            tracker(tracker), rPid(rPID), tPid(tPID) {};
      void redChase(float x, float y, float a, bool end);

      // auton functions
      void moveTo(::hc::benzene::Point target, float targetA); // moves to a point
        // moveTo({3, 4}, 45) - move to point (3, 4) and face 45deg
      // void moveFor(float length); // moves for a distance
        // moveFor(4) - move 4 in forwards
      // void turnToFace(Point point); // turns to face a point
        // turnToFace({4, 6}); - turn to face the point (4, 6)
      // void turnToFace(int angle); // turns to face an angle
        // turnToFace(45); - turn to face 45deg
      void moveAlong(::hc::benzene::Point wayPoints[], int size, float a); // moves the bot along a set of way points
        // moveAlong({{1, 4}, {2, 5}}, 0); // move through the points (1, 4) then (2, 5) and end facing 0deg
      // void raiseLiftTo(int height); // rasie lift to a certain amount
      // void shootBall(int spd); // shoots a ball
      // void flipCap(); // flips the currently held cap
    };
  }
}

extern hc::methane::Robot robot;

#endif
