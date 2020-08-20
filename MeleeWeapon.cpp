#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(const std::string &texture_file)
    : Weapon(texture_file)
{
    this->m_is_attack = false;
	this->m_is_attacking = false;
	this->m_dir = movement_states::MOVING_DOWN;
    //ctor
}

MeleeWeapon::~MeleeWeapon()
{
    //dtor
}

sf::Vector2f MeleeWeapon::limitAttackAngle(const int &dir)
{
    switch(dir)
    {
        case movement_states::MOVING_DOWN:
        {
            return sf::Vector2f(50,140);
        }
        case movement_states::MOVING_UP:
        {
            return sf::Vector2f(240,290);
        }
        case movement_states::MOVING_LEFT:
        {
            return sf::Vector2f(140,240);
        }
        case movement_states::MOVING_RIGHT:
        {
            return sf::Vector2f(290,60);
        }
    }
}
void MeleeWeapon::update(const float &dt, const int &dir, const sf::Vector2i &mousePos, const sf::Vector2f &center)
{
    this->m_sprite.setPosition(center);
    /*int dir = movement->getState(MOVING_LEFT) ? 2 : movement->getState(MOVING_RIGHT) ? 3 : movement->getState(MOVING_UP) ? 4 : movement->getState(MOVING_DOWN) ? 5 : 0;
    if(dir == 0) dir = this->m_dir;
    this->m_dir = dir;*/
    const float PI = 3.14159265f;
    if(this->m_is_attack)
    {
        this->m_is_attack = false;
        this->m_attack_deg_offset = this->m_attack_deg;
        fullAngle = limitAttackAngle(dir).y - limitAttackAngle(dir).x;
        fullAngle /= this->m_attack_time_speed;

        dss = this->limitAttackAngle(dir).y - this->m_attack_deg ;
        if(dir == movement_states::MOVING_RIGHT)
        {
            fullAngle = 360 - limitAttackAngle(dir).x + limitAttackAngle(dir).y;
            fullAngle /= this->m_attack_time_speed;
            if(270 < this->m_attack_deg && this->m_attack_deg < 360) dss = 360 - this->m_attack_deg + limitAttackAngle(dir).y;
        }
        if(dir == movement_states::MOVING_LEFT)
        {
            dss = this->m_attack_deg - this->limitAttackAngle(dir).x;
        }
        if(dss<=0){return;}
        this->m_attack_current_speed = this->m_attack_time_speed / (fullAngle / (dss / this->m_attack_time_speed));
        dss /= this->m_attack_current_speed;
        this->m_is_attacking = true;

    }
    if(this->m_is_attacking)
    {
        this->m_attack_time += dt;
        this->m_attack_deg = this->m_attack_deg_offset + fullAngle * this->m_attack_time;
        if(dir == movement_states::MOVING_LEFT) this->m_attack_deg = this->m_attack_deg_offset - dss * this->m_attack_time;
        if(this->m_attack_time >= this->m_attack_time_speed)
            this->m_is_attacking = false;
    }
    else
    {
        this->m_attack_deg = this->limitAttackAngle(dir).x;
        if(dir == movement_states::MOVING_LEFT) this->m_attack_deg = this->limitAttackAngle(dir).y;
        /*
        float dX = mousePos.x - this->m_sprite.getPosition().x;
        float dY = mousePos.y - this->m_sprite.getPosition().y;

        this->m_attack_deg = std::atan2(dY, dX);
        this->m_attack_deg = this->m_attack_deg * 360.f / (2*PI);
        if(this->m_attack_deg < 0) this->m_attack_deg+=360;

        if(dir == PLAYER_MOVE_DIR::RIGHT)
        {
            if(270 < this->m_attack_deg && this->m_attack_deg < 360 && this->m_attack_deg < this->limitAttackAngle(dir).x) this->m_attack_deg = this->limitAttackAngle(dir).x;
            if(0 < this->m_attack_deg && this->m_attack_deg < 90 && this->m_attack_deg > this->limitAttackAngle(dir).y) this->m_attack_deg = this->limitAttackAngle(dir).y;

            if(90 < this->m_attack_deg && this->m_attack_deg < 180)  this->m_attack_deg = this->limitAttackAngle(dir).y;
            if(180 < this->m_attack_deg && this->m_attack_deg < 270)  this->m_attack_deg = this->limitAttackAngle(dir).x;
        }
        else
        {
            if(this->m_attack_deg < this->limitAttackAngle(dir).x) this->m_attack_deg = this->limitAttackAngle(dir).x;
            if(this->m_attack_deg > this->limitAttackAngle(dir).y) this->m_attack_deg = this->limitAttackAngle(dir).y;
        }*/
    }
    this->m_sprite.setRotation(this->m_attack_deg + 90.f);
    float x = this->m_attack_distance * std::cos(this->m_attack_deg * PI / 180.f);
    float y = this->m_attack_distance * std::sin(this->m_attack_deg * PI / 180.f);

    this->m_point_attack = sf::Vector2f(center.x + x,center.y + y);
}
