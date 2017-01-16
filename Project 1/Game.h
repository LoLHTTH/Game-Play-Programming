#include <iostream>
#include <gl/glew.h>
#include <gl/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

// CUSTOM MADE VECTORS AND MATRIXS
#include "Vector.h"
#include "Matrix.h"

#include <string.h>

using namespace std;
using namespace sf;
//using namespace gpp;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	//void rotatePoints(Vertex vertex[]);

	Clock clock;
	Time elapsed;

	float rotationAngle = 0.0f;
};