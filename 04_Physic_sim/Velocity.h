#pragma once
#include "Point.h"
#include <cmath>

class Velocity {
  public:
    /**
     * @brief Конструктор по умолчанию
     */
    inline Velocity() = default;

    /**
     * @brief Конструктор скорости от полярных координат
     * @param abs - длина вектора
     * @param angle - угол наклона вектора
     */
    inline Velocity(double abs, double angle) {
        const double x = std::cos(angle);
        const double y = std::sin(angle);
        vec = Point{x, y} * abs;
    }

    /**
     * @brief Конструктор от точки
     * @param vector
     */
    inline Velocity(const Point& vector) {
        setVector(vector);
    }

    /**
     * @brief Установить значение вектора по точке
     * @param vector
     */
    inline void setVector(const Point& vector) {
        vec = vector;
    }

    /**
     * @brief Возвращает точку конца вектора
     * @return
     */
    inline Point vector() const {
        return vec;
    }

  private:
    Point vec;
};
