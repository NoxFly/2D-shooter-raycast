#include "Wall.h"





Wall::Wall(float x, float y, float width, float height):
	m_borderThickness(3),
	m_position(x + m_borderThickness, y + m_borderThickness),
	m_size(width - 2*m_borderThickness, height - 2*m_borderThickness)
{

}




Wall::~Wall() {

}





std::vector<sf::Vector2f> Wall::operator[](int pos) {
	std::vector<sf::Vector2f> wallPos = {};

	switch(pos) {
		case 0: // top
			wallPos.push_back(m_position);
			wallPos.push_back(sf::Vector2f(m_position.x + m_size.x, m_position.y));
			break;

		case 1: // right
			wallPos.push_back(sf::Vector2f(m_position.x + m_size.x, m_position.y));
			wallPos.push_back(m_position + m_size);
			break;
		
		case 2: // bottom
			wallPos.push_back(sf::Vector2f(m_position.x, m_position.y + m_size.y));
			wallPos.push_back(m_position + m_size);
			break;
		
		case 3: // left
			wallPos.push_back(m_position);
			wallPos.push_back(sf::Vector2f(m_position.x, m_position.y + m_size.y));
			break;
		
		default:
			break;
	}

	return wallPos;
}






void Wall::draw(sf::RenderWindow &window) {
	sf::RectangleShape rect(m_size);

	rect.setPosition(m_position);
	rect.setFillColor(sf::Color(220,220,220));
	rect.setOutlineColor(sf::Color(100,100,100));
	rect.setOutlineThickness(m_borderThickness);

	window.draw(rect);
}





sf::Vector2f Wall::getPosition() const {
	return sf::Vector2f(m_position.x - m_borderThickness, m_position.y - m_borderThickness);
}





sf::Vector2f Wall::getSize() const {
	return sf::Vector2f(m_size.x + 2*m_borderThickness, m_size.y + 2*m_borderThickness);
}