#ifndef BENZENE_HPP
#define BENZENE_HPP

#include "main.h"


#define TORAD(deg) ((deg) * (PI / 180))
#define TODEG(rad) ((rad) * (180 / PI))


namespace hc {
  namespace benzene {
    class Tracker {
    private:
      pros::ADIEncoder *lEncoder;
      pros::ADIEncoder *rEncoder;
      pros::ADIEncoder *cEncoder;
      pros::ADIGyro *gyro;

      float x;
      float y;
      float a;

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

      void debug();

      void track();
    };
  }
}

#endif
