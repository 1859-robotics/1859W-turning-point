
#include "benzene.hpp"

namespace hc {
  void benzene::Tracker::debug() {
    // std::cout << "(" << x << ", " << y << ")  | " << TODEG(a) << std::endl;
  }

  void benzene::Tracker::track() {
    float newL = lEncoder->get_value();
    float newR = rEncoder->get_value();
    float newC = mEncoder->get_value();

    std::cout << "newL : " << newL << std::endl;
    std::cout << "newR : " << newR << std::endl;
    std::cout << "newC : " << newC << std::endl;

    float dL = (lEncoderVal - newL) / 41.69;
    float dR = (rEncoderVal - newR) / 41.69;
    float dC = (mEncoderVal - newC) / 41.69;

    lEncoderVal = newL;
    rEncoderVal = newR;
    mEncoderVal = newC;

    float newA = a + ((dL - dR) / (SL + SR)); // TODO: reset nodes?
    float dA = newA - a;

    // std::cout << "dA: " << dA << std::endl;

    float dS = (dL + dR) / 2;

    float localOffX, localOffY;

    if(dA != 0) {
      localOffX = 2 * sin(dA / 2) * ((dC / dA) + SS);
      localOffY = 2 * sin(dA / 2) * ((dS / dA) + SR);
    } else {
      localOffX = dC;
      localOffY = dS;
    }

    float avgA = a + (dA / 2);

    float polarR = sqrt((localOffX * localOffX) + (localOffY * localOffY));
    float polarA = atan2(localOffY, localOffX) - avgA;

    float dX = cos(polarA) * polarR;
    float dY = sin(polarA) * polarR;


    this->x += dX;
    this->y -= dY;
    this->a = newA;
  }

  void benzene::Tracker::setPos(float x, float y, float a) {
    std::cout << "seting pos" << std::endl;
    this->x = x;
    this->y = y;
    this->a = a;
  }

  void benzene::Tracker::setPos(benzene::Point pt, float a) {
    std::cout << "seting pos" << std::endl;
    this->x = pt.x;
    this->y = pt.y;
    this->a = a;
  }

  void benzene::Tracker::reset() {
    lEncoder->reset();
    rEncoder->reset();
    mEncoder->reset();
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
