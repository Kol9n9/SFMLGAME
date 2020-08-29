#include "Tile.h"

Tile::Tile(const sf::Texture &texture, const sf::IntRect &rect,const sf::Vector2f &pos, const int &tile_type)
{
    this->m_sprite.setTexture(texture);
    this->m_sprite.setTextureRect(rect);
    this->m_sprite.setPosition(pos);
    this->m_pos = pos;
    this->m_tile_type = tile_type;
    //ctor
}

Tile::Tile(Tile *old_tile)
{
    this->m_sprite = old_tile->m_sprite;
    this->m_pos = old_tile->m_pos;
    this->m_tile_type = old_tile->m_tile_type;
}

Tile::~Tile()
{
    //dtor
}

void Tile::render(sf::RenderTarget *target)
{
    target->draw(this->m_sprite);
    if(this->m_isBorderShow)
    {
        sf::RectangleShape shape;
        shape.setPosition(this->m_pos);
        shape.setSize(sf::Vector2f(this->m_sprite.getGlobalBounds().width,this->m_sprite.getGlobalBounds().height));
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color(7,150,3));
        shape.setOutlineThickness(-2);
        target->draw(shape);
    }
}
void Tile::update(const sf::Vector2i &mousePos)
{
    this->m_isHover = false;
    this->m_isBorderShow = false;
    this->isContain(mousePos);
}
void Tile::isContain(const sf::Vector2i &mousePos)
{
    if(this->m_sprite.getGlobalBounds().contains(mousePos.x,mousePos.y))
    {
        this->m_isHover = true;
    }
}
void Tile::setPosition(const sf::Vector2f &pos)
{
    this->m_sprite.setPosition(pos);
    this->m_pos = pos;
}
void Tile::Moving(const sf::Vector2f &pos)
{
    this->setPosition(pos);
}
