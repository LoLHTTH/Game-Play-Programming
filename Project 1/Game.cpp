#include "Game.h"

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[8];
GLubyte triangles[36];

float angle = 0.5f;

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	/* Vertices counter-clockwise winding */

	// FRONT FACE

	// Left Bottom
	vertex[0].coordinate[0] = -0.1f;
	vertex[0].coordinate[1] = -0.1f;
	vertex[0].coordinate[2] = 0.0f;
		  
	// Right Bottom
	vertex[1].coordinate[0] = 0.1f;
	vertex[1].coordinate[1] = -0.1f;
	vertex[1].coordinate[2] = 0.0f;

	// Top Left
	vertex[2].coordinate[0] = -0.1f;
	vertex[2].coordinate[1] = 0.1f;
	vertex[2].coordinate[2] = 0.0f;

	// Top Right
	vertex[3].coordinate[0] = 0.1f;
	vertex[3].coordinate[1] = 0.1f;
	vertex[3].coordinate[2] = 0.0f;

	// BACK FACE

	// Left Bottom
	vertex[4].coordinate[0] = -0.1f;
	vertex[4].coordinate[1] = -0.1f;
	vertex[4].coordinate[2] = -0.2f;

	// Right Bottom
	vertex[5].coordinate[0] = 0.1f;
	vertex[5].coordinate[1] = -0.1f;
	vertex[5].coordinate[2] = -0.2f;

	// Top Left
	vertex[6].coordinate[0] = -0.1f;
	vertex[6].coordinate[1] = 0.1f;
	vertex[6].coordinate[2] = -0.2f;

	// Top Right
	vertex[7].coordinate[0] = 0.1f;
	vertex[7].coordinate[1] = 0.1f;
	vertex[7].coordinate[2] = -0.2f;
		  
	//CYAN
	vertex[0].color[0] = 0.0f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 1.0f;

	//GREEN
	vertex[1].color[0] = 0.0f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	// PINK
	vertex[2].color[0] = 1.0f;
	vertex[2].color[1] = 0.411765f;
	vertex[2].color[2] = 0.705882f;

	//RED
	vertex[3].color[0] = 1.0f;
	vertex[3].color[1] = 0.0f;
	vertex[3].color[2] = 0.0f;

	//YELLOW
	vertex[4].color[0] = 1.0f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	//BLUE
	vertex[4].color[0] = 0.0f;
	vertex[4].color[1] = 0.0f;
	vertex[4].color[2] = 1.0f;
		  
	//INDIGO
	vertex[5].color[0] = 0.294118f;
	vertex[5].color[1] = 0.0f;
	vertex[5].color[2] = 0.509804f;

	//ORANGE
	vertex[6].color[0] = 1.0f;
	vertex[6].color[1] = 0.647059f;
	vertex[6].color[2] = 0;
	
	//DARK GREEN
	vertex[7].color[0] = 0.333333f;
	vertex[7].color[1] = 0.419608f;
	vertex[7].color[2] = 0.184314f;

	//FRONT
	triangles[0] = 3;   triangles[1] = 2;   triangles[2] = 0;
	triangles[3] = 3;   triangles[4] = 0;   triangles[5] = 1;

	//BACK
	triangles[30] = 6;   triangles[31] = 7;   triangles[32] = 5;
	triangles[33] = 6;   triangles[34] = 5;   triangles[35] = 4;

	//LEFT SIDE
	triangles[6] = 2;   triangles[7] = 6;   triangles[8] = 4;
	triangles[9] = 2;   triangles[10] = 4;   triangles[11] = 0;

	//RIGHT SIDE
	triangles[12] = 7;   triangles[13] = 3;   triangles[14] = 1;
	triangles[15] = 7;   triangles[16] = 1;   triangles[17] = 5;

	//TOP SIDE
	triangles[18] = 7;   triangles[19] = 6;   triangles[20] = 2;
	triangles[21] = 7;   triangles[22] = 2;   triangles[23] = 3;

	//BOT SIDE
	triangles[24] = 1;   triangles[25] = 0;   triangles[26] = 4;
	triangles[27] = 1;   triangles[28] = 4;   triangles[29] = 5;

	glEnable(GL_CULL_FACE);
	glTranslated(-0.45, 0.5, 0);

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Game::update()
{
	elapsed = clock.getElapsedTime();
	glRotated(0.1, 0.1, 0.1, 0.1);

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		/*rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}*/
		//rotation();
	}

	//Change vertex data
	//vertex[0].coordinate[0] += -0.0001f;
	//[0].coordinate[1] += -0.0001f;
	//vertex[0].coordinate[2] += -0.0001f;

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/

	// Draw TRIANGLE
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

//void rotatePoints(Vertex vertex[])
//{
//	Matrix matrixRotate;
//}
















