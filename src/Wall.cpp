#include "Wall.h"

Wall::Wall(float x1, float y1, float width, float height): m_position(x1+3, y1+3), m_size(width-6, height-6) {

}

Wall::~Wall() {

}

void Wall::draw(sf::RenderWindow &window) {
	sf::RectangleShape rect(m_size);
	rect.setPosition(m_position);
	rect.setFillColor(sf::Color(220,220,220));
	rect.setOutlineColor(sf::Color(100,100,100));
	rect.setOutlineThickness(3);

	window.draw(rect);
}

sf::Vector2f Wall::getPosition() const {
	return sf::Vector2f(m_position.x-3, m_position.y-3);
}

sf::Vector2f Wall::getSize() const {
	return sf::Vector2f(m_size.x+6, m_size.y+6);
}