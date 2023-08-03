
#ifndef PHYSICS_DUST_H
#define PHYSICS_DUST_H

#include <vector>

#include "Ball.hpp"
#include "World.h"


class Dust {
  public:
    Dust();
    ~Dust();

    Dust(Point center);

    void draw(Painter& painter) const;

  private:
    Point m_center;
    std::vector<Ball> m_flash;
    int m_count = 10;
};

#endif // PHYSICS_DUST_H
