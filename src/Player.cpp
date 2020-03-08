#include "Player.h"

#include <cmath>
#include <iostream>
#include <algorithm>

Player::Player(float x, float y): m_limits(0, 0), m_position(x, y), m_size(15), m_visionAngle(90), m_visionRange(200), m_heading(0), m_speed(2), m_rotationSpeed(0.05), m_dir(sf::Vector2f(cos(m_heading), sin(m_heading))), m_lookPoint(m_position.x + m_dir.x*m_visionRange, m_position.y + m_dir.y*m_visionRange) {
	
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
    const int maxpts = 10;
    for(int i = 0; i < maxpts; ++i) {
        const float a = (angle - spread / 2.f) + (i * spread) / (maxpts - 1);
        ret.push_back(radius * sf::Vector2f(cos(a), sin(a)));
    }
    return ret;
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

	sf::Vertex v1[] = {sf::Vertex(m_position, sf::Color::Blue), sf::Vertex(boundaries[0], sf::Color::Blue)};
	sf::Vertex v2[] = {sf::Vertex(m_position, sf::Color::Blue), sf::Vertex(boundaries[1], sf::Color::Blue)};

	window.draw(v1, 2, sf::Lines);
	window.draw(v2, 2, sf::Lines);

	float a1 = std::min(vectorToAngle(m_position, boundaries[0]), vectorToAngle(m_position, boundaries[1]));
	float a2 = std::max(vectorToAngle(m_position, boundaries[0]), vectorToAngle(m_position, boundaries[1]));

	printf("a1: %f | a2: %f\n", a1, a2);
	//

	std::vector<sf::Vector2f> closest = {};

	float c1, c2, c3, c4;

	c1 = vectorToAngle(m_position, sf::Vector2f(0, 0));
	c2 = vectorToAngle(m_position, sf::Vector2f(m_limits.x, 0));
	c3 = vectorToAngle(m_position, m_limits);
	c4 = vectorToAngle(m_position, sf::Vector2f(0, m_limits.y));

	printf("c1: %f, c2: %f, c3: %f, c4: %f\n", c1, c2, c3, c4);

	if(a1 < c1 && c1 < a2) closest.push_back(sf::Vector2f(0, 0));
	if(a1 < c2 && c2 < a2) closest.push_back(sf::Vector2f(m_limits.x, 0));
	if(a1 < c3 && c3 < a2) closest.push_back(m_limits);
	if(a1 < c4 && c4 < a2) closest.push_back(sf::Vector2f(0, m_limits.y));

	for(auto wall : walls) {
		sf::Vector2f wallPos = wall->getPosition();
		sf::Vector2f wallSize = wall->getSize();

		c1 = vectorToAngle(m_position, wallPos);
		c2 = vectorToAngle(m_position, sf::Vector2f(wallPos.x+wallSize.x, wallPos.y));
		c3 = vectorToAngle(m_position, sf::Vector2f(wallPos.x, wallPos.y+wallSize.y));
		c4 = vectorToAngle(m_position, sf::Vector2f(wallPos.x+wallSize.x, wallPos.y+wallSize.y));

		// store the 4 vertex of the wall if they validate all requires
		// -- in visionAngle
		if(a1 < c1 && c1 < a2) closest.push_back(wallPos);
		if(a1 < c2 && c2 < a2) closest.push_back(sf::Vector2f(wallPos.x+wallSize.x, wallPos.y));
		if(a1 < c3 && c3 < a2) closest.push_back(sf::Vector2f(wallPos.x, wallPos.y+wallSize.y));
		if(a1 < c4 && c4 < a2) closest.push_back(sf::Vector2f(wallPos.x+wallSize.x, wallPos.y+wallSize.y));
	}

	// eliminate who's not in the visionAngle
	// eliminate who's not in the visionRange
	// eliminate who's not the closest
	

	// display closest vertex
	sf::Vertex line[2];
	line[0] = sf::Vertex(m_position, sf::Color::Red);
	
	for(auto vertex : closest) {
		line[1] = sf::Vertex(sf::Vector2f(vertex.x, vertex.y), sf::Color::Red);
		window.draw(line, 2, sf::Lines);
	}
}