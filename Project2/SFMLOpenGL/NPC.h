#pragma once

#include <SFML/Graphics.hpp>

class NPC
{
public:
	NPC(sf::Vector3f pos);
	sf::Vector3f getPos() const;
	void addX();
	void addY();
	void addZ();
	void subX();
	void subY();
	void subZ();
	void setX(float x);
private:
	sf::Vector3f m_pos;
};