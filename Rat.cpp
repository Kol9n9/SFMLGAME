#include "Rat.h"

Rat::Rat(const float &base_hp, const float &base_damage,const sf::Vector2f &pos)
    : Enemy("resouces/rat.png",sf::IntRect(18,42,21,23),base_hp,base_damage,pos)
{
    this->m_hp = this->m_base_hp;
    this->m_hp_max = this->m_base_hp_max;
    this->m_damage = this->m_base_damage;
    this->m_hitbox = new Hitbox();
    this->m_isDied = false;
    this->m_hitbox->updateHitbox(this->m_position,this->getSpriteSize());
    this->m_hp_bar = new GUI::Progressbar(new GUI::Point(this->m_position.x,this->m_position.y-10),sf::Vector2f(this->m_hitbox->getHitbox().getSize().x,5),sf::Color(255,255,255),sf::Color(255,0,0),sf::Color(255,0,0));
    this->m_hp_bar->setPercent(100);
    //ctor
}

Rat::~Rat()
{
    //dtor
}

void Rat::update(const float &dt,const sf::Vector2i &mousePos)
{
    if(this->m_isDied) return;
    if(this->m_hitbox) this->m_hitbox->updateHitbox(this->m_position,this->getSpriteSize());
    if(this->m_hp_bar) this->m_hp_bar->update();
}
void Rat::render(sf::RenderTarget *target)
{
    if(this->m_isDied) return;
    target->draw(this->m_sprite);
    if(this->m_hitbox) target->draw(this->m_hitbox->getHitbox());
    if(this->m_hp_bar && this->m_hitbox && this->m_hitbox->intersect(GUI::GUI::mousePos)) this->m_hp_bar->render(target);
}
void Rat::attack()
{

}
void Rat::loseHP(const float &damage)
{
    this->m_hp -= damage;
    int percent = this->m_hp / this->m_hp_max * 100;
    this->m_hp_bar->setPercent(percent);
    if(this->m_hp <= 0) this->m_isDied = true;
}
