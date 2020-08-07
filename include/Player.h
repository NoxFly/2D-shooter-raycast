#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>

#include "Wall.h"

class Player {
	public:
		/**
		 * Create a player
		 * @param x player's position x
		 * @param y player's position y
		 */
		Player(float x, float y);

		/**
		 * On player's destruction
		 */
		~Player();

		/**
		 * Sets the limit of the player, who cannot surpass the limits
		 * @param limits
		 */
		void setLimits(sf::Vector2f limits);

		/**
		 * Sets the limit of the player, who cannot surpass the limits
		 * @param x
		 * @param y
		 */
		void setLimits(float x, float y);

		/**
		 * moves the player
		 * @param x movement's x
		 * @param y movement's y
		 */
		void move(int x, int y);

		/**
		 * moves the player
		 * @param vec movement (x, y)
		 */
		void move(sf::Vector2i vec);

		/**
		 * Sets immediate player's position
		 * @param x new player's position x
		 * @param y new player's position y
		 */
		void setPosition(float x, float y);

		/**
		 * Sets immediate player's position
		 * @param v new player's position (x, y)
		 */
		void setPosition(sf::Vector2i v);

		/**
		 * Rotates the player's heading
		 */
		void rotate(int direction);

		/**
		 * Draws the player
		 */
		void draw(sf::RenderWindow &window);

		/**
		 * Checks collision with given walls
		 * @param walls all walls that need to be checked
		 */
		void collide(std::vector<Wall*> &walls);

		/**
		 * Draws a red line on every walls that are on the player's vision
		 * @param window the window we will draw the red lines
		 * @param walls the walls to check
		 */
		void sonar(sf::RenderWindow &window, std::vector<Wall*> &walls);

		/**
		 * Draws the player's vision
		 * @param window the window we must draw the vision
		 */
		void drawVision(sf::RenderWindow &window);

		/**
		 * Check if a given point is in the player's vision
		 * @param point the given point the check
		 * @param a the player's vision range limit on both extremities
		 * @return either the point is in the player's vision
		 */
		bool isUnderVision(sf::Vector2f &point, float *a);

	private:
		// limits the player cannot surpass
		sf::Vector2f m_limits;
		
		//  player's position
		sf::Vector2f m_position;

		// player vision's angle
		float m_visionAngle;

		// player vision's range
		float m_visionRange;

		// player's heading
		float m_heading;

		// player's speed
		float m_speed;

		// player's rotation's speed
		float m_rotationSpeed;

		// 
		sf::Vector2f m_dir;

		// player circle's size
		int m_size;

		// where the player is looking at
		sf::Vector2f m_lookPoint;
};

#endif // player