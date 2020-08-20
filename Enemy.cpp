#include "Enemy.h"

Enemy::Enemy(const std::string &file_texture, const sf::IntRect &rect,const float &base_hp, const float &base_damage,const sf::Vector2f &spawn_pos)
    : Entity(file_texture,rect,base_hp,base_damage,spawn_pos)
{
    //ctor
}

Enemy::~Enemy()
{
    //dtor
}
