#ifndef HITBOX_H
#define HITBOX_H
#include "SFML/Graphics.hpp"

class Hitbox
{
    public:
        Hitbox();
        virtual ~Hitbox();
        void updateHitbox(const sf::Vector2f &pos,const sf::Vector2f &size);
        sf::RectangleShape &getHitbox() { return m_hitbox;}
        bool intersect(Hitbox &hit);
    protected:

    private:
        sf::RectangleShape m_hitbox;
};

#endif // HITBOX_H
