#include "Animation.h"

Animation::Animation(sf::Sprite &sprite)
    : m_sprite(sprite)
{
}

Animation::~Animation()
{
    //dtor
}

void Animation::addAnimation(const std::string &key, const float &timer, const std::vector<sf::IntRect> &frames)
{
    this->m_animlist[key] = new Anim(timer,frames,this->m_sprite);
}
void Animation::play(const std::string &key,const float &dt,const bool &first)
{
    this->m_animlist[key]->play(dt,first);
}
