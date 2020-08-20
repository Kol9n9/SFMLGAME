#ifndef WEAPON_H
#define WEAPON_H
#include "SFML/Graphics.hpp"
#include "cmath"
#include <iostream>
#include "Movement.h"
class Weapon
{
    public:
        Weapon(const std::string &texture_file);
        virtual ~Weapon();
        virtual void attack() = 0;
        virtual void update(const float &dt, const int &dir, const sf::Vector2i &mousePos, const sf::Vector2f &center) = 0;
        virtual bool &getAttacking() = 0;
        sf::Sprite &getSprite() {return m_sprite;}
        sf::Vector2f getSpriteSize() { return sf::Vector2f(m_sprite.getGlobalBounds().width,m_sprite.getGlobalBounds().height);}
        sf::Vector2f &getPointAttack() {return m_point_attack;}
    protected:
        sf::Sprite m_sprite;
        sf::Texture m_texture;
        float m_attack_distance;
        sf::Vector2f m_point_attack;
    private:
};

#endif // WEAPON_H
