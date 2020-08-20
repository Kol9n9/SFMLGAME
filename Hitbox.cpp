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
bool Hitbox::intersect(const sf::Vector2i &mousePos)
{
    return (mousePos.x >= this->m_hitbox.getPosition().x && mousePos.x <= this->m_hitbox.getPosition().x + this->m_hitbox.getSize().x &&
            mousePos.y >= this->m_hitbox.getPosition().y && mousePos.y <= this->m_hitbox.getPosition().y + this->m_hitbox.getSize().y);
}

bool Hitbox::intersect(const sf::Vector2f &pos, const sf::Vector2f &size)
{
    return (this->m_hitbox.getPosition().x <= pos.x && this->m_hitbox.getPosition().x >= pos.x - size.x &&
            this->m_hitbox.getPosition().y <= pos.y && this->m_hitbox.getPosition().y >= pos.y - size.y);
}
