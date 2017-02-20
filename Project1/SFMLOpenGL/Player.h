#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	sf::Vector2f getPos() const;
	void addX();
	void subX();
	void setX(float x);

	void addY();
	void subY();
	void setY(float y);
private:
	sf::Vector2f m_pos;
};