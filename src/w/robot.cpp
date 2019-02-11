#include "robot.hpp"

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

// target stuffs
w::odom::Point closest(w::odom::Point current, w::odom::Point head, w::odom::Point target) {
  w::odom::Point n = normalize(head);
  w::odom::Point v = sub(target, current);
  float d = dot(v, n);
  return add(current, multScalar(n, d));
}
w::odom::Point getNormalPoint(w::odom::Point p, w::odom::Point a, w::odom::Point b) {
  w::odom::Point ap = sub(p, a);
  w::odom::Point ab = sub(b, a);
  ab = normalize(ab);
  ab = multScalar(ab, dot(ap, ab));
  w::odom::Point r = add(a, ab);
  if ((r.y > std::max(a.y, b.y) || r.x > std::max(a.x, b.x)) ||
      (r.y < std::min(a.y, b.y) || r.x < std::min(a.x, b.x)) ||
      (r.y > std::max(a.y, b.y) || r.x < std::min(a.x, b.x)) ||
      (r.y < std::min(a.y, b.y) || r.x > std::max(a.x, b.x))) {
    r = dist(p, a) < dist(p, b) ? a : b;
  }
  return r;
}
w::odom::Point getTarget(w::odom::Point path[], int len, w::odom::Point current, float along) {
  w::odom::Point target;

  w::odom::Point normal;
  int seg = 0;

  for(int i = 0; i < len - 1; i++) {
    w::odom::Point normalPoint = getNormalPoint(current, path[i], path[i + 1]);
    if(i == 0 || (dist(current, normalPoint) < dist(current, normal))) {
      normal = normalPoint;
      seg = i;
    }
  }

  std::cout << "normal:  (" << normal.x << ", " << normal.y << ")" << std::endl;


  w::odom::Point turnless = sub(path[seg + 1], path[seg]);
  turnless = normalize(turnless);
  turnless = multScalar(turnless, along);
  turnless = add(normal, turnless);
  float subDist = dist(normal, path[seg + 1]);

  if(dist(normal, turnless) < subDist) return turnless;

  w::odom::Point lookAhead;
  w::odom::Point prevPoint = normal;
  float n = along;

  while(0 < n) {
    if(seg + 1 > len) {
      n = 0;
      lookAhead = path[len - 1];
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


namespace w {
  void robot::Robot::seek(float x, float y, pid::PID *transPID, pid::PID *rotPID) {
    float tA = rollPI(atan2(y - posTracker.y, x - posTracker.x) - posTracker.a);

    w::odom::Point close = closest({
      posTracker.x, posTracker.y                   // current
    }, { cos(posTracker.a), sin(posTracker.a)}, {  // head
      x, y                                         // target
    });

    float V = transPID->calculate(-dist(close, { posTracker.x, posTracker.y }), 0);

    float aP = atan2(close.y - posTracker.y, close.x - posTracker.x) - posTracker.a;
    aP = fmod(aP, (TAU)) * SGN(aP);
    if (abs(aP) > PI / 2) {
      V = -V;
      tA -= PI * SGN(aP);
    }


    float W = rotPID->calculate(tA, 0);

    float Vr = V + W;
    float Vl = V - W;

    float maxMag = std::max(abs(Vr), abs(Vl));

    if(maxMag > MAX_SPEED) {
      Vl = (Vl / maxMag) * MAX_SPEED;
      Vr = (Vr / maxMag) * MAX_SPEED;
    }

    if(fabs(Vr) < MIN_SPEED) Vr = MIN_SPEED * SGN(Vr);
    if(fabs(Vl) < MIN_SPEED) Vl = MIN_SPEED * SGN(Vl);

    RIGHT_DRIVE_SET(Vr);
    LEFT_DRIVE_SET(Vl);
  }

  void robot::Robot::moveTo(w::odom::Point target, float err, float exit) {
    w::pid::PID *transPID = new w::pid::PID(10, 0, 0, 0.001, 0.0001, MAX_SPEED, MIN_SPEED);
    w::pid::PID *rotPID = new w::pid::PID(2, 0, 0, 0.0001, 0.00001, MAX_SPEED, 0);

    std::uint32_t started = pros::millis();

    while(!withinErr(posTracker.x, posTracker.y, target.x, target.y, err)) {
      // if((pros::millis() - started) > exit) break;
      seek(target.x, target.y, transPID, rotPID);
      pros::delay(20);
    }

    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void robot::Robot::moveTo(w::odom::Point target, float err, w::pid::PIDConfig tPID, w::pid::PIDConfig rPID, float exit) {
    w::pid::PID *transPID = new w::pid::PID(tPID, 0.001, 0.0001);
    w::pid::PID *rotPID = new w::pid::PID(rPID, 0.0001, 0.00001);

    std::uint32_t started = pros::millis();

    while(!withinErr(posTracker.x, posTracker.y, target.x, target.y, err)) {
      // if((pros::millis() - started) > exit) break;

      seek(target.x, target.y, transPID, rotPID);
      pros::delay(20);
    }

    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void robot::Robot::moveTo(w::odom::Point target, w::pid::PIDConfig tPID, w::pid::PIDConfig rPID, float exit) {
    robot::Robot::moveTo(target, P_ERR, tPID, rPID);
  }

  void robot::Robot::moveToSimple(w::odom::Point target) {
    turnToFace(target, 60);
    moveFor(dist(posTracker.x, posTracker.y, target.x, target.y));
  }

  void robot::Robot::moveAlong(w::odom::Point wayPoints[], int len, float lookAhead, w::pid::PIDConfig tPID, w::pid::PIDConfig rPID, float err, float exit) {

    std::uint32_t started = pros::millis();
    w::pid::PID *transPID = new w::pid::PID(tPID, 0.001, 0.0001);
    w::pid::PID *rotPID = new w::pid::PID(rPID, 0.0001, 0.00001);

    while(!withinErr(posTracker.x, posTracker.y, wayPoints[len - 1].x, wayPoints[len - 1].y, err)) {
      w::odom::Point target = getTarget(wayPoints, len, { posTracker.x, posTracker.y }, lookAhead);

      if((pros::millis() - started) > exit) break;

      seek(target.x, target.y, transPID, rotPID);
      pros::delay(20);
    }

    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void robot::Robot::moveFor(float distIn, float exit) {
    w::odom::Point start = {
      posTracker.x,
      posTracker.y
    };

    mainPID.reset();
    mainPID.config(8, 0, 0.1, 0.001, 0.001, MAX_SPEED, MIN_SPEED);

    std::uint32_t started = pros::millis();

    mainPID.doPID(0, P_ERR, [=]() -> float {
      if((pros::millis() - started) > exit) return 0;
      return (fabs(distIn) - dist(start.x, start.y, posTracker.x, posTracker.y));
    }, [=](float output) -> void {
      RIGHT_DRIVE_SET_AUTO(SGN(-distIn) * output);
      LEFT_DRIVE_SET_AUTO(SGN(-distIn) * output);
    });
    RIGHT_DRIVE_SET_AUTO(0);
    LEFT_DRIVE_SET_AUTO(0);
  }

  void robot::Robot::turnToFace(float deg, float max) {
      mainPID.reset();
      robot::Robot::turnToFace(deg, { 1.4, 0, 0.4, max, MIN_SPEED, 3, 30 });
  }

  void robot::Robot::turnToFace(w::odom::Point point, w::pid::PIDConfig c) {
    turnToFace(TODEG(atan2(point.y - posTracker.y, point.x - posTracker.x)), c);
  }

  void robot::Robot::turnToFace(float deg, w::pid::PIDConfig c) {
    mainPID.reset();
    mainPID.config(c);

    if(withinRange(TODEG(posTracker.a), deg, A_ERR)) return;

    mainPID.doPID(deg, A_ERR, []() -> float {
      return TODEG(posTracker.a);
    }, [=](float output) -> void {
      RIGHT_DRIVE_SET(output);
      LEFT_DRIVE_SET(-output);
    });

    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void robot::Robot::turnToFace(w::odom::Point point, float max) {
    turnToFace(TODEG(atan2(point.y - posTracker.y, point.x - posTracker.x)), max);
  }

  void robot::Robot::combineSet(bool rev) {
    combine.move(rev ? 127 : -127);
  }

  void robot::Robot::feedBall(float exit) {
    std::uint32_t started = pros::millis();

    while(!limit.get_value()) {
      if((pros::millis() - started) > exit) return;
      INTAKE_SET(127);
    }
    INTAKE_SET(0);
  }

  void robot::Robot::reset() {
    tracker->reset();
  }

  bool robot::Robot::hasBall() {
    return !!limit.get_value();
  }

  void robot::Robot::flyUp(int rpm, std::function <void(float)> action) {
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

w::robot::Robot robot = w::robot::Robot(&posTracker, &mainPID);
