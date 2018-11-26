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
  void methane::Robot::redChase(float x, float y, float a, bool end = true) {
    while(!withinErr(tracker->x, tracker->y, tracker->a, x, y, a)) {

      float rot =   remap(fmod(TORAD(a - tracker->a), PI), -PI, PI, -1, 1);
      float trans = cos(TORAD(tracker->a) - atan2(tracker->y - y, tracker->x - x));

      float speedR = rPid->calculate(a, tracker->a);
      float speedT = tPid->calculate(-dist(tracker->x, tracker->y, x, y), 0);

      float idealVR = -((trans * (speedT) + rot * (speedR))) * 2;
      float idealVL = -((trans * (speedT) - rot * (speedR))) * 2;

      if(fabs(idealVL) > MAX_SPEED || fabs(idealVR) > MAX_SPEED) {
        if(fabs(idealVL) > fabs(idealVR)) {
          idealVR = (fabs(idealVR) - fabs(fabs(idealVL) - MAX_SPEED)) * SGN(idealVR);
          idealVL = MAX_SPEED * SGN(idealVL);
        } else if(fabs(idealVR) > fabs(idealVL)) {
          idealVL = (fabs(idealVL) - (fabs(idealVR) - MAX_SPEED)) * SGN(idealVL);
          idealVR = MAX_SPEED * SGN(idealVR);
        }
      }

      float targetVR = fabs(idealVR) > MIN_SPEED ? idealVR :
                       fabs(idealVR) < ZERO_SPEED ? 0 :
                       MIN_SPEED * SGN(idealVR);
      float targetVL = fabs(idealVL) > MIN_SPEED ? idealVL :
                       fabs(idealVR) < ZERO_SPEED ? 0 :
                       MIN_SPEED * SGN(idealVL);
      RIGHT_DRIVE_SET(targetVR);
      LEFT_DRIVE_SET(targetVL);
      // writeDebugStream("(%f%s%f%s%f%s", tracker->x, ", ", tracker->y, ")    | ", tracker->a, "\n-----\n\n");
    }
    if(end) {
      RIGHT_DRIVE_SET(0);
      RIGHT_DRIVE_SET(0);
    }
  }

  void methane::Robot::moveTo(::hc::benzene::Point target, float targetA) {
    std::cout << "Moving to: " << target.x << ", " << target.y << ")  |   " << targetA;

    redChase(target.x, target.y, targetA);
  }

}
