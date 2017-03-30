#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
// need to draw this
class GameOver
{
public:
	GameOver();
	void readFont();
	void render(sf::RenderWindow &window);
private:
	sf::Font m_font;
	sf::Text m_text;

};