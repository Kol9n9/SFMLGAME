#include "Sword.h"


Sword::Sword(const std::string &texture_file)
    : MeleeWeapon(texture_file)
{
    this->m_sprite.setOrigin
	(
		this->m_sprite.getGlobalBounds().width / 2.f,
		this->m_sprite.getGlobalBounds().height
	);
}
Sword::~Sword()
{
    //dtor
}
void Sword::attack()
{

}
void Sword::update(const int &dir, const sf::Vector2i &mousePos, const sf::Vector2f &center)
{
    this->m_sprite.setPosition(center);
    float dX = mousePos.x - this->m_sprite.getPosition().x;
	float dY = mousePos.y - this->m_sprite.getPosition().y;
    const float PI = 3.14159265f;
	float deg = std::atan2(dY, dX) * 180.f / PI;
	if(dir == PLAYER_MOVE_DIR::RIGHT)
    {
        if(deg < -60) deg = -60;
        else if(deg > 40) deg = 40;
    }
    if(dir == PLAYER_MOVE_DIR::DOWN)
    {
        if(deg < 50) deg = 50;
        else if(deg > 140) deg = 140;
    }
    if(dir == PLAYER_MOVE_DIR::LEFT)
    {
        /*if(deg + 180 > 60) deg = -120;*/
        if(deg < 0 && deg + 180 > 60) deg = -120;
        if(deg > 0 && deg < 135) deg = 135;

    }
    if(dir == PLAYER_MOVE_DIR::UP)
    {
        if(deg > -75) deg = -75;
        if(deg < -120) deg = -120;
    }
    this->m_sprite.setRotation(deg + 90.f);
}
