#ifndef GAME_H
#define GAME_H

#include <string>
#include <sstream>

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/wglew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <Debug.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Ground.h"
#include "Player.h"
#include "NPC.h"

using namespace std;
using namespace sf;
using namespace glm;

enum GameState
{
	play,
	gameover,
	win,
};

class Game
{
public:
	Game();
	Game(sf::ContextSettings settings);
	~Game();
	void run();
private:
	RenderWindow window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	string readShader();
	string readFragment();
	void createCube(glm::mat4 &model);

	// views
	sf::View m_fullView;
	sf::View m_leftView;
	sf::View m_rightView;
	// windows
	sf::RenderWindow m_windowLeft;
	sf::RenderWindow m_windowRight;
};

#endif