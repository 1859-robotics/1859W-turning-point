#include "benzene.hpp"

namespace hc {
  void benzene::Tracker::debug() {
    std::cout << "(" << x << ", " << y << ")  | " << a << std::endl;
  }

  void benzene::Tracker::track() {
    float newR = rEncoder->get_value();
    float newL = lEncoder->get_value();
    float newM = cEncoder->get_value();

    float dR = (newR - rEncoderVal) / 41.69;
    float dL = (newL - lEncoderVal) / 41.69;
    float dM = (newM - mEncoderVal) / 41.69;

    rEncoderVal = rEncoder->get_value();
    lEncoderVal = lEncoder->get_value();
    mEncoderVal = cEncoder->get_value();

    float dS = (dR + dL) / 2.0;
    float dA = (gyro->get_value() / 10) - a;

    if(abs(dA) > 100) dA -= -360 * SGN(dA);

    float avgA = ((dA + a) + a) / 2;


    float dX = dS * sin(TORAD(avgA)) - dM * cos(TORAD(avgA));
    float dY = dS * cos(TORAD(avgA)) + dM * sin(TORAD(avgA));

    x += dX;
    y += dY;
    a += dA;

  }

  void benzene::Tracker::setPos(float x, float y, float a) {
    x = x;
    y = y;
    a = a;
  }

  void benzene::Tracker::reset() {
    lEncoder->reset();
    rEncoder->reset();
    cEncoder->reset();
    gyro->reset();
  }

  void benzene::track(void *ptr) {
    benzene::Tracker* tracker = static_cast<benzene::Tracker*>(ptr);
    while(true) {
      tracker->track();
      tracker->debug();
      pros::delay(20);
    }
  }
}
