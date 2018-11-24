#include "benzene.hpp"

namespace hc {
  void benzene::Tracker::debug() {
    std::cout << "(" << x << ", " << y << ")  | " << a << std::endl;
  }

  void benzene::Tracker::track() {
    std::cout << "(" << x << ", " << y << ")  | " << a << std::endl;
  }
}
