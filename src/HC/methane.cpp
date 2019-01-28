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

float dist(::hc::benzene::Point a, ::hc::benzene::Point b) {
    return sqrt((a.x * b.x) + (a.y * b.y));
}

float dot(float x1, float y1, float x2, float y2) {
  return (x1 * x2) + (y1 * y2);
}

float dot(::hc::benzene::Point a, ::hc::benzene::Point b) { return a.x * b.x + a.y * b.y; }


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

::hc::benzene::Point getNormalPoint(::hc::benzene::Point p, ::hc::benzene::Point a, ::hc::benzene::Point b) {
  ::hc::benzene::Point ap = sub(p, a);
  ::hc::benzene::Point ab = sub(b, a);
  ab = normalize(ab);
  ab = multScalar(ab, dot(ap, ab));
  ::hc::benzene::Point r = add(a, ab);
  if ((r.y > std::max(a.y, b.y) && r.x > std::max(a.x, b.x)) ||
      (r.y < std::min(a.y, b.y) && r.x < std::min(a.x, b.x)) ||
      (r.y > std::max(a.y, b.y) && r.x < std::min(a.x, b.x)) ||
      (r.y < std::min(a.y, b.y) && r.x > std::max(a.x, b.x))) {
    r = dist(p, a) < dist(p, b) ? a : b;
  }
  return r;
}

::hc::benzene::Point getTarget(::hc::benzene::Point path[], int len, ::hc::benzene::Point current, float along) {
    // let normalPoint = getNormalFromPath(p, path)
    // let lookAhead = lookAheadOnPath(path, normalPoint, lookAheadDist)

    ::hc::benzene::Point target;

    //TODO: make this not bad
    ::hc::benzene::Point min = { -1, -1 };
    int seg = 0;

    for(int i = 0; i < len - 1; i++) {
        ::hc::benzene::Point normalPoint = getNormalPoint(current, path[i], path[i + 1]);
        if((min.x == -1 && min.y == -1) || (dist(current, normalPoint) < dist(current, min))) {
            min = normalPoint;
            seg = i;
        }
    }

    ::hc::benzene::Point turnless = sub(path[seg + 1], path[seg]);
    turnless = normalize(turnless);
    turnless = multScalar(turnless, along);
    turnless = add(current, turnless);
    float subDist = dist(current, path[seg + 1]);

    if(!(dist(current, turnless) > subDist)) return turnless;


    ::hc::benzene::Point lookAhead = current;
    ::hc::benzene::Point prevPoint = current;
    int n = along;

    while(0 < n) {
        if(seg + 1 > len) {
            n = 0;
            lookAhead = path[seg];
        } else if(n > dist(prevPoint, path[seg + 1])) {
            n -= dist(prevPoint, path[seg + 1]);
            prevPoint = path[seg + 1];
            seg++;
        } else {
            lookAhead = sub(path[seg + 1], prevPoint);
            lookAhead = normalize(lookAhead);
            lookAhead = multScalar(lookAhead, n);
            lookAhead = add(path[seg], lookAhead);
            n = 0;
        }
    }
    return lookAhead;

}


namespace hc {
  void methane::Robot::seek(float x, float y, propene::PID *transPID, propene::PID *rotPID) {
    float tA = atan2(posTracker.y - y, posTracker.x - x);

    ::hc::benzene::Point close = closest(
      { posTracker.x, posTracker.y },
      { cos(posTracker.a), sin(posTracker.a) },
      { x, y }
    );

    float V = dist(close.x, close.y, posTracker.x, posTracker.y);
    V = std::isnan(V) ? 0 : V;
    // V = abs(V) > 1 ? SGN(V) : V;

    float aP = atan2(close.y - posTracker.y, close.x - posTracker.x);
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

    LEFT_DRIVE_SET(Vl);
    RIGHT_DRIVE_SET(Vr);
  }

  void methane::Robot::moveTo(::hc::benzene::Point target, float err, float exit) {
    ::hc::propene::PID *transPID = new ::hc::propene::PID(10, 0, 0, 0.001, 0.0001, MAX_SPEED, MIN_SPEED);
    ::hc::propene::PID *rotPID = new ::hc::propene::PID(2, 0, 0, 0.0001, 0.00001, MAX_SPEED, MIN_SPEED);

    std::uint32_t started = pros::millis();

    while(!withinErr(posTracker.x, posTracker.y, target.x, target.y, err)) {
      if((pros::millis() - started) > exit) break;
      seek(target.x, target.y, transPID, rotPID);
      pros::delay(20);
    }

    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void methane::Robot::moveTo(::hc::benzene::Point target, float err, ::hc::propene::PIDConfig tPID, ::hc::propene::PIDConfig rPID, float exit) {
    ::hc::propene::PID *transPID = new ::hc::propene::PID(tPID, 0.001, 0.0001);
    ::hc::propene::PID *rotPID = new ::hc::propene::PID(rPID, 0.0001, 0.00001);

    std::uint32_t started = pros::millis();

    while(!withinErr(posTracker.x, posTracker.y, target.x, target.y, err)) {
      if((pros::millis() - started) > exit) break;
      seek(target.x, target.y, transPID, rotPID);
      pros::delay(20);
    }

    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void methane::Robot::moveTo(::hc::benzene::Point target, ::hc::propene::PIDConfig tPID, ::hc::propene::PIDConfig rPID, float exit) {
    methane::Robot::moveTo(target, P_ERR, tPID, rPID);
  }

  void methane::Robot::moveToSimple(::hc::benzene::Point target) {
    turnToFace(target, 60);
    moveFor(dist(posTracker.x, posTracker.y, target.x, target.y));
  }

  void methane::Robot::moveAlong(::hc::benzene::Point wayPoints[], int len, float lookAhead, ::hc::propene::PIDConfig tPID, ::hc::propene::PIDConfig rPID, float err) {

    while(!withinErr(posTracker.x, posTracker.y, wayPoints[len - 1].x, wayPoints[len - 1].y, err)) {
      ::hc::benzene::Point target = getTarget(wayPoints, len, { posTracker.x, posTracker.y }, lookAhead);
      ::hc::propene::PID *transPID = new ::hc::propene::PID(tPID, 0.001, 0.0001);
      ::hc::propene::PID *rotPID = new ::hc::propene::PID(rPID, 0.0001, 0.00001);
      std::cout << "target:  (" << target.x << ", " << target.y << ")" << std::endl;
      std::cout << "current: (" << posTracker.x << ", " << posTracker.y << ")" << std::endl;

      seek(target.x, target.y, transPID, rotPID);
      pros::delay(20);
    }
    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
    std::cout << "end moveAlong" << std::endl;
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
}

hc::methane::Robot robot = hc::methane::Robot(&posTracker, &mainPID);
