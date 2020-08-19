#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Animation.h"
#include <vector>
#include "SFML/Graphics.hpp"
#include "Movement.h"
#include "Sword.h"
#include "GUI.h"


class Player : public Entity
{
    public:
        Player();
        virtual ~Player();
        void move(const float &dt, const float &dir_x, const float &dir_y);
        void update(const float &dt,const sf::Vector2i &mousePos);
        void render(sf::RenderTarget *target);
        sf::Vector2f &getPointAttack() { return m_weapon->getPointAttack();}
        void attack();
    protected:

    private:
        Animation *m_animation;
        Movement *m_movement;
        Weapon *m_weapon;
        void initAnimations();
        int m_dir;
};

#endif // PLAYER_H
