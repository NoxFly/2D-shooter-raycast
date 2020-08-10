#ifndef __RAY_H__
#define __RAY_H__


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Wall.h"

class Ray {
    public:
        /**
         * Create a ray for an entity
         * @param position the pointer of the parent's position
         * @param angle the direction's angle of the ray
         */
        Ray(sf::Vector2f &position, float &heading, float angle, float &length);
        ~Ray();

        /**
         * GETTER - Returns the ray's heading
         * @return angle
         */
        float heading() const;

        /**
         * GETTER - Returns the ray vector's direction
         * @return 2d vector of floats
         */
        sf::Vector2f direction() const;

        /**
         * GETTER - Returns the ray's position
         * @return ray's position
         */
        sf::Vector2f position() const;

        /**
         * SETTER - Changes the ray's angle
         */
        void setAngle(const float angle);

        /**
         * GETTER - get the ray's angle
         */
        float getAngle() const;

        /**
         * SETTER - Changes the ray's length
         */
        void setLength(const float length);

        /**
         * Returns the intersection's point between the ray and a given wall
         * @param wall wall to test
         * @return intersection's point
         */
        sf::Vector2f cast(const std::vector<sf::Vector2f> &wall);



    private:
        // player's position
        sf::Vector2f &m_position;

        // player's heading
        float &m_heading;

        // ray's angle compared to the player's heading
        float m_angle;
        
        // ray's length
        float m_length;
};





#endif // RAY_H