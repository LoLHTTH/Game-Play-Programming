#pragma once
#include <SFML\Graphics.hpp>

class Ground
{
public:
	Ground();
	void render(sf::RenderWindow &window);
private:
	sf::RectangleShape m_rect;
};