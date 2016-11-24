#include "Game.h"
#include "Matrix.h"
#include "Vector.h"

bool flip = false;
int current = 1;
float scale = 0.5f;
//TRIANGLE 1
Vector v1(0.0, 2.0, -5.0);
Vector v2(-2.0, -2.0, -5.0);
Vector v3(2.0, -2.0, -5.0);
//TRIANGLE 2
Vector v4(0.2, 0.0, -2.0);
Vector v5(-2.0, -2.0, -2.0);
Vector v6(2.0, -2.0, -2.0);

Matrix rotateMatrix;
Matrix translateMatrix;

Game::Game() : window(VideoMode(800, 600), "OpenGL"), primatives(2)
{
	index = glGenLists(primatives);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	glNewList(index, GL_COMPILE);

	glBegin(GL_TRIANGLES);
	{
		glColor3f(1.0f, 0.0f, 1.0f);
		//glVertex3f(0.0, 2.0, -5.0);
		//glVertex3f(-2.0, -2.0, -5.0);
		//glVertex3f(2.0, -2.0, -5.0);

		glVertex3f(v1.x(), v1.y(), v1.z());
		glVertex3f(v2.x(), v2.y(), v2.z());
		glVertex3f(v3.x(), v3.y(), v3.z());
		
	}
	glEnd();
	glEndList();

	glNewList(index + 1, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		//glVertex3f(0.2, 0.0, -2.0);
		//glVertex3f(-2.0, -2.0, -2.0);
		//glVertex3f(2.0, -2.0, -2.0);

		glVertex3f(v4.x(), v4.y(), v4.z());
		glVertex3f(v5.x(), v5.y(), v5.z());
		glVertex3f(v6.x(), v6.y(), v6.z());
	}
	glEnd();
	glEndList();


	//v1 = v1.scale(0.2);
	//v2 = v2.scale(0.2);
	//v3 = v3.scale(0.2);

	//translateMatrix = translateMatrix.translate(1, 0);
	//v1 = translateMatrix * v1;

	//glScalef(scale, 1.0f, scale);// scales the triangle in size
	//glTranslatef(1.0f, 0.0f, 0.0f);// moves the triangle in the x axis by 1
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
			current++;
			if (current > primatives)
			{
				current = 1;
			}
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}
	rotateMatrix = rotateMatrix.rotation(rotationAngle);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		//ROTATE TRIANGLE 1
		v1 = rotateMatrix * v1;
		v2 = rotateMatrix * v2;
		v3 = rotateMatrix * v3;
		//ROTATE TRIANGLE 2
		v4 = rotateMatrix * v4;
		v5 = rotateMatrix * v5;
		v6 = rotateMatrix * v6;
	}

	//glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	//glLoadIdentity(); //replace the current matrix with the identity matrix
	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Draw up" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Investigate Here!!!!!
	initialize(); // TO DRAW AGAIN WITH NEW POINTS

	cout << "Drawing Primative " << current << endl;
	glCallList(current);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

