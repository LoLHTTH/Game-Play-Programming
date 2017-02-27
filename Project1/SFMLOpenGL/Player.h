#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	sf::Vector3f getPos() const;
	sf::Vector2f getVelocity() const;
	void setVelocityY(float velocityY);
	void setPos(sf::Vector3f pos);
	void addX();
	void subX();
	void setX(float x);

	void addY();
	void subY();
	void setY(float y);

	void addZ();
	void subZ();

private:
	sf::Vector3f m_pos;
	sf::Vector2f m_velocity;
};