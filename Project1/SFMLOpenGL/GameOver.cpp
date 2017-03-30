#include "GameOver.h"

GameOver::GameOver()
{
	readFont();
	m_text.setColor(sf::Color::White);
	m_text.setPosition(0, 0);
	m_text.setFont(m_font);
}
void GameOver::readFont()
{
	if (!m_font.loadFromFile(".//Assets//Fonts//BBrick.ttf"))
	{
		std::cout << "File is not found!" << std::endl;
	}
}
void GameOver::render(sf::RenderWindow &window)
{
	window.clear();
	window.draw(m_text);
	window.display();
}