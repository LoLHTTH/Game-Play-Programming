#include "Player.h"

Player::Player()
{
	m_pos = sf::Vector3f(0, 0, 0);
	m_velocity = sf::Vector2f(50, 50);
}

sf::Vector3f Player::getPos() const
{
	return m_pos;
}
sf::Vector2f Player::getVelocity() const
{
	return m_velocity;
}
void Player::setPos(sf::Vector3f pos)
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
void Player::addZ()
{
	m_pos.z++;
}
void Player::subZ()
{
	m_pos.z--;
}
void Player::setVelocityY(float velocity)
{
	m_velocity.y = velocity;
}