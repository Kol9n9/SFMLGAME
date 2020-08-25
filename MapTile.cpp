#include "MapTile.h"

void MapTile::initTexture(const std::string &texture_file)
{
    this->m_texture.loadFromFile(texture_file);
}
MapTile::MapTile(const std::string &texture_file)
{
    this->initTexture(texture_file);
    //ctor
}

MapTile::~MapTile()
{
    //dtor
}
void MapTile::addTile(const sf::IntRect &rect,const sf::Vector2f &pos)
{
    this->m_tiles.push_back(new Tile(this->m_texture,rect,pos));
}

void MapTile::render(sf::RenderTarget *target)
{
    if(!this->m_tiles.empty())
    {
        for(auto &tile : this->m_tiles)
        {
            tile->render(target);
        }
    }
}
