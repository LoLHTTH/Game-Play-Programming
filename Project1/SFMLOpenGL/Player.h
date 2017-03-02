#pragma once

#include <SFML/Graphics.hpp>

// The player class contains position and status of the player model
class Player
{
public:
	Player();
	sf::Vector3f getPos() const; // to get current pos
	bool checkAlive(); // to check alive
	void setDead(); // make it dead

	void setPos(sf::Vector3f pos); // set position of player
	void addX(); // add 1 to x
	void subX(); // sub 1 to x
	void setX(float x); // set position of x

	void addY();// add 1 to y
	void subY();// sub 1 to y
	void setY(float y); // set position of y

	void addZ();// add 1 to z
	void subZ();// sub 1 to z
	void setZ(float z); // set position of z

private:
	sf::Vector3f m_pos;
	bool m_alive;
};