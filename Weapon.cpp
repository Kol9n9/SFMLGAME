#include "Weapon.h"

Weapon::Weapon(const std::string &texture_file)
{
    this->m_texture.loadFromFile(texture_file);
    this->m_sprite.setTexture(this->m_texture);
    //ctor
}

Weapon::~Weapon()
{
    //dtor
}
