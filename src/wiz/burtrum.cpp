#include "wiz/burtrum.hpp"
#include "robot-config.hpp"

namespace wiz {
  void Burtrum::driveVector(float forward, float turn) {
    // This code is taken from WPIlib. All credit goes to them. Link:
    // https://github.com/wpilibsuite/allwpilib/blob/master/wpilibc/src/main/native/cpp/Drive/DifferentialDrive.cpp#L73

    float forwardSpeed = std::clamp<float>(forward, -MAX_SPEED, MAX_SPEED);
    float yaw = std::clamp<float>(turn, -MAX_SPEED, MAX_SPEED);

    float leftOutput = forwardSpeed + yaw;
    float rightOutput = forwardSpeed - yaw;
    float maxInputMag = std::max<float>(std::abs(leftOutput), std::abs(rightOutput));

    if (maxInputMag > MAX_SPEED) {
      leftOutput /= maxInputMag;
      rightOutput /= maxInputMag;

      RIGHT_DRIVE_SET(rightOutput * MAX_SPEED);
      LEFT_DRIVE_SET(leftOutput * MAX_SPEED);

    } else {
      RIGHT_DRIVE_SET(rightOutput);
      LEFT_DRIVE_SET(leftOutput);
    }
  }

  void Burtrum::reset() {
    tracker.reset();
  }
}
