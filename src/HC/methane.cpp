#include "methane.hpp"


// util functions
bool withinRange(float target, float current, float error) {
  return abs(target - current) < error;
}

bool withinErr(float cX, float cY, float cA, float tX, float tY, float tA, float eP = P_ERR, float eA = A_ERR) {
  return (
    withinRange(tX, cX, eP) &&
    withinRange(tY, cY, eP) &&
    withinRange(tA, cA, eA)
  );
}

float dist(float x1, float y1, float x2, float y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

float dot(float x1, float y1, float x2, float y2) {
  return  (x1 * x2) + (y1 * y2);
}


float remap (float value, float from1, float to1, float from2, float to2) {
      return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
  }
// end util functions


namespace hc {
  void methane::Robot::seek(float x, float y, float a, bool end = true) {

  }

  void methane::Robot::moveTo(::hc::benzene::Point target, float targetA) {
  }

  void methane::Robot::moveAlong(::hc::benzene::Point wayPoints[], int size, float endA) {

  }

  void methane::Robot::turnToFace(float deg) {
    std::cout << "starting turn to face" << std::endl;

    pid->doPID(deg, 3, []() -> float {
      return TODEG(posTracker.a);
    }, [](float output) -> void {
      RIGHT_DRIVE_SET(-output);
      LEFT_DRIVE_SET(output);
    });
    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void methane::Robot::turnToFace(::hc::benzene::Point point) {
    turnToFace(TODEG(atan2(point.x, point.y)));
  }

  void methane::Robot::reset() {
    std::cout << "reseting bot..." << std::endl;
    tracker->reset();
    std::cout << "reset bot" << std::endl;
  }
}

hc::methane::Robot robot = hc::methane::Robot(&posTracker, &mainPID);
