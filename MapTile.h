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
        void update(const sf::Vector2f &mousePos);
        void addTile(const int &render_level, const sf::IntRect &rect,const sf::Vector2f &pos, const int &tile_type);
        Tile *addTile(const int &render_level, Tile *tile, const sf::Vector2f &pos);

        Tile *getHoverTile() {return m_tile_hover;}

        std::map<int, Tile*> getLevelTiles(const int &level = 0);
        void setTileEdit(Tile *tile){m_tile_edit = tile;}

        void loadLevel();
        void saveLevel();
    protected:

    private:
        sf::Texture m_texture;
        Tile *m_tile_edit;
        Tile *m_tile_hover;
        std::map<int, std::vector<Tile*>>m_tiles;
        std::map<int, sf::IntRect> m_level_tile;
};

#endif // MAPTILE_H
