#include "Player.h"
#include "utils.h"

#include <limits>
#include <cmath>
#include <algorithm>
#include <stdlib.h>


Player::Player(float x, float y):
	m_limits(0, 0),
	m_position(x, y),
	m_size(15),
	m_visionAngle(140),
	m_visionRange(200),
	m_heading(0),
	m_speed(2),
	m_rotationSpeed(0.05),
	m_lookPoint(m_position.x + direction().x * m_visionRange, m_position.y + direction().y * m_visionRange),
	m_rays{}
{
	for(float i = -m_visionAngle/2; i < m_visionAngle/2; i += 1) {
		m_rays.push_back(Ray(m_position, m_heading, degToRad(i), m_visionRange));
	}
}



Player::~Player() {

}






sf::Vector2f Player::direction() const {
	return angleToVector(m_heading);
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

	m_lookPoint = sf::Vector2f(m_position.x + direction().x * m_visionRange, m_position.y + direction().y * m_visionRange);
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
	sf::CircleShape circle(m_size, 30);

	circle.setFillColor(sf::Color(255, 160, 0));
	circle.setOrigin(m_size, m_size);
	circle.setPosition(m_position);

	window.draw(circle);
}




void Player::drawVision(sf::RenderWindow &window, std::vector<Wall*> &walls) {
	sf::VertexArray arr(sf::TriangleFan);

	sf::Color color(0, 255, 0, 100);

    arr.append(sf::Vertex(m_position, color));
    
	for(auto v : looks(walls)) {
		arr.append(sf::Vertex(v, color));
	}

    arr.append(sf::Vertex(m_position, color));

	window.draw(arr);
}





void Player::rotate(int dir) {
	m_heading += dir * m_rotationSpeed;

	auto degHeading = radToDeg(m_heading);

	if(abs(degHeading) > 360.0) {
		m_heading -= dir * degToRad(360.0);
	}

	m_lookPoint = sf::Vector2f(m_position.x + direction().x * m_visionRange, m_position.y + direction().y * m_visionRange);
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
			

			if(idx == 0) 		m_position.y = wallPos.y - m_size;
			else if(idx == 1) 	m_position.x = wallPos.x + wallSize.x + m_size;
			else if(idx == 2) 	m_position.y = wallPos.y + wallSize.y + m_size;
			else 				m_position.x = wallPos.x - m_size;
		}

	}
}






std::vector<sf::Vector2f> Player::looks(std::vector<Wall*> &walls) {
	std::vector<sf::Vector2f> rays = {};

	std::vector<std::vector<sf::Vector2f>> wallEdges = {};

	for(auto& wall : walls) {
		for(auto i=0; i < 4; i++) {
			wallEdges.push_back((*wall)[i]);
		}
	}

	for(auto& ray : m_rays) {
		// which wall is the nearest from all other to the current ray - distance value
		float minimal = std::numeric_limits<double>::infinity();
		
		// vector intersection point of [this - minimal]
		sf::Vector2f closest;
		bool hasClosest = false;

		// for each wall
		for(auto& wall : wallEdges) {

			// get the intersection's point between the ray and the wall
			sf::Vector2f pt = ray.cast(wall);

			// then d is the distance betwwen the player and the intersection point
			float d = dist(m_position, pt);

			// if the distance between the player and the current wall is lower than the previous lower registered one
			if(d < minimal) {
				// register it as the new closest intersection point
				closest = pt;
				hasClosest = true;
			}
			
			minimal = std::min(d, minimal);
		
		}

		// if it intersects with at least one wall
		if(hasClosest) {
			// push that intersection point in the array of intersection points
			rays.push_back(closest);				
		}
		

	}

	return rays;
}