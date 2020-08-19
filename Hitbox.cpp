#include "Hitbox.h"

Hitbox::Hitbox()
{
    this->m_hitbox.setFillColor(sf::Color::Transparent);
    this->m_hitbox.setOutlineColor(sf::Color(255,0,0));
    this->m_hitbox.setOutlineThickness(2);
    //ctor
}

Hitbox::~Hitbox()
{
    //dtor
}
void Hitbox::updateHitbox(const sf::Vector2f &pos,const sf::Vector2f &size)
{
    this->m_hitbox.setPosition(pos);
    this->m_hitbox.setSize(size);
}
bool Hitbox::intersect(Hitbox &hit)
{
    return (this->m_hitbox.getPosition().x >= hit.getHitbox().getPosition().x && this->m_hitbox.getPosition().x <= hit.getHitbox().getPosition().x + hit.getHitbox().getSize().x &&
            this->m_hitbox.getPosition().y >= hit.getHitbox().getPosition().y && this->m_hitbox.getPosition().y <= hit.getHitbox().getPosition().y + hit.getHitbox().getSize().y);
}
