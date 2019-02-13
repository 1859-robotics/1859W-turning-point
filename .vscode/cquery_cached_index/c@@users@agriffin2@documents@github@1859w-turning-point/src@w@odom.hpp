#ifndef ODOM_HPP
#define ODOM_HPP

#include "main.h"
#include <math.h>

namespace w {
  namespace odom {
    typedef struct {
      float x;
      float y;
    } Point;

    class Tracker {
    private:
      pros::ADIEncoder *lEncoder;
      pros::ADIEncoder *rEncoder;
      pros::ADIEncoder *mEncoder;

      int lEncoderVal;
      int rEncoderVal;
      int mEncoderVal;

    public:
      Tracker(pros::ADIEncoder *lEncoder,
              pros::ADIEncoder *rEncoder,
              pros::ADIEncoder *mEncoder) :
              lEncoder(lEncoder),
              rEncoder(rEncoder),
              mEncoder(mEncoder) {};

      // for ease of use we make the x, y, and a vars public
      float x;
      float y;
      float a;

      void debug();
      void track();
      void setPos(float x, float y, float a);
      void setPos(Point pt, float a);
      void reset();
    };
    void track(void *tracker);
  }
}

#endif
