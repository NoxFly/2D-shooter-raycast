#ifndef __WALL_H__
#define __WALL_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Wall {
	public:
		/**
		 * Create a wall
		 * @param x wall's x (top-left corner)
		 * @param y wall's y (top-left corner)
		 * @param width wall's width
		 * @param height wall's height
		 */
		Wall(float x, float y, float width, float height);
		~Wall();

		/**
		 * Draws the wall
		 * @param window the window we want to draw the wall
		 */
		void draw(sf::RenderWindow &window);

		/**
		 * GETTER - Gets the wall's position
		 * @return wall's position
		 */
		sf::Vector2f getPosition() const;

		/**
		 * GETTER - Gets the wall's size
		 * @return wall's size
		 */
		sf::Vector2f getSize() const;

	private:
		// wall's position
		sf::Vector2f m_position;

		// wall's size
		sf::Vector2f m_size;
};

#endif // wall