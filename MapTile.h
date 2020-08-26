#ifndef MAPTILE_H
#define MAPTILE_H

#include "Tile.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
class MapTile
{
    public:
        MapTile();
        virtual ~MapTile();
        void render(sf::RenderTarget *target);
        void addTile(const int &render_level, const sf::IntRect &rect,const sf::Vector2f &pos);
        void addTile(const int &render_level, Tile *tile, const sf::Vector2f &pos);

        std::map<int, Tile*> getLevelTiles(const int &level = 0);

        void loadLevel();
    protected:

    private:
        sf::Texture m_texture;
        std::map<int, std::vector<Tile*>>m_tiles;
        std::map<int, sf::IntRect> m_level_tile;
};

#endif // MAPTILE_H
