#pragma once

#include <SFML/Graphics.hpp>

class NPC
{
public:
	NPC(sf::Vector2f pos);
private:
	sf::Vector2f m_pos;
};