#include "wiz/burtrum.hpp"

namespace wiz {
  void Burtrum::driveVector(float forward, float turn) {
    // This code is taken from WPIlib. All credit goes to them. Link:
    // https://github.com/wpilibsuite/allwpilib/blob/master/wpilibc/src/main/native/cpp/Drive/DifferentialDrive.cpp#L73

    const float forwardSpeed = std::clamp<float>(forward, -MAX_SPEED, MAX_SPEED);
    const float yaw = std::clamp<float>(turn, -MAX_SPEED, MAX_SPEED);

    float leftOutput = forwardSpeed + yaw;
    float rightOutput = forwardSpeed - yaw;
    if (const float maxInputMag = std::max<float>(std::abs(leftOutput), std::abs(rightOutput));
        maxInputMag > MAX_SPEED) {
        leftOutput /= maxInputMag;
        rightOutput /= maxInputMag;
      }
      RIGHT_DRIVE_SET(rightOutput);
      LEFT_DRIVE_SET(leftOutput);
  }
}
