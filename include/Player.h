#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>

#include "Wall.h"

class Player {
	public:
		Player(float x, float y);
		~Player();

		void setLimits(sf::Vector2f limits);
		void setLimits(float x, float y);

		void move(int x, int y);
		void move(sf::Vector2i vec);
		void setPosition(float x, float y);
		void setPosition(sf::Vector2i v);
		void rotate(int direction);
		void draw(sf::RenderWindow &window);

		void collide(std::vector<Wall*> &walls);
		void sonar(sf::RenderWindow &window, std::vector<Wall*> &walls);
		void drawVision(sf::RenderWindow &window);

		bool isUnderVision(sf::Vector2f &point, float *a);

	private:
		sf::Vector2f m_limits;
		sf::Vector2f m_position;
		float m_visionAngle;
		float m_visionRange;
		float m_heading;
		float m_speed;
		float m_rotationSpeed;
		sf::Vector2f m_dir;
		int m_size;
		sf::Vector2f m_lookPoint;
};

#endif // player