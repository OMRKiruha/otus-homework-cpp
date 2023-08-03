#include "Ball.hpp"
#include <cmath>

/**
 * @brief Задать скорость шара
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    m_velocity = velocity;
}

/**
 * @brief Получить скорость шара
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return {m_velocity};
}

/**
 * @brief Выполняем отрисовку объекта
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(m_center, m_radius, m_color);
}

/**
 * @brief Задать координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    m_center = center;
}

/**
 * @brief Получить координаты центра объекта
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return m_center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius() не требуется
 */
double Ball::getRadius() const {
    return m_radius;
}

/**
 * @brief Возвращает массу объекта
 */
double Ball::getMass() const {
    return m_mass;
}

/**
 * @brief Конструктор от всех параметров
 * @details В нашем приложении считаем, что все шары состоят из одинакового
 * материала с фиксированной плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 **/
Ball::Ball(double radius, Point center, Velocity velocity, Color color,
           bool isCollidable)
    : m_radius(radius), m_mass(0.0), m_center(center), m_velocity(velocity),
      m_color(color), m_isCollidable(isCollidable) {
    m_mass = M_PI * pow(m_radius, 3.) * 4. / 3.;
}

bool Ball::isCollidableBalls(Ball& one, Ball& other) {
    return one.m_isCollidable && other.m_isCollidable;
}

bool Ball::getCollidable() {
    return m_isCollidable;
}
