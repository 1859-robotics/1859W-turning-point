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
    float tA = atan2(posTracker.y - y, posTracker.x - x);
    // tA = Math.abs(tA) > (4 * PI) ? tA - PI * sgn(tA) : tA
    // console.log(tA)

    ::hc::benzene::Point close = closest(
      { posTracker.x, posTracker.y },
      { cos(posTracker.a), sin(posTracker.a) },
      { x, y }
    );

    float V = -dist(close.x, close.y, posTracker.x, posTracker.y);
    V = std::isnan(V) ? 0 : V;
    // V = abs(V) > 1 ? SGN(V) : V;

    float aP = atan2(close.x - posTracker.x, close.y - posTracker.y);
    aP = fmod(aP, (2 * PI)) * SGN(aP);
    if (abs(aP) > PI/2) {
      V = V * -1;
      tA -= PI * SGN(aP);
    }

    float W = angleDiff(tA, posTracker.a);

    float rot = rotPID->calculate(W, 0);
    float trans = transPID->calculate(V, 0);

    float Vr = trans + rot;
    float Vl = trans - rot;

    DEBUG_VAR(trans);
    DEBUG_VAR(rot);
    DEBUG_VAR(W);
    DEBUG_VAR(V);

    LEFT_DRIVE_SET(Vl);
    RIGHT_DRIVE_SET(Vr);
  }

  void methane::Robot::moveTo(::hc::benzene::Point target, float targetA) {
    ::hc::propene::PID *transPID = new ::hc::propene::PID(1, 0, 0, 0.001, 0.0001, MAX_SPEED / 2, MIN_SPEED / 2);
    ::hc::propene::PID *rotPID = new ::hc::propene::PID(1, 0, 0, 0.0001, 0.00001, MAX_SPEED / 2, MIN_SPEED / 2);


    while(!withinErr(posTracker.x, posTracker.y, target.x, target.y)) {
      seek(target.x, target.y, transPID, rotPID);
    }

    // if(!withinRange(TODEG(posTracker.a), targetA, A_ERR))
    //   turnToFace(targetA);

    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void methane::Robot::moveToSimple(::hc::benzene::Point target) {
    turnToFace(target, 60);
    moveFor(dist(posTracker.x, posTracker.y, target.x, target.y));
  }

  void methane::Robot::moveAlong(::hc::benzene::Point wayPoints[], int size, float endA) {

  }

  void methane::Robot::moveFor(float distIn, float exit) {
    ::hc::benzene::Point start = {
      posTracker.x,
      posTracker.y
    };

    pid->config(8, 0, 0.1, 0.001, 0.001, MAX_SPEED, MIN_SPEED);

    std::uint32_t started = pros::millis();

    pid->doPID(0, P_ERR, [=]() -> float {
      if((pros::millis() - started) > exit) return 0;
      return (fabs(distIn) - dist(start.x, start.y, posTracker.x, posTracker.y));
    }, [=](float output) -> void {
      RIGHT_DRIVE_SET(SGN(-distIn) * output);
      LEFT_DRIVE_SET(SGN(-distIn) * output);
    });
    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void methane::Robot::turnToFace(float deg, float max) {
    pid->config(3, 0.01, 0.2, 3, 30, max, MIN_SPEED);

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

  void methane::Robot::turnToFace(::hc::benzene::Point point, float max) {
    turnToFace(TODEG(atan2(point.y - posTracker.y, point.x - posTracker.x)), max);
  }

  void methane::Robot::combineSet(bool rev) {
    combine.move(rev ? 127 : -127);
  }

  void methane::Robot::feedBall(float exit) {
    while(!limit.get_value()) {
      INTAKE_SET(127);
    }
    INTAKE_SET(0);
  }

  void methane::Robot::reset() {
    tracker->reset();
  }

  bool methane::Robot::hasBall() {
    return !!limit.get_value();
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
        FLYWHEEL_SET(-127); //TODO: make this not bad
      }
    }
  }

  void methane::Robot::nono(int s, int time) {
    // NONO_SET(s);
    // pros::delay(time);
    // NONO_SET(0);
  }
}

hc::methane::Robot robot = hc::methane::Robot(&posTracker, &mainPID);
