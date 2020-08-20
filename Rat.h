#ifndef RAT_H
#define RAT_H

#include "Enemy.h"

class Rat : public Enemy
{
    public:
        Rat(const sf::Vector2f &pos = sf::Vector2f(0,0));
        virtual ~Rat();
        void update(const float &dt,const sf::Vector2i &mousePos);
        void render(sf::RenderTarget *target);
        void attack();
        void loseHP(const float &damage);

    protected:

    private:


};

#endif // RAT_H
