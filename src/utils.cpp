#include "utils.h"

float degToRad(float deg) {
	return deg * M_PI / 180;
}





float angle(sf::Vector2f v) {
    return std::atan2(v.y, v.x);
}





float vectorToAngle(sf::Vector2f v1, sf::Vector2f v2) {
	auto r = std::atan2( v2.y - v1.y, v2.x - v1.x ) * 180 / M_PI;
	return r < 0 ? r + 360 : r;
}





std::vector<sf::Vector2f> getCirclePoints(float angle, float spread, float radius) {
    std::vector<sf::Vector2f> ret;
    const int maxpts = spread/M_PI*30;
    for(int i = 0; i < maxpts; ++i) {
        const float a = (angle - spread / 2.f) + (i * spread) / (maxpts - 1);
        ret.push_back(radius * sf::Vector2f(cos(a), sin(a)));
    }
    return ret;
}





bool isBetween(float value, float value1, float value2) {
	// make the angle from value1 to value2 to be <= 180 degrees
	float rAngle = fmod(fmod(value2 - value1, 360) + 360, 360);
	if(rAngle >= 180) std::swap(value1, value2);

	// check if it passes through zero
	if(value1 <= value2) return value >= value1 && value <= value2;
	else return value >= value1 || value <= value2;
}





float dist(sf::Vector2f point1, sf::Vector2f point2) {
	return hypot(point2.x-point1.x, point2.y-point1.y);
}