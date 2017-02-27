#include "Goal.h"

Goal::Goal()
{
	m_pos = sf::Vector2f(64,0);
}

float Goal::getX()
{
	return m_pos.x;
}

float Goal::getY()
{
	return m_pos.y;
}