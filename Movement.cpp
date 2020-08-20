#include "Movement.h"

Movement::Movement(Entity *entity, float acceleration, float deceleration, float maxVelocity)
    : m_entity(entity), m_acceleration(acceleration), m_deceleration(deceleration), m_maxVelocity(maxVelocity)
{
    //ctor
}

Movement::~Movement()
{
    //dtor
}

void Movement::move(const float &dt, const float &dir_x, const float &dir_y)
{
    this->m_velocity.x += this->m_acceleration * dir_x * dt;
    this->m_velocity.y += this->m_acceleration * dir_y * dt;
}
void Movement::stopMove()
{
    this->m_velocity.x = this->m_velocity.y = 0;
}
void Movement::update(const float &dt)
{
    if(this->m_velocity.x > 0.f)
    {
        if(this->m_velocity.x > this->m_maxVelocity)
            this->m_velocity.x = this->m_maxVelocity;
        this->m_velocity.x -= this->m_deceleration * dt;
        if(this->m_velocity.x < 0.f)
            this->m_velocity.x = 0;
    }
    else if(this->m_velocity.x < 0.f)
    {
        if(this->m_velocity.x < -this->m_maxVelocity)
            this->m_velocity.x = -this->m_maxVelocity;
        this->m_velocity.x += this->m_deceleration * dt;
        if(this->m_velocity.x > 0.f)
            this->m_velocity.x = 0;
    }
    if(this->m_velocity.y > 0.f)
    {
        if(this->m_velocity.y > this->m_maxVelocity)
            this->m_velocity.y = this->m_maxVelocity;
        this->m_velocity.y -= this->m_deceleration * dt;
        if(this->m_velocity.y < 0.f)
            this->m_velocity.y = 0;
    }
    else if(this->m_velocity.y < 0.f)
    {
        if(this->m_velocity.y < -this->m_maxVelocity)
            this->m_velocity.y = -this->m_maxVelocity;
        this->m_velocity.y += this->m_deceleration * dt;
        if(this->m_velocity.y > 0.f)
            this->m_velocity.y = 0;
    }
    this->m_entity->moved(this->m_velocity);
}
const bool Movement::getState(const short unsigned state) const
{
    switch (state)
	{
	case IDLE:

		if (this->m_velocity.x == 0.f && this->m_velocity.y == 0.f)
			return true;

		break;

	case MOVING:

		if (this->m_velocity.x != 0.f || this->m_velocity.y != 0.f)
			return true;

		break;

	case MOVING_LEFT:

		if (this->m_velocity.x < 0.f)
			return true;

		break;

	case MOVING_RIGHT:

		if (this->m_velocity.x > 0.f)
			return true;

		break;

	case MOVING_UP:

		if (this->m_velocity.y < 0.f)
			return true;

		break;

	case MOVING_DOWN:

		if (this->m_velocity.y > 0.f)
			return true;

		break;
	}

	return false;
}
