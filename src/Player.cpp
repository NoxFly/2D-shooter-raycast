#include "Player.h"

#include <cmath>
#include <iostream>
#include <algorithm>

Player::Player(float x, float y): m_limits(0, 0), m_position(x, y), m_size(15), m_visionAngle(140), m_visionRange(200), m_heading(0), m_speed(2), m_rotationSpeed(0.05), m_dir(sf::Vector2f(cos(m_heading), sin(m_heading))), m_lookPoint(m_position.x + m_dir.x*m_visionRange, m_position.y + m_dir.y*m_visionRange) {
	
}

Player::~Player() {

}

void Player::setLimits(sf::Vector2f limits) {
	m_limits = limits;
}

void Player::setLimits(float x, float y) {
	m_limits = sf::Vector2f(x, y);
}

void Player::move(int x, int y) {
	move(sf::Vector2i(x, y));
}

void Player::move(sf::Vector2i vec) {
	sf::Vector2f velocity = sf::Vector2f(cos(m_heading), sin(m_heading));
	float speed = vec.y * m_speed;

	sf::Vector2f tmp(velocity.x, velocity.y);

	velocity.x = velocity.x * speed / hypot(tmp.x, tmp.y);
	velocity.y = velocity.y * speed / hypot(tmp.x, tmp.y);

	m_position.x += velocity.x;
	m_position.y += velocity.y;

	if(m_position.x - m_size < 0) m_position.x = m_size; // left limit
	if(m_position.y - m_size < 0) m_position.y = m_size; // top limit

	if(m_position.x + m_size > m_limits.x) m_position.x = m_limits.x - m_size; // right limit
	if(m_position.y + m_size > m_limits.y) m_position.y = m_limits.y - m_size; // bottom limit

	m_lookPoint = sf::Vector2f(m_position.x + m_dir.x*m_visionRange, m_position.y + m_dir.y*m_visionRange);
}

void Player::setPosition(float x, float y) {
	m_position.x = x;
	m_position.y = y;
	move(0, 0);
}

void Player::setPosition(sf::Vector2i v) {
	m_position = (sf::Vector2f)v;
	move(0, 0);
}

void Player::draw(sf::RenderWindow &window) {
	// draw the player
	sf::CircleShape circle(m_size, 15);
	circle.setFillColor(sf::Color(255, 160, 0));
	circle.setOrigin(m_size, m_size);
	circle.setPosition(m_position);
	window.draw(circle);

	/* sf::Vertex line[2] {
		sf::Vertex(m_position, sf::Color::Red),
		sf::Vertex(sf::Vector2f(m_position.x+m_dir.x*1000, m_position.y+m_dir.y*1000), sf::Color::Red)
	};
	window.draw(line, 2, sf::Lines); */
}

void Player::rotate(int direction) {
	m_heading += direction * m_rotationSpeed;
	m_dir = sf::Vector2f(cos(m_heading), sin(m_heading));
	m_lookPoint = sf::Vector2f(m_position.x + m_dir.x*m_visionRange, m_position.y + m_dir.y*m_visionRange);
}

void Player::collide(std::vector<Wall*> &walls) {
	for(auto wall : walls) {
		sf::Vector2f wallPos = wall->getPosition();
		sf::Vector2f wallSize = wall->getSize();

		if(m_position.x+m_size > wallPos.x && m_position.x-m_size < wallPos.x+wallSize.x  && m_position.y+m_size > wallPos.y && m_position.y -m_size < wallPos.y+wallSize.y) {
			std::vector<float> nearestBorder = {
				m_position.y+m_size - wallPos.y, // top
				wallPos.x+wallSize.x - m_position.x-m_size, // right
				wallPos.y+wallSize.y - m_position.y-m_size, // bottom
				m_position.x+m_size - wallPos.x // left
			};

			auto it = std::min_element(std::begin(nearestBorder), std::end(nearestBorder));
			std::size_t idx = std::distance(std::begin(nearestBorder), it);
			
			if(idx == 0) m_position.y = wallPos.y - m_size;
			else if(idx == 1) m_position.x = wallPos.x+wallSize.x + m_size;
			else if(idx == 2) m_position.y = wallPos.y+wallSize.y + m_size;
			else m_position.x = wallPos.x - m_size;
		}
	}
}



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

bool isAngleBetween(float target, float angle1, float angle2) {
	// make the angle from angle1 to angle2 to be <= 180 degrees
	float rAngle = fmod(fmod(angle2 - angle1, 360) + 360, 360);
	if(rAngle >= 180) std::swap(angle1, angle2);

	// check if it passes through zero
	if(angle1 <= angle2) return target >= angle1 && target <= angle2;
	else return target >= angle1 || target <= angle2;
}

float dist(sf::Vector2f point1, sf::Vector2f point2) {
	return hypot(point2.x-point1.x, point2.y-point1.y);
}

void Player::drawVision(sf::RenderWindow &window) {
	sf::VertexArray arr(sf::LinesStrip);

    arr.append(sf::Vertex(m_position, sf::Color::Green));
    
	for(sf::Vector2f v : getCirclePoints(angle(m_lookPoint - m_position), degToRad(m_visionAngle), m_visionRange))
		arr.append(sf::Vertex(m_position + v, sf::Color::Green));

    arr.append(sf::Vertex(m_position, sf::Color::Green));

	window.draw(arr);
}


void Player::sonar(sf::RenderWindow &window, std::vector<Wall*> &walls) {

	sf::Vector2f boundaries[2];

	float h = m_heading - degToRad(m_visionAngle/2);
	sf::Vector2f d(cos(h), sin(h));
	boundaries[0] = sf::Vector2f(m_position.x + d.x*m_visionRange, m_position.y + d.y*m_visionRange);
	
	h = m_heading + degToRad(m_visionAngle/2);
	d = sf::Vector2f(cos(h), sin(h));
	boundaries[1] = sf::Vector2f(m_position.x + d.x*m_visionRange, m_position.y + d.y*m_visionRange);

	float a[] = {
		std::min(vectorToAngle(m_position, boundaries[0]), vectorToAngle(m_position, boundaries[1])),
		std::max(vectorToAngle(m_position, boundaries[0]), vectorToAngle(m_position, boundaries[1]))
	};

	//

	std::vector<sf::Vector2f> closest = {};

	// c1 = vectorToAngle(m_position, sf::Vector2f(0, 0));
	// c2 = vectorToAngle(m_position, sf::Vector2f(m_limits.x, 0));
	// c3 = vectorToAngle(m_position, m_limits);
	// c4 = vectorToAngle(m_position, sf::Vector2f(0, m_limits.y));

	sf::Vector2f p1 = sf::Vector2f(0, 0);
	sf::Vector2f p2 = sf::Vector2f(m_limits.x, 0);
	sf::Vector2f p3 = m_limits;
	sf::Vector2f p4 = sf::Vector2f(0, m_limits.y);

	if(isUnderVision(p1, a)) closest.push_back(p1);
	if(isUnderVision(p2, a)) closest.push_back(p2);
	if(isUnderVision(p3, a)) closest.push_back(p3);
	if(isUnderVision(p4, a)) closest.push_back(p4);
	

	for(auto wall : walls) {
		sf::Vector2f wallSize = wall->getSize();
		
		p1 = wall->getPosition();
		p2 = sf::Vector2f(p1.x+wallSize.x, p1.y);
		p3 = sf::Vector2f(p1.x, p1.y+wallSize.y);
		p4 = sf::Vector2f(p1.x+wallSize.x, p1.y+wallSize.y);

		// add it ?
		if(isUnderVision(p1, a)) closest.push_back(p1);
		if(isUnderVision(p2, a)) closest.push_back(p2);
		if(isUnderVision(p3, a)) closest.push_back(p3);
		if(isUnderVision(p4, a)) closest.push_back(p4);
	}	

	// display closest vertex
	sf::Vertex line[2];
	line[0] = sf::Vertex(m_position, sf::Color::Red);
	
	for(auto vertex : closest) {
		line[1] = sf::Vertex(sf::Vector2f(vertex.x, vertex.y), sf::Color::Red);
		window.draw(line, 2, sf::Lines);
	}
}

bool Player::isUnderVision(sf::Vector2f &point, float *a) {
	int r = 0;
	
	// -- in visionAngle
	if(isAngleBetween(vectorToAngle(m_position, point), a[0], a[1])) r++;

	// -- in visionRange
	if(dist(m_position, point) <= dist(m_position, m_lookPoint)) r++;

	return r == 2;
}