#pragma once

#include "main.h"
#include "position.hpp"

#include <math.h>

#define WHEEL_D 41.69
#define SL 4.25
#define SR 4.25
#define SS 2.55

namespace jctc {
  namespace odom {
    class Tracker {
    private:
      pros::ADIEncoder *lEncoder;
      pros::ADIEncoder *rEncoder;
      pros::ADIEncoder *mEncoder;

      int lEncoderVal;
      int rEncoderVal;
      int mEncoderVal;

      float x;
      float y;
      float a;
    public:
      Tracker(pros::ADIEncoder *lEncoder,
              pros::ADIEncoder *rEncoder,
              pros::ADIEncoder *mEncoder) :
              lEncoder(lEncoder),
              rEncoder(rEncoder),
              mEncoder(mEncoder) {};

      void debug();
      void step();
      void setPos(float x, float y, float a);
      void setPos(Point pt, float a);
      void setPos(Position pos);
      void reset();
    };
  }
}
