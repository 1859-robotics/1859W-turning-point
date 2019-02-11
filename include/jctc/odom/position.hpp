#pragma once
#include "main.h"

namespace jctc {
  namespace odom {
    struct Point {
      float x;
      float y;
    };

    struct Position {
      Point coord;
      float a;
    };

    // operators
    Point add(Point, Point);
    Point sub(Point, Point);
    Point mult(Point, Point);
    Point mult(Point, float);
    Point div(Point, Point);

    // misc util stuff
    float mag(Point);
    float dot(Point, Point);
    float dist(Point, Point);
    float dist(Position, Position);
    Point normalize(Point);
    float angleBetween(Position, Position);

  }
}
