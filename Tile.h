#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"
#include <iostream>
class Tile
{
    public:
        Tile(const sf::Texture &texture, const sf::IntRect &rect, const sf::Vector2f &pos);
        virtual ~Tile();
        void render(sf::RenderTarget *target);
        void update();

        sf::Sprite &getTile() { return m_sprite;}
        bool isContain(const sf::Vector2i &mousePos);

        void Moving(const sf::Vector2f &pos);
        sf::Vector2f getTileCenter() {return sf::Vector2f(this->m_sprite.getGlobalBounds().width/2,this->m_sprite.getGlobalBounds().height/2);}
    protected:

    private:
        sf::Sprite m_sprite;




};

#endif // TILE_H
