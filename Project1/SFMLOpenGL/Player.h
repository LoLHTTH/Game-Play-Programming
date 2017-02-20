#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	sf::Vector2f getPos() const;
	sf::Vector2f getVelocity() const;
	void setPos(sf::Vector2f pos);
	void addX();
	void subX();
	void setX(float x);

	void addY();
	void subY();
	void setY(float y);
private:
	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;
};