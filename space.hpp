#include "space.h"
#include "box2d.hpp"
#include "gun.hpp"

class Space:public Box2D
{

public:
    Space(float m_bl = 0, float m_tl = 0):Box2D(bl,tr);
private:
    Gun g;
}
