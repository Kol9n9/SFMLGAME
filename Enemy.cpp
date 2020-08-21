#include "Enemy.h"

Enemy::Enemy(const std::string &file_texture, const sf::IntRect &rect,const sf::Vector2f &spawn_pos)
    : Entity(file_texture,rect,spawn_pos)
{
    //ctor
}

Enemy::~Enemy()
{
    if(this->m_hp_bar) delete this->m_hp_bar;
    std::cout << "~Enemy\n";
    //dtor
}
