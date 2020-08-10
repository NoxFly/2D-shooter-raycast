#include "Ray.h"
#include "utils.h"
#include "cmath"

#include <iostream>


Ray::Ray(sf::Vector2f &position, float &heading, float angle, float &length):
    m_position(position),
    m_heading(heading),
    m_angle(angle),
    m_length(length)
{
    
}





Ray::~Ray() {

}





float Ray::heading() const {
    return atan2(direction().y, direction().x);
}





sf::Vector2f Ray::direction() const {
    return angleToVector(m_heading + m_angle);
}





sf::Vector2f Ray::position() const {
    return m_position;
}





float Ray::getAngle() const {
    return m_angle;
}





void Ray::setAngle(const float angle) {
    m_angle = angle;
}





void Ray::setLength(const float length) {
    if(length > 0) {
        m_length = length;
    }
}





sf::Vector2f Ray::cast(const std::vector<sf::Vector2f> &wall) {
    float x1 = wall[0].x;
    float y1 = wall[0].y;
    float x2 = x1 + wall[1].x;
    float y2 = y2 + wall[1].y;

    float x3 = m_position.x;
    float y3 = m_position.y;
    float x4 = m_position.x + (direction().x * m_length);
    float y4 = m_position.y + (direction().y * m_length);

    float delta, gamma, lambda;
    
    delta = (x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1);
    
    if(delta != 0) {
        lambda = ((y4 - y3) * (x4 - x1) + (x3 - x4) * (y4 - y1)) / delta;
        gamma = ((y1 - y2) * (x4 - x1) + (x2 - x1) * (y4 - y1)) / delta;

        if(0 < lambda && lambda < 1 && 0 < gamma && gamma < 1) {
            return sf::Vector2f(
                ((x1*y2 - y1*x2) * (x3 - x4) - (x1 - x2) * (x3*y4 - y3*x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)),
                ((x1*y2 - y1*x2) * (y3 - y4) - (y1 - y2) * (x3*y4 - y3*x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))
            );
        }
    }

    return sf::Vector2f(x4, y4);
}