#include "TextTag.h"

TextTag::TextTag(const std::string &font_file)
{
    this->m_font.loadFromFile(font_file);
}

TextTag::~TextTag()
{
    //dtor
}

void TextTag::update(const float &dt)
{
    if(!this->m_tags.empty())
    {
        for(int i = 0; i < this->m_tags.size(); ++i)
        {

            this->m_tags[i]->update(dt);
            if(this->m_tags[i]->isFinished())
            {
                delete this->m_tags[i];
                this->m_tags.erase(this->m_tags.begin() + i);
            }
        }
    }
}
void TextTag::render(sf::RenderTarget *target)
{
    if(!this->m_tags.empty())
    {
        for(auto &it : this->m_tags)
        {
            it->render(target);
        }
    }
}
void TextTag::addTextTag(const sf::String &str,const sf::Vector2f &pos)
{
    this->m_tags.push_back(new Tag(this->m_font,str,pos,70,20));
}
