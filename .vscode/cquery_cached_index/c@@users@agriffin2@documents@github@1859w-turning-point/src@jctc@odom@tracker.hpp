#pragma once

#include "main.h"
#include "position.hpp"

#include <math.h>

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
      Tracker(pros::ADIEncoder *lEncoder, pros::ADIEncoder *rEncoder, pros::ADIEncoder *mEncoder) :
              lEncoder(lEncoder), rEncoder(rEncoder), mEncoder(mEncoder) {};

      void debug();
      void step();
      void setPos(float x, float y, float a);
      void setPos(Point pt, float a);
      void setPos(Position pos);
      Position getPos();
      void reset();
    };
  }
}
