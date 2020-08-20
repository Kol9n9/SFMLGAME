#ifndef RAT_H
#define RAT_H

#include "Enemy.h"

class Rat : public Enemy
{
    public:
        Rat(const float &base_hp, const float &base_damage,const sf::Vector2f &pos = sf::Vector2f(0,0));
        virtual ~Rat();
        void update(const float &dt,const sf::Vector2i &mousePos);
        void render(sf::RenderTarget *target);
        void attack();
        void loseHP(const float &damage);
        float &getDamage() {return m_damage;}
        float &getHP() {return m_hp;}
        float &getFullHP() {return m_hp_max;}
    protected:

    private:
        float m_hp;
        float m_hp_max;
        float m_damage;

};

#endif // RAT_H
