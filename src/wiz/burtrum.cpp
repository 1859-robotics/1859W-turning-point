#include "wiz/burtrum.hpp"
#include "robot-config.hpp"

static bool withinRange(float target, float current, float error) {
  return fabs(target - current) < error;
}

namespace wiz {
  void Burtrum::driveVector(float forward, float turn) const {
    // This code is taken from WPIlib. All credit goes to them. Link:
    // https://github.com/wpilibsuite/allwpilib/blob/master/wpilibc/src/main/native/cpp/Drive/DifferentialDrive.cpp#L73

    float forwardSpeed = std::clamp<float>(forward, -MAX_SPEED, MAX_SPEED);
    float yaw = std::clamp<float>(turn, -MAX_SPEED, MAX_SPEED);

    float leftOutput = forwardSpeed + yaw;
    float rightOutput = forwardSpeed - yaw;
    float maxInputMag = std::max<float>(std::abs(leftOutput), std::abs(rightOutput));

    if (maxInputMag > 40) {
      leftOutput /= maxInputMag;
      rightOutput /= maxInputMag;

      RIGHT_DRIVE_SET(rightOutput * 40);
      LEFT_DRIVE_SET(leftOutput * 40);

    } else {
      RIGHT_DRIVE_SET(rightOutput);
      LEFT_DRIVE_SET(leftOutput);
    }
  }

  void Burtrum::reset() {
    tracker.reset();
  }

  void Burtrum::combineSet(bool rev) {
    combine.move(rev ? 127 : -127);
  }

  void Burtrum::feedBall(float exit) {
    std::uint32_t started = pros::millis();

    while(!limit.get_value()) {
      if((pros::millis() - started) > exit) return;
      INTAKE_SET(127);
    }
    INTAKE_SET(0);
  }

  bool Burtrum::hasBall() {
    return !!limit.get_value();
  }

  void Burtrum::flyUp(int rpm, std::function <void(float)> action) {
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


  void Burtrum::moveToTest(odom::Point target, float acceptableErr, unsigned int timeout) {
    while(!withinErr(target, tracker.getPos().pos, P_ERR)) {
      odom::Position state = tracker.getPos();

      odom::Point close = odom::closest({
        state.pos.x, state.pos.y                          // current
      }, { (float)cos(state.a), (float)sin(state.a) }, {  // head
        target.x, target.y                                // target
      });

      // float angleErr = angleToPoint({ target.x, target.y });
      float angleErr = fmod((atan2(target.y - state.pos.y, target.x - state.pos.x)) - state.a, TAU);
      if(std::isnan(angleErr)) angleErr = 0;
      if(fabs(angleErr) < acceptableErr) angleErr = 0;

      float distanceErr = distanceToPoint(close);

      float aP = atan2(close.y - state.pos.y, close.x - state.pos.x) - state.a;
      aP = fmod(aP, (TAU)) * SGN(aP);
      if (abs(aP) > PI / 2) {
        distanceErr = -distanceErr;
        angleErr -= PI * SGN(aP);
      }

      float angleVel = turnPid.calculate(angleErr, 0);
      float distanceVel = distPid.calculate(-distanceErr, 0);

      LOG_VAR(TODEG(angleErr));

      // std::cout << "state: "; odom::print(state);
      // std::cout << "target: "; odom::print(target);
      // std::cout << "close: "; odom::print(close);

      // driveVector(distanceVel, angleVel);

      pros::delay(20);
    }
    driveVector(0, 0);
  }
}
