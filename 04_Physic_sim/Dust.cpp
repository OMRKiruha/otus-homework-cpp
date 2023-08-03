
#include "Dust.h"

Dust::Dust() = default;

Dust::~Dust() = default;

Dust::Dust(Point center) {
    double radius = 5.;
    m_center = center;
    double startVelocity = 50.;
    Color color{0, 0, 0};
    bool isCollidable = false;
    // Заполняем вектор шарами
    // Начальная точка center

    // Количество и скорость вычисляем
    for (int i = 0; i < m_count; ++i) {
        Velocity velocity{startVelocity, 2 * M_PI * i / m_count};
        Ball ball(radius, m_center, velocity, color, isCollidable);
        m_flash.push_back(ball);
    }
}
void Dust::draw(Painter& painter) const {
    for(auto& spark : m_flash ){
        spark.draw(painter);
    }
}
std::vector<Ball>& Dust::getFlash() {
    return m_flash;
}
