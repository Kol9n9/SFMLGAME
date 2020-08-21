#ifndef TEXTTAG_H
#define TEXTTAG_H

#include "SFML/Graphics.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
enum TextTag_TYPE{TextTag_DEFAULT = 0, TextTag_POSITIVE,TextTag_NEGATIVE};
class TextTag
{
    public:
        TextTag(const std::string &font_file);
        virtual ~TextTag();
        void render(sf::RenderTarget *target);
        void update(const float &dt);
        void addTextTag(TextTag_TYPE tag_type, const sf::String &str, const sf::Vector2f &pos);
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
                sf::Color m_color;
                /*sf::Vector2f m_velocity;
                sf::Vector2f m_acceleration;*/
                Tag(const sf::Font &font,const unsigned int &textSize, const sf::Color &color, const float &lifetime, const float &speed)
                    : m_color(color), m_lifetime(lifetime), m_speed(speed)
                {
                    this->m_text.setFont(font);
                    this->m_text.setCharacterSize(textSize);
                    this->m_text.setFillColor(color);
                }
                Tag(Tag *tag, const sf::String &str, const sf::Vector2f &pos) : m_pos(pos)
                {
                    this->m_text = tag->m_text;
                    this->m_text.setString(str);
                    this->m_text.setPosition(m_pos);
                    this->m_lifetime = tag->m_lifetime;
                    this->m_speed = tag->m_speed;
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
        std::map<unsigned,Tag*>m_tag_templates;
        std::vector<Tag*>m_tags;
        sf::Font m_font;
        void initFont(const std::string &font_file);
        void initTagTemplates();
};

#endif // TEXTTAG_H
