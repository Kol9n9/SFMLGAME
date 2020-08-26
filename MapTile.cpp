#include "MapTile.h"

MapTile::MapTile()
{
    //ctor
}

MapTile::~MapTile()
{
    std::cout << "~MapTile\n";
    for(auto &vec : this->m_tiles)
    {
        for(auto &tile : vec.second)
        {
            delete tile;
        }
    }
    //dtor
}
void MapTile::addTile(const int &render_level, const sf::IntRect &rect,const sf::Vector2f &pos)
{
    this->m_tiles[render_level].push_back(new Tile(this->m_texture,rect,pos));
}
void MapTile::addTile(const int &render_level, Tile *tile,const sf::Vector2f &pos)
{
    std::cout << "Created\n";
    this->m_tiles[render_level].push_back(tile);
}
std::map<int, Tile*> MapTile::getLevelTiles(const int &level)
{
    std::cout << "1\n";
    std::map<int, Tile*> result;
    for(auto it = this->m_level_tile.begin(); it != this->m_level_tile.end(); ++it)
    {
        result[(it->first)] = new Tile(this->m_texture,(it->second),sf::Vector2f(0,0));
        std::cout << result[(it->first)]->getTile().getGlobalBounds().height << "\n";
    }
    std::cout << "2\n";
    return result;
}
void MapTile::render(sf::RenderTarget *target)
{
    for(auto &vec : this->m_tiles)
    {
        for(auto &tile : vec.second)
        {
            tile->render(target);
        }
    }
}
void MapTile::loadLevel()
{
    std::ifstream level("config/level1.cfg");
    std::ifstream tile("config/level1tile.cfg");

    if(!level)
    {
        std::cout << "File not found\n";
        return;
    }
    if(!tile)
    {
        std::cout << "File not found\n";
        return;
    }
    std::string level_texture;
    int tile_type;
    int tile_height;
    int tile_width;
    int tile_left;
    int tile_top;
    tile >> level_texture;
    this->m_texture.loadFromFile(level_texture);
    while(!tile.eof())
    {
        tile >> tile_type;
        tile >> tile_left;
        tile >> tile_top;
        tile >> tile_width;
        tile >> tile_height;
        this->m_level_tile[tile_type] = sf::IntRect(tile_left,tile_top,tile_width,tile_height);
    }
    sf::Vector2f pos;
    int type;
    int render_level;
    while(!level.eof())
    {
        level >> render_level;
        level >> pos.x;
        level >> pos.y;
        level >> type;
        this->addTile(render_level, this->m_level_tile[type],pos);
    }
}
