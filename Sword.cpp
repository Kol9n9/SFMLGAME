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
	this->m_attack_time_speed = 0.1;
}
Sword::~Sword()
{
    //dtor
}
void Sword::attack()
{
    if(this->m_is_attacking) return;
    this->m_is_attack = true;
    this->m_attack_time = 0;
}

