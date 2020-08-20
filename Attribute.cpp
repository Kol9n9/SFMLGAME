#include "Attribute.h"

Attribute::Attribute(const int &level, const int &strength, const int &agility, const int &stamina)
    : m_level(level), m_strength(strength), m_agility(agility), m_stamina(stamina)
{
    this->m_hp = this->m_stamina * 10;
    this->updateAttribute();
    //ctor
}

Attribute::~Attribute()
{
    //dtor
}

void Attribute::updateAttribute()
{

    this->m_hp_max = this->m_stamina * 10;
    this->m_damage = this->m_strength * 2;
}
