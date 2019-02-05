#ifndef ODOM_HPP
#define ODOM_HPP

#include "main.h"
#include <math.h>


#define TORAD(deg) ((deg) * (PI / 180))
#define TODEG(rad) ((rad) * (180 / PI))
#define SGN(in) (in == 0 ? 0 : (in > 0 ? 1 : -1))

#define WHEEL_D 41.69
#define SL 4.25
#define SR 4.25
#define SS 2.55

#define POINT_LIST(...) __VA_ARGS__

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

      float lEncoderVal;
      float rEncoderVal;
      float mEncoderVal;

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
