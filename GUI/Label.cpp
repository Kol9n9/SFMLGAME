#include "Label.h"
namespace GUI{
    Label::Label(const sf::Vector2f &start_pos, const sf::String &str, sf::Font *font, unsigned int textSize,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : GUI(start_pos,sf::Vector2f(0,0),c_IDLE,c_HOVER,c_CLICK), str(str), font(font), textSize(textSize)
    {
        /*std::string utf8 = str.c_str();
        sf::String t = sf::String::fromUtf8(utf8.begin(),utf8.end());*/
        this->text.setString(str);
        this->text.setPosition(this->getStartPos());
        this->text.setFont(*this->font);
        this->text.setCharacterSize(this->textSize);
        this->setTextBoxSize();

        this->text.setColor(this->getColorIDLE());
        //ctor
    }

    Label::~Label()
    {
        //dtor
    }
    void Label::updateColor()
    {
        switch(this->getGUIStatus())
        {
            case GUI_STATUS::IDLE:
            {
                this->text.setColor(this->getColorIDLE());
                break;
            }
            case GUI_STATUS::HOVER:
            {
                this->text.setColor(this->getColorHOVER());
                break;
            }
            case GUI_STATUS::CLICKING:
            {
                this->text.setColor(this->getColorCLICK());
                break;
            }
        }
    }
    void Label::updateColor(const GUI_STATUS &status)
    {
        switch(status)
        {
            case GUI_STATUS::IDLE:
            {
                this->text.setColor(this->getColorIDLE());
                break;
            }
            case GUI_STATUS::HOVER:
            {
                this->text.setColor(this->getColorHOVER());
                break;
            }
            case GUI_STATUS::CLICKING:
            {
                this->text.setColor(this->getColorCLICK());
                break;
            }
        }
    }
    void Label::update()
    {
        updateGUIState();
        updateColor();
    }
    void Label::Moving()
    {
         this->setPosition(sf::Vector2f(static_cast<sf::Vector2f>(GUI::mousePos) - this->getMoveOffset()));
    }
    void Label::render(sf::RenderTarget *target)
    {
        if(this->isBoxShow)
        {
            sf::RectangleShape debug_shape;
            debug_shape.setOutlineColor(sf::Color::Red);
            debug_shape.setOutlineThickness(5);
            debug_shape.setPosition(this->getStartPos());
            debug_shape.setSize(this->getSizes());
            target->draw(debug_shape);
        }
        target->draw(this->text);
    }
    void Label::setText(const std::string &str)
    {
        std::string utf8 = str.c_str();
        sf::String t = sf::String::fromUtf8(utf8.begin(),utf8.end());
        this->text.setString(t);
        this->setTextBoxSize();
    }
    void Label::setFont(sf::Font *font)
    {
        this->font = font;
        this->text.setFont(*this->font);
        this->setTextBoxSize();
    }
    void Label::setTextSize(const unsigned int size)
    {
        this->textSize = size;
        this->text.setCharacterSize(this->textSize);
        this->setTextBoxSize();
    }
    void Label::setTextBoxSize()
    {
        this->setSizes(sf::Vector2f(this->text.getLocalBounds().width, this->text.getLocalBounds().height));
    }
    void Label::setPosition(const sf::Vector2f &pos)
    {
        this->setStartPos(sf::Vector2f(pos.x,pos.y));
        this->text.setPosition(pos);
    }
    void Label::setBoxSize(const sf::Vector2f &size)
    {
        float x = size.x;
        float y = size.y;
        /*if(this->getSizes().x > size.x) x = this->getSizes().x;
        if(this->getSizes().y > size.y) y = this->getSizes().y;*/
        this->setSizes(sf::Vector2f(x,y));
    }
    void Label::setScale(const sf::Vector2f &scale)
    {
        float x = this->text.getScale().x;
        float y = this->text.getScale().y;
        x/=scale.x;
        y/=scale.y;

        this->text.setScale(scale.x,scale.y);
        this->setSizes(sf::Vector2f(this->getSizes().x / x,this->getSizes().y / y));
    }
    void Label::Resizing()
    {
        sf::Vector2f newSize = this->getSizes();
        sf::Vector2f oldSize(this->text.getLocalBounds().width, this->text.getLocalBounds().height);
        float x = newSize.x / oldSize.x;
        int ac = this->textSize * x;
        if(ac < 5) ac = 5;
        this->setTextSize(ac);
    }
}
