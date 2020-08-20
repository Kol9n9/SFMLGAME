#include "TextInput.h"

namespace GUI{
    TextInput::TextInput(const Point *start_pos, const sf::Vector2f &sizes, sf::Font *font, unsigned int textSize,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : Label(start_pos,"",font,textSize,c_IDLE,c_HOVER,c_CLICK)
    {
        this->setSizes(sizes);
        this->str = "Text input";
        this->text.setFont(*font);
        this->text.setCharacterSize(this->textSize);
        this->text.setPosition(sf::Vector2f(start_pos->x,start_pos->y));
        this->text.setString(this->str);
        this->isActive = false;
        this->text_box.setPosition(sf::Vector2f(start_pos->x,start_pos->y+2));
        this->text_box.setSize(this->getSizes());
        this->text_box.setOutlineColor(sf::Color(127,127,127));
        this->text_box.setOutlineThickness(5);
        //ctor
    }

    TextInput::~TextInput()
    {
        //dtor
    }
    void TextInput::update()
    {
        this->updateGUIState();
        if(this->isActive && GUI::mouse_click_event == MOUSE_CLICK_EVENTS::LEFTCLICK && this->getGUIStatus() != GUI_STATUS::HOVER)
            this->isActive = false;
        switch(this->getGUIStatus())
        {
            case GUI_STATUS::CLICK:
            {
                this->isActive = true;
            }
        }
    }
    void TextInput::inputSymbol(const uint32_t &symbol)
    {
        if(symbol == GUI_TEXT_BACKSPACE)
        {
            if(this->str.getSize() > 0)
            {
                this->str = this->str.substring(0,this->str.getSize()-1);
            }
        }
        else if(symbol == GUI_TEXT_ESCAPE)
        {
            this->isActive = false;
            return;
        }
        else
        {
            this->str += symbol;
        }
        this->text.setString(str);
    }
    void TextInput::render(sf::RenderTarget *target)
    {
        if(this->isBoxShow)
        {
            sf::RectangleShape debug_shape;
            debug_shape.setOutlineColor(sf::Color::Red);
            debug_shape.setOutlineThickness(5);
            debug_shape.setPosition(sf::Vector2f(this->getStartPoint().x,this->getStartPoint().y));
            debug_shape.setSize(this->getSizes());
            target->draw(debug_shape);
        }
        target->draw(this->text_box);
        target->draw(this->text);
    }
    void TextInput::setPosition(const sf::Vector2f &pos)
    {
        this->setStartPoint(Point(pos.x,pos.y));
        this->text.setPosition(pos);
    }
    void TextInput::setSize(const sf::Vector2f &size)
    {

    }
    void TextInput::Moving()
    {
        this->setPosition(sf::Vector2f(static_cast<sf::Vector2f>(GUI::mousePos) - this->getMoveOffset()));
    }
    void TextInput::Resizing()
    {

    }
}
