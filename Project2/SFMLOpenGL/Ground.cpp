#include "Ground.h"

Ground::Ground()
{
	m_rect.setFillColor(sf::Color(123,123,432,255));
	m_rect.setSize(sf::Vector2f(800, 400));
	m_rect.setPosition(sf::Vector2f(0, 300));
}

void Ground::render(sf::RenderWindow &window)
{
	window.draw(m_rect);
}