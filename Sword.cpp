#include "Sword.h"


Sword::Sword(const std::string &texture_file)
    : MeleeWeapon(texture_file)
{
    this->m_sprite.setOrigin
	(
		this->m_sprite.getGlobalBounds().width / 2.f,
		this->m_sprite.getGlobalBounds().height
	);
	this->m_attack_distance = 50.f;
	this->m_attack_time_speed = 2;
	this->m_is_attack = false;
	this->isAtacking = false;
}
Sword::~Sword()
{
    //dtor
}
void Sword::attack()
{
    if(this->m_is_attack) return;
    this->m_is_attack = true;
    this->m_attack_time = 0;
    this->isAtacking = true;


    std::cout << "this->m_attack_deg = " << this->m_attack_deg << "\n";



}
sf::Vector2f Sword::limitAttackAngle(const int &dir)
{
    switch(dir)
    {
        case PLAYER_MOVE_DIR::DOWN:
        {
            return sf::Vector2f(50,140);
        }
        case PLAYER_MOVE_DIR::UP:
        {
            return sf::Vector2f(240,290);
        }
        case PLAYER_MOVE_DIR::LEFT:
        {
            return sf::Vector2f(140,240);
        }
        case PLAYER_MOVE_DIR::RIGHT:
        {
            return sf::Vector2f(290,60);
        }
    }
}
void Sword::update(const float &dt, const int &dir, const sf::Vector2i &mousePos, const sf::Vector2f &center)
{
    this->m_sprite.setPosition(center);
    if(this->isAtacking)
    {
        float fullAngle = limitAttackAngle(dir).x < 0 ? limitAttackAngle(dir).x * -1 : limitAttackAngle(dir).x;
        fullAngle += limitAttackAngle(dir).y < 0 ? limitAttackAngle(dir).y * -1 : limitAttackAngle(dir).y;
        fullAngle /= this->m_attack_time_speed;



        dss = (this->m_attack_deg < 0) ? this->m_attack_deg * -1 : this->m_attack_deg;
        std::cout << "dss  = " << dss  << "\n";
        dss += limitAttackAngle(dir).y;
        std::cout << "dss  = " << dss  << "\n";
        this->m_attack_current_speed = this->m_attack_time_speed / (fullAngle / (dss / this->m_attack_time_speed));
        this->isAtacking = false;
        dss /= this->m_attack_current_speed;
        std::cout << "dss  = " << dss  << "\n";
        std::cout << "this->m_attack_current_speed  = " << this->m_attack_current_speed  << "\n";
    }
    if(this->m_is_attack)
    {
        const float PI = 3.14159265f;
        this->m_attack_time += dt;



        this->m_attack_deg += dss * dt;
        //std::cout << "this->m_attack_deg  = " << this->m_attack_deg  << "\n";
        this->m_sprite.setRotation(this->m_attack_deg + 90.f);
        float x = this->m_attack_distance * std::cos(this->m_attack_deg * PI / 180.f);
        float y = this->m_attack_distance * std::sin(this->m_attack_deg * PI / 180.f);
        this->m_point_attack = sf::Vector2f(center.x + x,center.y + y);

        if(this->m_attack_time >= this->m_attack_current_speed)
            this->m_is_attack = false;
        return;
    }

    float dX = mousePos.x - this->m_sprite.getPosition().x;
	float dY = mousePos.y - this->m_sprite.getPosition().y;
    const float PI = 3.14159265f;
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
    }

    this->m_sprite.setRotation(this->m_attack_deg + 90.f);
    float x = this->m_attack_distance * std::cos(this->m_attack_deg * PI / 180.f);
    float y = this->m_attack_distance * std::sin(this->m_attack_deg * PI / 180.f);

    this->m_point_attack = sf::Vector2f(center.x + x,center.y + y);
}
