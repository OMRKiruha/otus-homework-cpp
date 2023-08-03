#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Ball {
  public:
    Ball() = default;

    Ball(double radius, Point center, Velocity velocity, Color color,
         bool isCollidable);

    ~Ball() = default;

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;

    void draw(Painter& painter) const;

    void setCenter(const Point& center);
    Point getCenter() const;

    double getRadius() const;
    double getMass() const;

    static bool isCollidableBalls(Ball& one, Ball& other);
    bool getCollidable();

  private:
    double m_radius{};
    double m_mass{};
    Point m_center;
    Velocity m_velocity;
    Color m_color;
    bool m_isCollidable;
};
