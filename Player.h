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
        Player(const float &base_hp, const float &base_damage,const sf::Vector2f &pos = sf::Vector2f(0,0));
        virtual ~Player();
        void move(const float &dt, const float &dir_x, const float &dir_y);
        void update(const float &dt,const sf::Vector2i &mousePos);
        void render(sf::RenderTarget *target);
        void loseHP(const float &damage);
        sf::Vector2f &getPointAttack() { return m_weapon->getPointAttack();}
        void attack();
        bool &getAttacking() {return m_weapon->getAttacking();}
        float &getDamage() { return m_damage;}
        float &getHP() { return m_hp;}
        float &getFullHP() { return m_hp_max;}
        Weapon *getWeapon() {return m_weapon;}
    protected:

    private:
        Animation *m_animation;
        Movement *m_movement;
        Weapon *m_weapon;
        float m_hp;
        float m_hp_max;
        float m_damage;
        void initAnimations();
        int m_dir;
        int m_old_dir;
        bool m_first;
};

#endif // PLAYER_H
