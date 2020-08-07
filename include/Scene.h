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
		Scene(int width, int height, std::string title);
		~Scene();

		int winWidth() const;
		int winHeight() const;

	private:
		sf::RenderWindow m_window;
		Input m_input;
		Player m_player;
		std::vector<Wall*> m_walls;

		struct {
			float ratio;
			float cellSize;
			sf::Vector2i nCells;
		} m_cellContext;

		void drawGrid();
		void updatePlayer();
		void mainLoop();

		void createWall(int x, int y, int width, int height);
};

#endif // scene