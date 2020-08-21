#ifndef TEXTTAG_H
#define TEXTTAG_H

#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
class TextTag
{
    public:
        TextTag(const std::string &font_file);
        virtual ~TextTag();
        void render(sf::RenderTarget *target);
        void update(const float &dt);
        void addTextTag(const sf::String &str, const sf::Vector2f &pos);
    protected:

    private:
        class Tag{
            public:
                sf::Text m_text;
                sf::Vector2f m_pos;
                float m_lifetime;
                float m_dirX;
                float m_dirY;
                float m_speed;
                /*sf::Vector2f m_velocity;
                sf::Vector2f m_acceleration;*/
                Tag(const sf::Font &font, const sf::String &str, const sf::Vector2f &pos, const float &lifetime, const float &speed) : m_pos(pos), m_lifetime(lifetime), m_speed(speed)
                {
                    this->m_text.setString(str);
                    this->m_text.setFont(font);
                    this->m_text.setPosition(m_pos);
                    this->m_text.setCharacterSize(15);
                    this->m_dirX = pos.x;
                    this->m_dirY = pos.y;

                }
                const bool isFinished() const {return this->m_lifetime <= 0.f;}
                void update(const float &dt)
                {
                    if(this->m_lifetime > 0.f)
                    {
                        this->m_lifetime -= 100 * dt;
                        this->m_dirY -= this->m_speed * dt;
                        this->m_text.setPosition(sf::Vector2f(this->m_dirX,this->m_dirY));
                    }
                }
                void render(sf::RenderTarget *target)
                {
                    target->draw(this->m_text);
                }
        };
        std::vector<Tag*>m_tags;
        sf::Font m_font;
};

#endif // TEXTTAG_H
