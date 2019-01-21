#include "methane.hpp"


// util functions
bool withinRange(float target, float current, float error) {
  return abs(target - current) < error;
}

bool withinErr(float cX, float cY, float tX, float tY, float eP = P_ERR) {
  return (
    withinRange(tX, cX, eP) &&
    withinRange(tY, cY, eP)
  );
}

float dist(float x1, float y1, float x2, float y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

float dot(float x1, float y1, float x2, float y2) {
  return (x1 * x2) + (y1 * y2);
}

float remap (float value, float from1, float to1, float from2, float to2) {
  return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
}


float angleDiff(float angle1, float angle2) {
  float diff = fmod(( angle2 - angle1 + PI ), TAU) - PI;
  return diff < -PI ? diff + TAU : diff;
}
// end util functions


// vector stuffs
::hc::benzene::Point add(::hc::benzene::Point a, ::hc::benzene::Point b) {
  return { a.x + b.x, a.y + b.y };
}
::hc::benzene::Point sub(::hc::benzene::Point a, ::hc::benzene::Point b) {
  return { a.x - b.x, a.y - b.y };
}
::hc::benzene::Point mult(::hc::benzene::Point a, ::hc::benzene::Point b) {
  return { a.x * b.x, a.y * b.y };
}
::hc::benzene::Point div(::hc::benzene::Point a, ::hc::benzene::Point b) {
  return { a.x / b.x, a.y / b.y };
}

float mag(::hc::benzene::Point a) {
  return sqrt((a.x * a.x) + (a.y * a.y));
}

::hc::benzene::Point normalize(::hc::benzene::Point a) {
  return { a.x / mag(a), a.y / mag(a) };
}

::hc::benzene::Point multScalar(::hc::benzene::Point a, float b) {
  return { a.x * b, a.y * b };
}

::hc::benzene::Point closest(::hc::benzene::Point current, ::hc::benzene::Point head, ::hc::benzene::Point target) {
  ::hc::benzene::Point n = normalize(head);
  ::hc::benzene::Point v = sub(target, current);
  float d = dot(v.x, v.y, n.x, n.y);
  return add(current, multScalar(n, d));
}

namespace hc {
  void methane::Robot::seek(float x, float y, propene::PID *transPID, propene::PID *rotPID) {
    float eA = angleDiff(posTracker.a, atan2(y - posTracker.y, x - posTracker.x));

    ::hc::benzene::Point close = closest({
      posTracker.x, posTracker.y
    }, { cos(posTracker.a), sin(posTracker.a) }, {
      x, y
    });

    float V = -dist(close.x, close.y, posTracker.x, posTracker.y);

    if (abs(atan2(close.y - posTracker.y, close.x - posTracker.x) - posTracker.a) > PI/2) {
      V *= -1;
    }

    float trans = transPID->calculate(V, 0);
    float rot = rotPID->calculate(eA, 0);

    float idealVR = ((trans) - (rot));
    float idealVL = ((trans) + (rot));

    // DEBUG_VAR(trans);
    // DEBUG_VAR(eA);

    float maxMag = fmax(abs(idealVL), abs(idealVR));
    float minMag = fmin(abs(idealVL), abs(idealVR));

    if (maxMag > 127)  {
      idealVR /= maxMag;
      idealVL /= maxMag;

      RIGHT_DRIVE_SET(idealVR * 127);
      LEFT_DRIVE_SET(idealVL * 127);

    } else {
      RIGHT_DRIVE_SET(idealVR);
      LEFT_DRIVE_SET(idealVL);
    }


    // std::cout << "idealVR : " << idealVR << std::endl;
    // std::cout << "idealVL : " << idealVL << std::endl;


  }

  void methane::Robot::moveTo(::hc::benzene::Point target, float targetA) {
    ::hc::propene::PID *transPID = new ::hc::propene::PID(100, 0, 0, 0.001, 0.001, MAX_SPEED, MIN_SPEED);
    ::hc::propene::PID *rotPID = new ::hc::propene::PID(70, 0, 0, 0.0001, 0.00001, MAX_SPEED, MIN_SPEED);


    while(!withinErr(posTracker.x, posTracker.y, target.x, target.y)) {
      // std::cout << "posTracker.x: " << posTracker.x << std::endl;
      // std::cout << "posTracker.y: " << posTracker.y << std::endl;

      seek(target.x, target.y, transPID, rotPID);
    }

    // if(!withinRange(TODEG(posTracker.a), targetA, A_ERR))
    //   turnToFace(targetA);

    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void methane::Robot::moveAlong(::hc::benzene::Point wayPoints[], int size, float endA) {

  }

  void methane::Robot::moveFor(float distIn) {
    ::hc::benzene::Point start = {
      posTracker.x,
      posTracker.y
    };

    pid->config(8, 0, 0.1, 0.001, 0.001, MAX_SPEED, MIN_SPEED);


    pid->doPID(0, P_ERR, [=]() -> float {
      return (fabs(distIn) - dist(start.x, start.y, posTracker.x, posTracker.y));
    }, [=](float output) -> void {
      RIGHT_DRIVE_SET(SGN(-distIn) * output);
      LEFT_DRIVE_SET(SGN(-distIn) * output);
    });
    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void methane::Robot::turnToFace(float deg) {
    pid->config(3, 0.01, 0.2, 3, 30, MAX_SPEED, MIN_SPEED);

    if(withinRange(TODEG(posTracker.a), deg, A_ERR)) return;

    pid->doPID(deg, A_ERR, []() -> float {
      return TODEG(posTracker.a);
    }, [](float output) -> void {
      RIGHT_DRIVE_SET(output);
      LEFT_DRIVE_SET(-output);
    });

    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void methane::Robot::turnToFace(::hc::benzene::Point point) {
    turnToFace(TODEG(atan2(point.x - posTracker.x, point.y - posTracker.y)));
  }

  void methane::Robot::combineSet(bool rev) {
    combine.move(rev ? 127 : -127);
  }

  void methane::Robot::feedBall() {
    while(!limit.get_value()) {
      INTAKE_SET(127);
    }
    INTAKE_SET(0);

  }

  void methane::Robot::reset() {
    tracker->reset();
  }

  void methane::Robot::flyUp(int rpm, std::function <void(float)> action) {
    while(true) {
      if(withinRange(rpm, FLYWHEEL_GET_VEL, FLYWHEEL_ERR)) {
        action(FLYWHEEL_GET_VEL);
        FLYWHEEL_SET(FLYWHEEL_IDLE);
        break;
      } else if(FLYWHEEL_GET_VEL < rpm) {
        FLYWHEEL_SET(127);
      } else {
        FLYWHEEL_SET(20);
      }
    }
  }
}

hc::methane::Robot robot = hc::methane::Robot(&posTracker, &mainPID);
