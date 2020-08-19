#ifndef WEAPON_H
#define WEAPON_H
#include "SFML/Graphics.hpp"
#include "cmath"
#include <iostream>

class Weapon
{
    public:
        Weapon(const std::string &texture_file);
        virtual ~Weapon();
        virtual void attack() = 0;
        virtual void update(const int &dir, const sf::Vector2i &mousePos, const sf::Vector2f &center) = 0;
        sf::Sprite &getSprite() {return m_sprite;}
    protected:
        sf::Sprite m_sprite;
        sf::Texture m_texture;
    private:
};

#endif // WEAPON_H
