#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "main.h"
#include "odom.hpp"
#include "auton_selector.hpp"
#include "pid.hpp"
#include "../robot-config.hpp"

// robot specification macros
#define ZERO_SPEED 30
#define A_ERR 2
#define P_ERR 4

bool withinRange(float target, float current, float error);

namespace w {
  namespace robot {
    class Robot { // this class handles all of the auton functions
    private:
      ::w::odom::Tracker *tracker;

    public:
      Robot(::w::odom::Tracker *tracker,
            ::w::pid::PID *mainPID) :
            tracker(tracker) {};
      void seek(float x, float y, ::w::pid::PID *transPID, ::w::pid::PID *rotPID);
      void reset();

      void feedBall(float exit = 10000);
      bool hasBall();

      void flyUp(int rpm, std::function <void(float)> action);

      void moveTo(::w::odom::Point target, float err = P_ERR, float exit = 5000); // moves to a point
      void moveTo(::w::odom::Point target, float err, ::w::pid::PIDConfig tPID, ::w::pid::PIDConfig rPID, float exit = 5000);
      void moveTo(::w::odom::Point target, ::w::pid::PIDConfig tPID, ::w::pid::PIDConfig rPID, float exit = 5000);

      void moveAlong(::w::odom::Point wayPoints[], int len, float lookAhead, ::w::pid::PIDConfig tPID, ::w::pid::PIDConfig rPID, float err = P_ERR, float exit = 10000);
      // moves the bot along a set of way points

      void moveToSimple(::w::odom::Point target);
      void moveFor(float dist, float exit = 5000);

      void combineSet(bool rev);
        // moveTo({3, 4}, 45) - move to point (3, 4) and face 45deg
      // void moveFor(float length); // moves for a distance
        // moveFor(4) - move 4 in forwards
      void turnToFace(float deg, float max = 100);
      void turnToFace(::w::odom::Point point, float max = 100);
        // moveAlong({{1, 4}, {2, 5}}, 0); // move through the points (1, 4) then (2, 5) and end facing 0deg
      // void raiseLiftTo(int height); // rasie lift to a certain amount
      // void shootBall(int spd); // shoots a ball
      // void flipCap(); // flips the currently held cap
    };
  }
}

extern w::robot::Robot robot;

#endif
