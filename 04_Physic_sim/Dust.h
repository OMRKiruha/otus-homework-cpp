
#ifndef PHYSICS_DUST_H
#define PHYSICS_DUST_H

#include <vector>

#include "Ball.hpp"

class Dust {
  public:
    Dust();
    ~Dust();

    Dust(Point center);

    void draw(Painter& painter) const;

    std::vector<Ball>& getFlash();

    inline void dropTTL() {
        timeToLive--;
    }

    inline int getTTL() const {
        return timeToLive;
    }

  private:
    Point m_center;
    std::vector<Ball> m_flash;
    int m_count = 10;
    int timeToLive = 2000;
};

#endif // PHYSICS_DUST_H
