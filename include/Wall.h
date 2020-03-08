#ifndef __WALL_H__
#define __WALL_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Wall {
	public:
		Wall(float x1, float y1, float width, float height);
		~Wall();

		void draw(sf::RenderWindow &window);
		sf::Vector2f getPosition() const;
		sf::Vector2f getSize() const;

	private:
		sf::Vector2f m_position;
		sf::Vector2f m_size;
};

#endif // wall