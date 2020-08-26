#include "Tile.h"

Tile::Tile(const sf::Texture &texture, const sf::IntRect &rect,const sf::Vector2f &pos)
{
    this->m_sprite.setTexture(texture);
    this->m_sprite.setTextureRect(rect);
    this->m_sprite.setPosition(pos);
    //ctor
}

Tile::~Tile()
{
    //dtor
}

void Tile::render(sf::RenderTarget *target)
{
    target->draw(this->m_sprite);
}

bool Tile::isContain(const sf::Vector2i &mousePos)
{
    return this->m_sprite.getGlobalBounds().contains(mousePos.x,mousePos.y);
}

void Tile::Moving(const sf::Vector2f &pos)
{

    this->m_sprite.setPosition(pos);

}
