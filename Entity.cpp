#include "Entity.h"

Entity::Entity()
{

}
Entity::Entity(const std::string &file_texture, const sf::IntRect &rect)
{
    this->m_texture.loadFromFile(file_texture);
    this->m_sprite.setTexture(this->m_texture);
    this->m_sprite.setTextureRect(rect);
    this->m_hitbox = new Hitbox();

}
Entity::Entity(const sf::Texture &texture, const sf::IntRect &rect)
{
    this->m_texture = texture;
    this->m_sprite.setTexture(this->m_texture);
    this->m_sprite.setTextureRect(rect);
    //ctor
}

Entity::~Entity()
{
    if(this->m_hitbox) delete this->m_hitbox;
    //dtor
}
sf::Vector2f const Entity::getSpriteSize()
{
    return sf::Vector2f(this->m_sprite.getGlobalBounds().width,this->m_sprite.getGlobalBounds().height);
}
sf::Vector2f const Entity::getSpriteCenter()
{
    return sf::Vector2f(this->m_position.x + this->getSpriteSize().x / 2, this->m_position.y + this->getSpriteSize().y / 2);
}
void Entity::moved(const sf::Vector2f &pos)
{
    this->setPosition((this->m_position+pos));
}
