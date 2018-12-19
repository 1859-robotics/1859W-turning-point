
#include "benzene.hpp"

namespace hc {
  void benzene::Tracker::debug() {
    std::cout << "(" << x << ", " << y << ")  | " << TODEG(a) << std::endl;
  }

  void benzene::Tracker::track() {
    float newL = lEncoder->get_value();
    float newR = rEncoder->get_value();
    float newC = mEncoder->get_value();

    float dL = (lEncoderVal - newL) / 41.69;
    float dR = (rEncoderVal - newR) / 41.69;
    float dC = (mEncoderVal - newC) / 41.69;

    lEncoderVal = newL;
    rEncoderVal = newR;
    mEncoderVal = newC;

    float newA = a + ((dL - dR) / (SL + SR)); // TODO: reset nodes?
    float dA = newA - a;

    // std::cout << "dA: " << dA << std::endl;

    float localOffX, localOffY;

    if(dA != 0) {
      localOffX = 2 * sin(dA / 2) * ((dC / dA) + SS);
      localOffY = 2 * sin(dA / 2) * ((dR / dA) + SR);
    } else {
      localOffX = dC;
      localOffY = dR;
    }

    float avgA = a + (dA / 2);

    float polarR = sqrt((localOffX * localOffX) + (localOffY * localOffY));
    float polarA = atan2(localOffY, localOffX) - avgA;

    float dX = cos(polarA) * polarR;
    float dY = sin(polarA) * polarR;

    x += dX;
    y += dY;
    a = newA;
  }

  void benzene::Tracker::setPos(float x, float y, float a) {
    x = x;
    y = y;
    a = a;
  }

  void benzene::Tracker::reset() {
    lEncoder->reset();
    rEncoder->reset();
    mEncoder->reset();
  }

  void benzene::track(void *ptr) {
    std::cout << "tracking began" << std::endl;
    benzene::Tracker* tracker = static_cast<benzene::Tracker*>(ptr);
    while(true) {
      tracker->track();
      tracker->debug();
      pros::delay(20);
    }
    std::cout << "tracking ended?" << std::endl;
  }
}
