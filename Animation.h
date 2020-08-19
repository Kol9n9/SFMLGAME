#ifndef ANIMATION_H
#define ANIMATION_H
#include "SFML/Graphics.hpp"
#include <string>
#include <map>
#include <vector>
#include <iostream>
class Animation
{

    public:
        Animation(sf::Sprite &sprite);
        virtual ~Animation();
        void play(const std::string &key,const float &dt);
        void addAnimation(const std::string &key, const float &timer, const std::vector<sf::IntRect> &frames);
    protected:

    private:

    class Anim{
    private:
        std::vector<sf::IntRect> m_frames;
        sf::IntRect m_currentFrame;
        int m_current;
        sf::Sprite &m_sprite;
        float m_timer;
        float m_timerMax;
        bool m_isDone;
    public:

        Anim(const float &timerMax, const std::vector<sf::IntRect> &frames, sf::Sprite &sprite)
            : m_timer(timerMax-1), m_current(0), m_isDone(false), m_timerMax(timerMax), m_frames(frames), m_sprite(sprite)
        {
        }
        const bool &play(const float &dt)
        {
            this->m_isDone = false;
            this->m_timer += 100*dt;
            if(this->m_timer >= this->m_timerMax)
            {
                this->m_timer = 0;
                this->m_current++;
                this->m_currentFrame = this->m_frames[this->m_current];

                if(m_current == this->m_frames.size()-1)
                {
                    this->m_currentFrame = m_frames[0];
                    this->m_current = 0;
                    this->m_isDone = true;
                }
                this->m_sprite.setTextureRect(this->m_currentFrame);
            }

            return this->m_isDone;
        }
        void reset()
        {
            this->m_timer = this->m_timerMax;

        }

    };

    sf::Sprite &m_sprite;
    std::map<std::string,Anim*> m_animlist;
};

#endif // ANIMATION_H
