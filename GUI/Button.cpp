#include "Button.h"
namespace GUI{
    Button::Button(const sf::Vector2f &start_pos, const sf::Vector2f &sizes, Label *str, bool isV, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : Button_interface(start_pos,sizes,c_IDLE,c_HOVER,c_CLICK), isBoxVisible(isV)
    {
        this->text = str;
        this->updateTextPosition();
        //sf::Vector2f size = this->text->getSizes();
        //ctor
    }
    Button::Button(const sf::Vector2f &start_pos, const sf::Vector2f &sizes, const std::string &str,bool isV,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : Button_interface(start_pos,sizes,c_IDLE,c_HOVER,c_CLICK), isBoxVisible(isV)
    {
        this->text = NULL;
    }
    Button::~Button()
    {
        if(this->text) delete this->text;
        //dtor
    }
    void Button::update()
    {
        updateGUIState();
        this->updateColor();
        if(this->text) this->text->updateColor(this->getGUIStatus());

    }
    void Button::render(sf::RenderTarget *target)
    {
        if(this->isBoxShow)
        {
            sf::RectangleShape debug_shape;
            debug_shape.setOutlineColor(sf::Color::Red);
            debug_shape.setOutlineThickness(5);
            debug_shape.setPosition(this->getStartPos());
            debug_shape.setSize(this->getSizes());
            this->target->draw(debug_shape);
        }
        if(isBoxVisible) target->draw(this->getBox());
        if(this->text) this->text->render(target);
    }
    void Button::updateColor()
    {
        switch(this->getGUIStatus())
        {
            case GUI_STATUS::IDLE:
            {
                this->getBox().setFillColor(this->getColorIDLE());
                break;
            }
            case GUI_STATUS::HOVER:
            {
                this->getBox().setFillColor(this->getColorHOVER());
                break;
            }
            case GUI_STATUS::CLICKING:
            {
                this->getBox().setFillColor(this->getColorCLICK());
                break;
            }
        }
    }
    void Button::updateColor(const GUI_STATUS &status)
    {
        switch(status)
        {
            case GUI_STATUS::IDLE:
            {
                this->getBox().setFillColor(this->getColorIDLE());
                break;
            }
            case GUI_STATUS::HOVER:
            {
                this->getBox().setFillColor(this->getColorHOVER());
                break;
            }
            case GUI_STATUS::CLICKING:
            {
                this->getBox().setFillColor(this->getColorCLICK());
                break;
            }
        }
    }
    void Button::updateTextPosition()
    {
        this->text_offset.x = (this->getSizes().x - this->text->getSizes().x)/2;
        this->text_offset.y = (this->getSizes().y - this->text->getSizes().y)/2-this->text->getSizes().y/2;
        sf::Vector2f pos(this->text_offset.x + this->getStartPos().x,this->text_offset.y + this->getStartPos().y);
        this->text->setPosition(pos);
    }
    void Button::setPosition(const sf::Vector2f &pos)
    {
        this->setStartPos(sf::Vector2f(pos.x,pos.y));
        if(this->text) this->text->setPosition(this->text_offset+pos);
        this->getBox().setPosition(pos);
    }
    void Button::Moving()
    {
        this->setPosition(sf::Vector2f(GUI::mousePos.x - this->getMoveOffset().x,
                                           GUI::mousePos.y - this->getMoveOffset().y));
    }
    void Button::setSize(const sf::Vector2f &size)
    {
        this->setSizes(size);
        this->getBox().setSize(size);
    }
    void Button::Resizing()
    {
        this->updateTextPosition();
        this->setSize(this->getSizes());
    }
    void Button::setText(const sf::String &str)
    {
        this->text->setText(str);
        this->updateTextPosition();
    }
}
