#include "tracker.hpp"

float rollAnglePI(float angle) {
  return angle - TAU * std::floor((angle + PI) * (1.0 / TAU));
}

namespace jctc {
  namespace odom {
    void Tracker::debug() {
      //
    }

    void Tracker::step() {
      float newL = lEncoder->get_value();
      float newR = rEncoder->get_value();
      float newC = mEncoder->get_value();

      // // debuging encoders, uncoment to test if encoders are set up properly
      // std::cout << "newL : " << newL << std::endl;
      // std::cout << "newR : " << newR << std::endl;
      // std::cout << "newC : " << newC << std::endl;

      float dL = (lEncoderVal - newL) / WHEEL_SCALAR;
      float dR = (rEncoderVal - newR) / WHEEL_SCALAR;
      float dC = (mEncoderVal - newC) / WHEEL_SCALAR;

      lEncoderVal = newL;
      rEncoderVal = newR;
      mEncoderVal = newC;

      float newAngle = a + (((dL - dR) / (SL + SR)));
      float dA = newAngle - a;

      // std::cout << "dA: " << dA << std::endl;

      float dM = (dL + dR) / 2;

      float localOffX, localOffY;

      if(dA == 0) {
        localOffX = dC;
        localOffY = dM;
      } else {
        localOffX = 2 * sin(dA / 2) * ((dC / dA) + SS);
        localOffY = 2 * sin(dA / 2) * ((dM / dA) + (SL + SR) / 2);
      }

      float avgAngle = a + (dA / 2);

      float polarR = sqrt(std::pow(localOffX, 2) + std::pow(localOffY, 2));
      float polarA = (atan2(localOffY, localOffX)) - avgAngle;

      float dX = cos(polarA) * polarR;
      float dY = sin(polarA) * polarR;


      x += dX;
      y += dY;
      a = rollAnglePI(newAngle);
    }

    void Tracker::setPos(float x, float y, float a) {

    }

    void Tracker::setPos(Point pt, float a) {

    }

    void Tracker::setPos(Position pos) {

    }

    void reset() {

    }

  }
}
