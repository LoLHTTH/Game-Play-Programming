#include "Player.h"

Player::Player()
{
	m_pos = sf::Vector2f(0, 0);
}

sf::Vector2f Player::getPos() const
{
	return m_pos;
}

void Player::addX()
{
	m_pos.x++;
}
void Player::subX()
{
	m_pos.x--;
}
void Player::setX(float x)
{
	m_pos.x = x;
}

void Player::addY()
{
	m_pos.y++;
}
void Player::subY()
{
	m_pos.y--;
}
void Player::setY(float y)
{
	m_pos.y = y;
}