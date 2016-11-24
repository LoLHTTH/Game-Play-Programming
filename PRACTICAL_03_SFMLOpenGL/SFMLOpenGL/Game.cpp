#include "Game.h"

Game::Game() : window(VideoMode(800, 600), "OpenGL")
{
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
}

void Game::update()
{
	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Draw up" << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glClear(GL_COLOR_BUFFER_BIT); 
	glBegin(GL_TRIANGLES); 
	{ 
	glColor3f(1, 1, 0);
	glVertex3f(0.0, 2.0, -5.0);
	glVertex3f(-2.0, -2.0, -5.0);
	glVertex3f(2.0, -2.0, -5.0);
	}
	glEnd();

	glBegin(GL_POINTS);
	{ 
		for (float i = -2; i <= 2.2f;i +=0.1f)
		{
			glColor3f(1, 0, 1);
			glVertex3f(i, 2.0, -5.0);
		}
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glVertex3f(0, 2.0, -7.0);
		glVertex3f(5, 2.0, -10.0);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	{
		glColor3f(0, 0, 1);
		glVertex3f(0.0, 2.0, -5.0);
		glVertex3f(-2.0, -2.0, -5.0);
		glVertex3f(2.0, -2.0, -5.0);
		glVertex3f(0.0, 2.0, -5.0);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	{
		glColor3f(0, 1, 1);
		glVertex3f(0.0, 2.0, -5.0);
		glVertex3f(-2.0, -2.0, -5.0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	{
		glColor3f(0, 1, 0);
		glVertex3f(0, 2.0, -5.0);
		glVertex3f(1, 2.0, -5.0);
		glVertex3f(-0.5, 1, -5.0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	{
		glColor3f(1, 0, 0);
		glVertex3f(0.6, 2.0, -5.0);
		glVertex3f(0.2, -2.0, -5.0);
		glVertex3f(-0.3, 2, -5.0);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(1, 1, 1);
		glVertex3f(2, 2.0, -5.0);
		glVertex3f(2, -2, -5.0);
		glVertex3f(1, -2, -5.0);
		glVertex3f(1, 2.0, -5.0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3f(1, 0, 1);
		glVertex3f(-2, 2.0, -5.0);
		glVertex3f(-2, -2, -5.0);
		glVertex3f(-1, -2, -5.0);
		glVertex3f(-1, 2.0, -5.0);
	}
	glEnd();


	window.display();
}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

