#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Progressbar.h"

class Enemy : public Entity
{
    public:
        Enemy(const std::string &file_texture, const sf::IntRect &rect,const float &base_hp, const float &base_damage,const sf::Vector2f &spawn_pos);
        virtual ~Enemy();

    protected:
        GUI::Progressbar *m_hp_bar;
    private:

};

#endif // ENEMY_H
