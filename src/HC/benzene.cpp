
#include "benzene.hpp"

namespace hc {
  void benzene::Tracker::debug() {
    // std::cout << "(" << x << ", " << y << ")  | " << TODEG(a) << std::endl;
  }

  void benzene::Tracker::track() {
    float newL = lEncoder->get_value();
    float newR = rEncoder->get_value();
    float newC = mEncoder->get_value();

    // std::cout << "newL : " << newL << std::endl;
    // std::cout << "newR : " << newR << std::endl;
    // std::cout << "newC : " << newC << std::endl;
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

    float avgA = a + (dA / 2);

    float dX = (cos(avgA) * dS) + (sin(avgA) * dC);
    float dY = (sin(avgA) * dS) + (cos(avgA) * dC);

    this->x -= dX;
    this->y -= dY;
    this->a = newA;

  }


  // Pilons: your shit is too hard
  // void benzene::Tracker::track() {
  //   float newL = lEncoder->get_value();
  //   float newR = rEncoder->get_value();
  //   float newC = mEncoder->get_value();
  //
  //   // std::cout << "newL : " << newL << std::endl;
  //   // std::cout << "newR : " << newR << std::endl;
  //   // std::cout << "newC : " << newC << std::endl;
  //
  //   float dL = (lEncoderVal - newL) / 41.69;
  //   float dR = (rEncoderVal - newR) / 41.69;
  //   float dC = (mEncoderVal - newC) / 41.69;
  //
  //   lEncoderVal = newL;
  //   rEncoderVal = newR;
  //   mEncoderVal = newC;
  //
  //   float newA = a + ((dL - dR) / (SL + SR)); // TODO: reset nodes?
  //   float dA = newA - a;
  //
  //   // std::cout << "dA: " << dA << std::endl;
  //
  //   float dS = (dL + dR) / 2;
  //
  //   float localOffX, localOffY;
  //
  //   if(dA != 0) {
  //     localOffX = 2 * sin(dA / 2) * ((dS / dA) + SR);
  //     localOffY = 2 * sin(dA / 2) * ((dC / dA) + SS);
  //   } else {
  //     localOffX = dS;
  //     localOffY = dC;
  //   }
  //
  //   float avgA = a + (dA / 2);
  //
  //   float polarR = sqrt((localOffX * localOffX) + (localOffY * localOffY));
  //   float polarA = atan2(localOffY, localOffX) - avgA;
  //
  //   float dX = cos(polarA) * polarR;
  //   float dY = sin(polarA) * polarR;
  //
  //
  //   this->x -= dX;
  //   this->y -= dY;
  //   this->a = newA;
  // }

  void benzene::Tracker::setPos(float x, float y, float a) {
    std::cout << "seting pos" << std::endl;
    this->x = x;
    this->y = y;
    this->a = TORAD(a);
  }

  void benzene::Tracker::setPos(benzene::Point pt, float a) {
    std::cout << "seting pos" << std::endl;
    this->x = pt.x;
    this->y = pt.y;
    this->a = TORAD(a);
  }

  void benzene::Tracker::reset() {
    lEncoder->reset();
    rEncoder->reset();
    mEncoder->reset();
  }

  void benzene::track(void *ptr) {
    benzene::Tracker* tracker = static_cast<benzene::Tracker*>(ptr);
    lv_obj_t * pos = lv_label_create(lv_scr_act(), NULL);
    lv_obj_align(pos, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 20);

    lv_label_set_text(pos,
      ("(" + std::to_string(tracker->x) + ", " +
      std::to_string(tracker->y) + ")  | " +
      std::to_string(TODEG(tracker->a))).c_str());


    while(true) {
      tracker->track();
      tracker->debug();

      lv_label_set_text(pos,
        ("(" + std::to_string(tracker->x) + ", " +
        std::to_string(tracker->y) + ")  | " +
        std::to_string(TODEG(tracker->a))).c_str());

      pros::delay(20);
    }
  }
}
