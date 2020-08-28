#include "MapTile.h"

MapTile::MapTile()
{
    this->m_tile_edit = nullptr;
    this->m_tile_hover = nullptr;
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
void MapTile::addTile(const int &render_level, const sf::IntRect &rect,const sf::Vector2f &pos, const int &tile_type)
{
    this->m_tiles[render_level].push_back(new Tile(this->m_texture,rect,pos,tile_type));
}
Tile *MapTile::addTile(const int &render_level, Tile *tile,const sf::Vector2f &pos)
{
    Tile *newTile = new Tile(tile);
    this->m_tiles[render_level].push_back(newTile);
    this->m_tile_edit = newTile;
    return this->m_tiles[render_level].back();
}
void MapTile::removeTile(Tile *tile)
{
    for(int i(0); i < this->m_tiles.size(); ++i)
        for(int j(0); j < this->m_tiles[i].size();++j)
            if(this->m_tiles[i][j] == tile)
            {
                delete this->m_tiles[i][j];
                this->m_tiles[i].erase(this->m_tiles[i].begin() + j);
                if(this->m_tile_hover) this->m_tile_hover = nullptr;
                break;
            }
}
std::map<int, Tile*> MapTile::getLevelTiles()
{
    std::map<int, Tile*> result;
    for(auto it = this->m_level_tile.begin(); it != this->m_level_tile.end(); ++it)
    {
        result[(it->first)] = new Tile(this->m_texture,(it->second),sf::Vector2f(0,0),(it->first));
        std::cout << result[(it->first)]->getTile().getGlobalBounds().height << "\n";
    }
    return result;
}
void MapTile::render(sf::RenderTarget *target)
{
    for(auto &vec : this->m_tiles)
    {
        for(auto &tile : vec.second)
        {
            if(tile == this->m_tile_edit) continue;
            tile->render(target);
        }
    }
}
void MapTile::update(const sf::Vector2f &pos)
{
    this->m_tile_hover = nullptr;
    for(auto &vec : this->m_tiles)
    {
        for(auto &tile : vec.second)
        {
            tile->update(static_cast<sf::Vector2i>(pos));
            if(tile->isHover()) {this->m_tile_hover = tile;break;}
        }
    }
}
void MapTile::loadLevel(const int &lvl)
{
    this->clear();
    std::string levelfile = "config/level";
    levelfile += std::to_string(lvl);
    levelfile += ".cfg";

    std::string tilefile = "config/level";
    tilefile += std::to_string(lvl);
    tilefile += "tile.cfg";


    std::ifstream level(levelfile);
    std::ifstream tile(tilefile);

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
        this->addTile(render_level, this->m_level_tile[type],pos, type);
    }
    level.close();
    tile.close();
}
void MapTile::saveLevel(const int &lvl)
{
    std::string levelfile = "config/level";
    levelfile += std::to_string(lvl);
    levelfile += ".cfg";
    std::ofstream level(levelfile);
    for(auto &vec : this->m_tiles)
    {
        for(auto &tile : vec.second)
        {
            level << (vec.first) << " ";
            level << tile->getPosition().x << " ";
            level << tile->getPosition().y << " ";
            level << tile->getTileType() << "\n";
        }
    }
    level.close();
}
void MapTile::clear()
{
    this->m_level_tile.clear();
    for(int i(0); i < this->m_tiles.size(); ++i)
    {
        for(int j(0); j < this->m_tiles[i].size(); ++j)
        {
            delete this->m_tiles[i][j];
            this->m_tiles[i][j] = nullptr;
        }
        this->m_tiles[i].clear();
    }
    this->m_tiles.clear();
}
