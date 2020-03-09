#include "Scene.h"

#include <algorithm>
#include <iostream>

Scene::Scene(int width, int height, std::string title): m_window(sf::VideoMode(width, height),  title), m_input(m_window), m_player(width/2, height/2), m_walls{}, m_cellContext{0, 40, sf::Vector2i(0,0)} {   
    // set the window at the center of the screen
	const auto desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i middleScreen(desktop.width/2 - width/2, desktop.height/2 - height/2);
	m_window.setPosition(middleScreen);

	// set the walk's limits to the user
	m_player.setLimits((sf::Vector2f)m_window.getSize());

	// define a cell ratio related to width/height window's properties
	m_cellContext.ratio = std::max((float)winWidth(), (float)winHeight()) / std::min((float)winWidth(), (float)winHeight());
	m_cellContext.ratio *= m_cellContext.cellSize;
	m_cellContext.nCells = sf::Vector2i(winWidth()/m_cellContext.ratio*m_cellContext.cellSize, winHeight()/m_cellContext.ratio*m_cellContext.cellSize);

	// create some walls
	createWall(2, 2, 1, 1);
	createWall(2, 5, 2, 3);
	createWall(4, 7, 5, 1);
	createWall(11, 7, 2, 1);
	createWall(8, 3, 2, 2);

	// then run the main loop
	mainLoop();
}

Scene::~Scene() {
	
}

int Scene::winWidth() const {
	return m_window.getSize().x;
}

int Scene::winHeight() const {
	return m_window.getSize().y;
}

void Scene::mainLoop() {
	while(m_window.isOpen()) {
		// update controls
        m_input.update();

		// then update player controls
		updatePlayer();

		// clear
		m_window.clear(sf::Color(255, 255, 255));

		// draw the grid
		drawGrid();

		m_player.sonar(m_window, m_walls); // play a sonar to detect which walls are closest

		m_player.drawVision(m_window);

		// draw the player
		m_player.draw(m_window);

		// draw all walls
		for(auto wall : m_walls) wall->draw(m_window);

		// then display everything
		m_window.display();
    }
}

void Scene::drawGrid() {
	// horizontal lines
	for(int i=0; i < m_cellContext.nCells.y; i++) {
		sf::RectangleShape lineH(sf::Vector2f(winWidth(), 1));
		lineH.setPosition(0, i*m_cellContext.ratio);
		lineH.setFillColor(sf::Color(200,200,200));

		m_window.draw(lineH);
	}

	// vertical lines
	for(int i=0; i < m_cellContext.nCells.x; i++) {
		sf::RectangleShape lineV(sf::Vector2f(1, winHeight()));
		lineV.setPosition(i*m_cellContext.ratio, 0);
		lineV.setFillColor(sf::Color(200,200,200));

		m_window.draw(lineV);
	}
}

void Scene::updatePlayer() {
	// move forward / backward
	if(m_input.isKeyDown(sf::Keyboard::Z)) m_player.move(0, 1);
	if(m_input.isKeyDown(sf::Keyboard::S)) m_player.move(0, -1);

	// rotate
	if(m_input.isKeyDown(sf::Keyboard::Q)) m_player.rotate(-1);
	if(m_input.isKeyDown(sf::Keyboard::D)) m_player.rotate(1);

	if(m_input.isMouseButtonDown(sf::Mouse::Left)) {
		m_player.setPosition(sf::Mouse::getPosition(m_window));
	}


	m_player.collide(m_walls); // detect physical collision with walls
}

void Scene::createWall(int x, int y, int width, int height) {
	// convert grid units to pixel units
	m_walls.push_back(new Wall((x-1)*m_cellContext.ratio, (y-1)*m_cellContext.ratio, width*m_cellContext.ratio, height*m_cellContext.ratio));
}