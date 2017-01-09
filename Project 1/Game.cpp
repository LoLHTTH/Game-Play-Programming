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

Vertex vertex1[6];
GLubyte triangles[6];

Vertex vertex2[6];
Vertex vertex3[6];
Vertex vertex4[6];
Vertex vertex5[6];
Vertex vertex6[6];

float angle = 0.5f;
Matrix matrixRotation;
Matrix matrixScale;

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;
	matrixRotation = matrixRotation.rotation(angle);
	matrixScale = matrixScale.scale(100.5f, 100.5f);

	glewInit();

	/* Vertices counter-clockwise winding */
	// VERTEX 1 - Front

	vertex1[0].coordinate[0] = -0.5f;
	vertex1[0].coordinate[1] = -0.5f;
	vertex1[0].coordinate[2] = 0.0f;
		  
	vertex1[1].coordinate[0] = -0.5f;
	vertex1[1].coordinate[1] = 0.5f;
	vertex1[1].coordinate[2] = 0.0f;
		  
	vertex1[2].coordinate[0] = 0.5f;
	vertex1[2].coordinate[1] = 0.5f;
	vertex1[2].coordinate[2] = 0.0f;
		  
	vertex1[3].coordinate[0] = 0.5f; 
	vertex1[3].coordinate[1] = 0.5f;  
	vertex1[3].coordinate[2] = 0.0f;
		  
	vertex1[4].coordinate[0] = 0.5f; 
	vertex1[4].coordinate[1] = -0.5f;  
	vertex1[4].coordinate[2] = 0.0f;
		  
	vertex1[5].coordinate[0] = -0.5f; 
	vertex1[5].coordinate[1] = -0.5f;  
	vertex1[5].coordinate[2] = 0.0f;
		  
	vertex1[0].color[0] = 0.1f;
	vertex1[0].color[1] = 1.0f;
	vertex1[0].color[2] = 0.0f;
		  
	vertex1[1].color[0] = 0.2f;
	vertex1[1].color[1] = 1.0f;
	vertex1[1].color[2] = 0.0f;
		  
	vertex1[2].color[0] = 0.3f;
	vertex1[2].color[1] = 1.0f;
	vertex1[2].color[2] = 0.0f;

	vertex1[3].color[0] = 0.4f;
	vertex1[3].color[1] = 1.0f;
	vertex1[3].color[2] = 0.0f;

	vertex1[4].color[0] = 0.5f;
	vertex1[4].color[1] = 1.0f;
	vertex1[4].color[2] = 0.0f;

	vertex1[5].color[0] = 0.6f;
	vertex1[5].color[1] = 1.0f;
	vertex1[5].color[2] = 0.0f;

	// VERTEX 2 - Back

	vertex2[0].coordinate[0] = -0.3f;
	vertex2[0].coordinate[1] = -0.3f;
	vertex2[0].coordinate[2] = 0;
		  
	vertex2[1].coordinate[0] = -0.3f;
	vertex2[1].coordinate[1] = 0.3f;
	vertex2[1].coordinate[2] = 0;
		  
	vertex2[2].coordinate[0] = 0.3f;
	vertex2[2].coordinate[1] = 0.3f;
	vertex2[2].coordinate[2] = 0;
		  
	vertex2[3].coordinate[0] = 0.3f;
	vertex2[3].coordinate[1] = 0.3f;
	vertex2[3].coordinate[2] = 0;
		  
	vertex2[4].coordinate[0] = 0.3f;
	vertex2[4].coordinate[1] = -0.3f;
	vertex2[4].coordinate[2] = 0;
		  
	vertex2[5].coordinate[0] = -0.3f;
	vertex2[5].coordinate[1] = -0.3f;
	vertex2[5].coordinate[2] = 0;

	vertex2[0].color[0] = 0.1f;
	vertex2[0].color[1] = 1.0f;
	vertex2[0].color[2] = 1.0f;
		  
	vertex2[1].color[0] = 0.2f;
	vertex2[1].color[1] = 1.0f;
	vertex2[1].color[2] = 1.0f;
		  
	vertex2[2].color[0] = 0.3f;
	vertex2[2].color[1] = 1.0f;
	vertex2[2].color[2] = 1.0f;
		  
	vertex2[3].color[0] = 0.4f;
	vertex2[3].color[1] = 1.0f;
	vertex2[3].color[2] = 1.0f;
		  
	vertex2[4].color[0] = 0.5f;
	vertex2[4].color[1] = 1.0f;
	vertex2[4].color[2] = 1.0f;
		  
	vertex2[5].color[0] = 0.6f;
	vertex2[5].color[1] = 1.0f;
	vertex2[5].color[2] = 1.0f;

	// VERTEX 3 - Top

	vertex3[0].coordinate[0] = -0.5f;
	vertex3[0].coordinate[1] = 0.5f;
	vertex3[0].coordinate[2] = 0;
		  
	vertex3[1].coordinate[0] = 0.5f;
	vertex3[1].coordinate[1] = 0.5f;
	vertex3[1].coordinate[2] = 0;
		  
	vertex3[2].coordinate[0] = -0.3f;
	vertex3[2].coordinate[1] = 0.3f;
	vertex3[2].coordinate[2] = 0;
		  
	vertex3[3].coordinate[0] = -0.3f;
	vertex3[3].coordinate[1] = 0.3f;
	vertex3[3].coordinate[2] = 0;
		  
	vertex3[4].coordinate[0] = 0.5f;
	vertex3[4].coordinate[1] = 0.5f;
	vertex3[4].coordinate[2] = 0;
		  
	vertex3[5].coordinate[0] = 0.3f;
	vertex3[5].coordinate[1] = 0.3f;
	vertex3[5].coordinate[2] = 0;
		  
	vertex3[0].color[0] = 0.1f;
	vertex3[0].color[1] = 1.0f;
	vertex3[0].color[2] = 0.5f;
		  
	vertex3[1].color[0] = 0.2f;
	vertex3[1].color[1] = 1.0f;
	vertex3[1].color[2] = 0.5f;
		  
	vertex3[2].color[0] = 0.3f;
	vertex3[2].color[1] = 1.0f;
	vertex3[2].color[2] = 0.5f;
		  
	vertex3[3].color[0] = 0.4f;
	vertex3[3].color[1] = 1.0f;
	vertex3[3].color[2] = 0.5f;
		  
	vertex3[4].color[0] = 0.5f;
	vertex3[4].color[1] = 1.0f;
	vertex3[4].color[2] = 0.5f;
		  
	vertex3[5].color[0] = 0.6f;
	vertex3[5].color[1] = 1.0f;
	vertex3[5].color[2] = 0.5f;

	// VERTEX 4 - Bottom

	vertex4[0].coordinate[0] = -0.3f;
	vertex4[0].coordinate[1] = -0.3f;
	vertex4[0].coordinate[2] = 0;
		  
	vertex4[1].coordinate[0] = 0.3f;
	vertex4[1].coordinate[1] = -0.3f;
	vertex4[1].coordinate[2] = 0;
		  
	vertex4[2].coordinate[0] = -0.5f;
	vertex4[2].coordinate[1] = -0.5f;
	vertex4[2].coordinate[2] = 0;
		  
	vertex4[3].coordinate[0] = -0.5f;
	vertex4[3].coordinate[1] = -0.5f;
	vertex4[3].coordinate[2] = 0;
		  
	vertex4[4].coordinate[0] = 0.3f;
	vertex4[4].coordinate[1] = -0.3f;
	vertex4[4].coordinate[2] = 0;
		  
	vertex4[5].coordinate[0] = 0.5f;
	vertex4[5].coordinate[1] = -0.5f;
	vertex4[5].coordinate[2] = 0;
		  
	vertex4[0].color[0] = 0.1f;
	vertex4[0].color[1] = 0.2f;
	vertex4[0].color[2] = 0.5f;
		  
	vertex4[1].color[0] = 0.2f;
	vertex4[1].color[1] = 0.2f;
	vertex4[1].color[2] = 0.5f;
		  
	vertex4[2].color[0] = 0.3f;
	vertex4[2].color[1] = 0.2f;
	vertex4[2].color[2] = 0.5f;
		  
	vertex4[3].color[0] = 0.4f;
	vertex4[3].color[1] = 0.2f;
	vertex4[3].color[2] = 0.5f;
		  
	vertex4[4].color[0] = 0.5f;
	vertex4[4].color[1] = 0.2f;
	vertex4[4].color[2] = 0.5f;
		  
	vertex4[5].color[0] = 0.6f;
	vertex4[5].color[1] = 0.2f;
	vertex4[5].color[2] = 0.5f;

	// VERTEX 5 - Left

	vertex5[0].coordinate[0] = -0.5f;
	vertex5[0].coordinate[1] = 0.5f;
	vertex5[0].coordinate[2] = 0;
		  
	vertex5[1].coordinate[0] = -0.3f;
	vertex5[1].coordinate[1] = 0.3f;
	vertex5[1].coordinate[2] = 0;
		  
	vertex5[2].coordinate[0] = -0.3f;
	vertex5[2].coordinate[1] = -0.3f;
	vertex5[2].coordinate[2] = 0;
		  
	vertex5[3].coordinate[0] = -0.5f;
	vertex5[3].coordinate[1] = 0.5f;
	vertex5[3].coordinate[2] = 0;
		  
	vertex5[4].coordinate[0] = -0.3f;
	vertex5[4].coordinate[1] = -0.3f;
	vertex5[4].coordinate[2] = 0;
		  
	vertex5[5].coordinate[0] = -0.5f;
	vertex5[5].coordinate[1] = -0.5f;
	vertex5[5].coordinate[2] = 0;
		  
	vertex5[0].color[0] = 0.1f;
	vertex5[0].color[1] = 0.6f;
	vertex5[0].color[2] = 0.0f;
		  
	vertex5[1].color[0] = 0.2f;
	vertex5[1].color[1] = 0.6f;
	vertex5[1].color[2] = 0.0f;
		  
	vertex5[2].color[0] = 0.3f;
	vertex5[2].color[1] = 0.6f;
	vertex5[2].color[2] = 0.0f;
		  
	vertex5[3].color[0] = 0.4f;
	vertex5[3].color[1] = 0.6f;
	vertex5[3].color[2] = 0.0f;
		  
	vertex5[4].color[0] = 0.5f;
	vertex5[4].color[1] = 0.6f;
	vertex5[4].color[2] = 0.0f;
		  
	vertex5[5].color[0] = 0.6f;
	vertex5[5].color[1] = 0.6f;
	vertex5[5].color[2] = 0.0f;

	// VERTEX 6 - Right

	vertex6[0].coordinate[0] = 0.3f;
	vertex6[0].coordinate[1] = 0.3f;
	vertex6[0].coordinate[2] = 0;
		  
	vertex6[1].coordinate[0] = 0.5f;
	vertex6[1].coordinate[1] = 0.5f;
	vertex6[1].coordinate[2] = 0;
		  
	vertex6[2].coordinate[0] = 0.5f;
	vertex6[2].coordinate[1] = -0.5f;
	vertex6[2].coordinate[2] = 0;
		  
	vertex6[3].coordinate[0] = 0.3f;
	vertex6[3].coordinate[1] = 0.3f;
	vertex6[3].coordinate[2] = 0;
		  
	vertex6[4].coordinate[0] = 0.3f;
	vertex6[4].coordinate[1] = -0.3f;
	vertex6[4].coordinate[2] = 0;
		  
	vertex6[5].coordinate[0] = 0.5f;
	vertex6[5].coordinate[1] = -0.5f;
	vertex6[5].coordinate[2] = 0;
		  
	vertex6[0].color[0] = 1.0f;
	vertex6[0].color[1] = 0.1f;
	vertex6[0].color[2] = 1.0f;
		  
	vertex6[1].color[0] = 1.0f;
	vertex6[1].color[1] = 0.2f;
	vertex6[1].color[2] = 1.0f;
		  
	vertex6[2].color[0] = 1.0f;
	vertex6[2].color[1] = 0.3f;
	vertex6[2].color[2] = 1.0f;
		  
	vertex6[3].color[0] = 1.0f;
	vertex6[3].color[1] = 0.4f;
	vertex6[3].color[2] = 1.0f;
		  
	vertex6[4].color[0] = 1.0f;
	vertex6[4].color[1] = 0.5f;
	vertex6[4].color[2] = 1.0f;
		  
	vertex6[5].color[0] = 1.0f;
	vertex6[5].color[1] = 0.6f;
	vertex6[5].color[2] = 1.0f;


	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 4;   triangles[5] = 5;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex1, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

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
	if (sf::Keyboard::isKeyPressed(Keyboard::Space))
	{
		applyMatrix(matrixRotation);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::S))
	{
		applyMatrix(matrixScale);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::T))
	{
		translate();
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
	// Draw Green Triangles - Front
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex1, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	// Draw Cyan Triangles - Back
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex2, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	// Draw Turquiose Triangles - Top
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex3, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	// Draw Purple Triangles - Bottom
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex4, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	// Draw Dark Green Triangles - Left
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex5, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	// Draw Pink Triangles - Right
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex6, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

void Game::translate()
{
	Matrix matrixTranslate = matrixTranslate.translate(0.005f, 0);
	Vector vec[6];
	for (int i = 0; i < 6; i++)
	{
		vec[i] = Vector(vertex1[i].coordinate[0], vertex1[i].coordinate[1], 1);
		vec[i] = matrixTranslate * vec[i];
		vertex1[i].coordinate[0] = vec[i].x();
		vertex1[i].coordinate[1] = vec[i].y();

		vec[i] = Vector(vertex2[i].coordinate[0], vertex2[i].coordinate[1], 1);
		vec[i] = matrixTranslate * vec[i];
		vertex2[i].coordinate[0] = vec[i].x();
		vertex2[i].coordinate[1] = vec[i].y();

		vec[i] = Vector(vertex3[i].coordinate[0], vertex3[i].coordinate[1], 1);
		vec[i] = matrixTranslate * vec[i];
		vertex3[i].coordinate[0] = vec[i].x();
		vertex3[i].coordinate[1] = vec[i].y();
		 
		vec[i] = Vector(vertex4[i].coordinate[0], vertex4[i].coordinate[1], 1);
		vec[i] = matrixTranslate * vec[i];
		vertex4[i].coordinate[0] = vec[i].x();
		vertex4[i].coordinate[1] = vec[i].y();

		vec[i] = Vector(vertex5[i].coordinate[0], vertex5[i].coordinate[1], 1);
		vec[i] = matrixTranslate * vec[i];
		vertex5[i].coordinate[0] = vec[i].x();
		vertex5[i].coordinate[1] = vec[i].y();

		vec[i] = Vector(vertex6[i].coordinate[0], vertex6[i].coordinate[1], 1);
		vec[i] = matrixTranslate * vec[i];
		vertex6[i].coordinate[0] = vec[i].x();
		vertex6[i].coordinate[1] = vec[i].y();
	}
}
void Game::applyMatrix(Matrix matrix)
{
	Vector vec[6];
	for (int i = 0; i < 6; i++)
	{
		vec[i] = Vector(vertex1[i].coordinate[0], vertex1[i].coordinate[1], vertex1[i].coordinate[2]);
		vec[i] = matrix * vec[i];
		vertex1[i].coordinate[0] = vec[i].x();
		vertex1[i].coordinate[1] = vec[i].y();
		vertex1[i].coordinate[2] = vec[i].z();

		vec[i] = Vector(vertex2[i].coordinate[0], vertex2[i].coordinate[1], vertex2[i].coordinate[2]);
		vec[i] = matrix * vec[i];
		vertex2[i].coordinate[0] = vec[i].x();
		vertex2[i].coordinate[1] = vec[i].y();
		vertex2[i].coordinate[2] = vec[i].z();

		vec[i] = Vector(vertex3[i].coordinate[0], vertex3[i].coordinate[1], vertex3[i].coordinate[2]);
		vec[i] = matrix * vec[i];
		vertex3[i].coordinate[0] = vec[i].x();
		vertex3[i].coordinate[1] = vec[i].y();
		vertex3[i].coordinate[2] = vec[i].z();

		vec[i] = Vector(vertex4[i].coordinate[0], vertex4[i].coordinate[1], vertex4[i].coordinate[2]);
		vec[i] = matrix * vec[i];
		vertex4[i].coordinate[0] = vec[i].x();
		vertex4[i].coordinate[1] = vec[i].y();
		vertex4[i].coordinate[2] = vec[i].z();

		vec[i] = Vector(vertex5[i].coordinate[0], vertex5[i].coordinate[1], vertex5[i].coordinate[2]);
		vec[i] = matrix * vec[i];
		vertex5[i].coordinate[0] = vec[i].x();
		vertex5[i].coordinate[1] = vec[i].y();
		vertex5[i].coordinate[2] = vec[i].z();

		vec[i] = Vector(vertex6[i].coordinate[0], vertex6[i].coordinate[1], vertex6[i].coordinate[2]);
		vec[i] = matrix * vec[i];
		vertex6[i].coordinate[0] = vec[i].x();
		vertex6[i].coordinate[1] = vec[i].y();
		vertex6[i].coordinate[2] = vec[i].z();
	}
}


















