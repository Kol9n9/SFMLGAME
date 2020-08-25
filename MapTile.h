#ifndef MAPTILE_H
#define MAPTILE_H

#include "Tile.h"
#include <vector>
#include <string>
class MapTile
{
    public:
        MapTile(const std::string &texture_file);
        virtual ~MapTile();
        void render(sf::RenderTarget *target);
        void addTile(const sf::IntRect &rect,const sf::Vector2f &pos);
    protected:

    private:
        sf::Texture m_texture;
        std::vector<Tile*>m_tiles;

        void initTexture(const std::string &texture_file);
};

#endif // MAPTILE_H
