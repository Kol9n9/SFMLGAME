#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"
#include <iostream>
class Tile
{
    public:
        Tile(const sf::Texture &texture, const sf::IntRect &rect, const sf::Vector2f &pos, const int &tile_type);
        Tile(Tile *tile);
        virtual ~Tile();
        void render(sf::RenderTarget *target);
        void update(const sf::Vector2i &mousePos);

        void setPosition(const sf::Vector2f &pos);
        sf::Sprite &getTile() { return m_sprite;}
        sf::Vector2f &getPosition() {return m_pos;}
        int &getTileType() {return m_tile_type;}

        bool &isHover() { return m_isHover;}
        void Moving(const sf::Vector2f &pos);
        sf::Vector2f getTileCenter() {return sf::Vector2f(this->m_sprite.getGlobalBounds().width/2,this->m_sprite.getGlobalBounds().height/2);}
    protected:

    private:
        sf::Sprite m_sprite;
        sf::Vector2f m_pos;
        int m_tile_type;
        bool m_isHover;

        void isContain(const sf::Vector2i &mousePos);




};

#endif // TILE_H
