#include "benzene.hpp"

namespace hc {
  void benzene::Tracker::debug() {
    std::cout << "(" << x << ", " << y << ")  | " << TODEG(a) << std::endl;
  }

  void benzene::Tracker::track() {
    float newR = rEncoder->get_value();
    float newL = lEncoder->get_value();
    float newM = cEncoder->get_value();

    float dR = (newR - rEncoderVal) / 41.69;
    float dL = (newL - lEncoderVal) / 41.69;
    float dM = (newM - mEncoderVal) / 41.69;

    rEncoderVal = newR;
    lEncoderVal = newL;
    mEncoderVal = newM;

    float dA = (dL - dR) / (SL + SR);

    float dX, dY;
    a += dA;

    if(dA != 0) {
    	dX = (2 * sin(a / 2) * ((dM / dA) + SS)) * cos(a);
    	dY = (2 * sin(a / 2) * ((dR / dA) + SR)) * sin(a);
    } else {
    	dX = dM;
    	dY = dR;
    }

    x += dX;
    y += dY;
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
