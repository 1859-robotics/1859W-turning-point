#ifndef BENZENE_HPP
#define BENZENE_HPP

#include "main.h"
#include <math.h>


#define TORAD(deg) ((deg) * (PI / 180))
#define TODEG(rad) ((rad) * (180 / PI))
#define SGN(in) (in == 0 ? 0 : (in > 0 ? 1 : -1))

#define WHEEL_D 41.69
#define SL 1 // TODO: measure all of these
#define SR 1
#define SS 1

#define POINT_LIST(...) __VA_ARGS__

namespace hc {
  namespace benzene {
    class Tracker {
    private:
      pros::ADIEncoder *lEncoder;
      pros::ADIEncoder *rEncoder;
      pros::ADIEncoder *cEncoder;
      pros::ADIGyro *gyro;

      float lEncoderVal;
      float rEncoderVal;
      float mEncoderVal;

      float gyroVal;
    public:
      Tracker(pros::ADIEncoder *lEncoder,
              pros::ADIEncoder *rEncoder,
              pros::ADIEncoder *cEncoder,
              pros::ADIGyro *gyro) :
              lEncoder(lEncoder),
              rEncoder(rEncoder),
              cEncoder(cEncoder),
              gyro(gyro) {};

      // for ease of use we make the x, y, and a vars public
      float x;
      float y;
      float a;

      void debug();
      void track();
      void setPos(float x, float y, float a);
      void reset();
    };
    void track(void *tracker);

    typedef struct {
      int x;
      int y;
    } Point;
  }
}

#endif
