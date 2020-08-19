#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include "SFML/Graphics.hpp"

#include <iostream>
#include "Hitbox.h"

class Entity
{
    public:
        Entity();
        Entity(const std::string &file_texture, const sf::IntRect &rect);
        Entity(const sf::Texture &texture, const sf::IntRect &rect);
        virtual ~Entity();

        sf::Sprite &getSprite() { return this->m_sprite;}
        void setPosition(const sf::Vector2f &pos) {m_position = pos; m_sprite.setPosition(pos);}
        sf::Vector2f const &getPosition() { return m_position;}
        virtual void update(const float &dt,const sf::Vector2i &mousePos) = 0;
        virtual void moved(const sf::Vector2f &pos);
        virtual void render(sf::RenderTarget *target) = 0;
        virtual void attack() = 0;
        sf::Vector2f const getSpriteSize();
        sf::Vector2f const getSpriteCenter();
        Hitbox &getHitbox() { return *this->m_hitbox;}
    protected:

        sf::Sprite m_sprite;
        sf::Texture m_texture;
        sf::Vector2f m_position;
        Hitbox *m_hitbox;
    private:


};

#endif // ENTITY_H
