#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>

#include "Wall.h"
#include "Ray.h"

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
		void rotate(int dir);

		/**
		 * Draws the player
		 */
		void draw(sf::RenderWindow &window);

		/**
		 * Returns the points of the player vision's rays that hit walls
		 */
		std::vector<sf::Vector2f> looks(std::vector<Wall*> &walls);

		/**
		 * Checks collision with given walls
		 * @param walls all walls that need to be checked
		 */
		void collide(std::vector<Wall*> &walls);

		/**
		 * Draws the player's vision
		 * @param window the window we must draw the vision
		 */
		void drawVision(sf::RenderWindow &window, std::vector<Wall*> &walls);


		/**
		 * GETTER - Gets the player's direction thanks his heading
		 * @return vector direction
		 */
		sf::Vector2f direction() const;



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

		// player circle's size
		int m_size;

		// where the player is looking at
		sf::Vector2f m_lookPoint;

		// player vision's rays
		std::vector<Ray> m_rays;
};

#endif // player