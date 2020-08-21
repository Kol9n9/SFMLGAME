#include "TextTag.h"
void TextTag::initFont(const std::string &font_file)
{
    this->m_font.loadFromFile(font_file);
}
void TextTag::initTagTemplates()
{
    this->m_tag_templates[TextTag_TYPE::TextTag_DEFAULT] =  new Tag(this->m_font,15,sf::Color(255,255,255),80.f,20);
    this->m_tag_templates[TextTag_TYPE::TextTag_NEGATIVE] = new Tag(this->m_font,15,sf::Color(255,0,0),80.f,20);
    this->m_tag_templates[TextTag_TYPE::TextTag_POSITIVE] = new Tag(this->m_font,15,sf::Color(0,255,0),80.f,-20);
}
TextTag::TextTag(const std::string &font_file)
{
    this->initFont(font_file);
    this->initTagTemplates();
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
void TextTag::addTextTag(TextTag_TYPE tag_type, const sf::String &str,const sf::Vector2f &pos)
{
    this->m_tags.push_back(new Tag(this->m_tag_templates[tag_type],str,pos));
}
