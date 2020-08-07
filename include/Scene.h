#ifndef __SCENE_H__
#define __SCENE_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>

#include "Input.h"
#include "Player.h"
#include "Wall.h"

class Scene {
	public:
		/**
		 * @param width window's width
		 * @param height window's height
		 * @param title window's title
		 */
		Scene(int width, int height, std::string title);

		/**
		 * On window's destruction
		 */
		~Scene();

		/**
		 * GETTER - get the window's width
		 * @return window's width
		 */
		int winWidth() const;

		/**
		 * GETTER - get the window's height
		 * @return window's height
		 */
		int winHeight() const;

		/**
		 * Create a wall
		 * @param x wall's x (top-left corner)
		 * @param y wall's y (top-left corner)
		 * @param width wall's width
		 * @param height wall's height
		 */
		void createWall(int x, int y, int width, int height);

		/**
		 * Runs the main loop of the scene
		 */
		void run();

	private:
		// main window of the scene
		sf::RenderWindow m_window;

		// input manager
		Input m_input;

		// player of the scene
		Player m_player;

		// walls of the scene
		std::vector<Wall*> m_walls;

		// cell's informations
		struct {
			float ratio;
			float cellSize;
			sf::Vector2i nCells;
		} m_cellContext;

		/**
		 * Draw the background grid
		 */
		void drawGrid();

		/**
		 * Update the player coords and inputs
		 */
		void updatePlayer();

		/**
		 * main loop of the scene
		 */
		void mainLoop();
};

#endif // scene