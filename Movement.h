#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "SFML/Graphics.hpp"
#include "Entity.h"
enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };
class Movement
{
    public:
        Movement(Entity *entity, float acceleration, float deceleration, float maxVelocity);
        virtual ~Movement();
        void update(const float &dt);
        void move(const float &dt, const float &dir_x, const float &dir_y);
        const bool getState(const short unsigned state) const;
    protected:

    private:
        sf::Vector2f m_velocity;
        float m_acceleration;
        float m_deceleration;
        Entity *m_entity;
        float m_maxVelocity;
};

#endif // MOVEMENT_H
