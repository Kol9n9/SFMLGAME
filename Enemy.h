#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Progressbar.h"

class Enemy : public Entity
{
    public:
        Enemy(const std::string &file_texture, const sf::IntRect &rect,const sf::Vector2f &spawn_pos);
        virtual ~Enemy();
        float &getGivedXP(){return m_gived_xp;}
    protected:
        GUI::Progressbar *m_hp_bar;
        float m_gived_xp;
    private:

};

#endif // ENEMY_H
