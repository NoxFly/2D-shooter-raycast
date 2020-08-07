#ifndef __UTILS_H__
#define __UTILS_H__


#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

/**
 * Converts degrees to radians
 * @param deg angle in degrees
 * @returns angle in radians
 */
float degToRad(float deg);

/**
 * Get the angle of a vector
 * @param v vector
 * @return the angle in radians
 */
float angle(sf::Vector2f v);

/**
 * Get the angle between two vectors
 * @param v1 first vector
 * @param v2 second vector
 * @return angle in radians
 */
float vectorToAngle(sf::Vector2f v1, sf::Vector2f v2);

/**
 * Get the points of an arc
 * @param angle the given arc
 * @param spread arc's point number
 * @param radius arc's radius
 * @return a series of points
 */
std::vector<sf::Vector2f> getCirclePoints(float angle, float spread, float radius);

/**
 * Knows if a point is in an angle
 * @param target the point
 * @param angle1
 * @return a boolean - if the point is between or not
 */
bool isBetween(float value, float value1, float value2);

/**
 * calculates the distance between 2 points
 * @param point1
 * @param point2
 * @return the distance between the 2 points
 */
float dist(sf::Vector2f point1, sf::Vector2f point2);




#endif // utils