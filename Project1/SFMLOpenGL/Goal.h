#pragma once

#include <SFML/Graphics.hpp>

class Goal
{
public:
	Goal();
	float getX();
	float getY();
private:
	sf::Vector2f m_pos;
};