#include "Enemy.h"

Enemy::Enemy(const std::string &file_texture, const sf::IntRect &rect,const sf::Vector2f &spawn_pos)
    : Entity(file_texture,rect,spawn_pos)
{
    //ctor
}

Enemy::~Enemy()
{
    //dtor
}
