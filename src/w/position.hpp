#pragma once

namespace w {
  namespace odom {
    struct Point {
      float x, y;
    };
    struct Position {
      Point pos;
      float a;
    };

    float dist(::w::odom::Point a, ::w::odom::Point b);
    float dot(::w::odom::Point a, ::w::odom::Point b);
    Point add(Point a, Point b);
    Point sub(Point a, Point b);
    Point mult(Point a, Point b);
    Point mult(Point a, float b);
    Point div(Point a, Point b);
    float mag(::w::odom::Point a);
    Point normalize(Point a);

  }
}
