#include "Player.h"

Player::Player()
{
	m_pos = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 2);
}

sf::Vector2f Player::getPos() const
{
	return m_pos;
}
sf::Vector2f Player::getVelocity() const
{
	return m_velocity;
}
void Player::setPos(sf::Vector2f pos)
{
	m_pos = pos;
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