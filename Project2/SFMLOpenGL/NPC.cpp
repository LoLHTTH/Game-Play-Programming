#include "NPC.h"

NPC::NPC(sf::Vector3f pos)
{
	m_pos = pos;
}
sf::Vector3f NPC::getPos() const
{
	return m_pos;
}
void NPC::addX()
{
	m_pos.x++;
}
void NPC::addY()
{
	m_pos.y++;
}
void NPC::addZ()
{
	m_pos.z++;
}
void NPC::subX()
{
	m_pos.x--;
}
void NPC::subY()
{
	m_pos.y--;
}
void NPC::subZ()
{
	m_pos.z--;
}
void NPC::setX(float x)
{
	m_pos.x = x;
}