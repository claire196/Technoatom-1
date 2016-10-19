#include "bullett.h"
#include "ray2d.hpp"
#include "point2d.hpp"
#include "vector2d.hpp"


class Bullet: public Ray2D
{
  public:
   Bullet() : Ray2D ( Point2D orig, Vector2D dir);
}
