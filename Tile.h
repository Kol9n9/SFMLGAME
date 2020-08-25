#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"

class Tile
{
    public:
        Tile(const sf::Texture &texture, const sf::IntRect &rect, const sf::Vector2f &pos);
        virtual ~Tile();
        void render(sf::RenderTarget *target);
    protected:

    private:
        sf::Sprite m_sprite;
};

#endif // TILE_H
