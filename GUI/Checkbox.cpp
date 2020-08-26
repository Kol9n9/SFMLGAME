#include "Checkbox.h"

namespace GUI{
    Checkbox::Checkbox(const sf::Vector2f &start_pos, const int& sz, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : Button_interface(start_pos,sf::Vector2f(sz,sz),c_IDLE,c_HOVER,c_CLICK)
    {
        this->getBox().setOutlineColor(this->getColorIDLE());
        this->getBox().setOutlineThickness(5);
        this->lineWidth = sz/5;

        this->line1.setFillColor(this->getColorCLICK());
        this->line1.rotate(30.f);

        this->line2.setFillColor(this->getColorCLICK());
        this->line2.rotate(-60.f);

        this->updateLinesSize();
        this->updateLinesPosition();

        this->isCheck = false;

        //ctor
    }

    Checkbox::~Checkbox()
    {
        //dtor
    }
    void Checkbox::update()
    {
        this->updateGUIState();
        switch(this->getGUIStatus())
        {
            case GUI_STATUS::IDLE:
            {
                break;
            }
            case GUI_STATUS::HOVER:
            {
                break;
            }
            case GUI_STATUS::CLICK:
            {
                if(this->isCheck) this->isCheck = false;
                else this->isCheck = true;
                break;
            }
        }
    }
    void Checkbox::render(sf::RenderTarget *target)
    {
        target->draw(this->getBox());
        if(this->isBoxShow)
        {
            sf::RectangleShape debug_shape;
            debug_shape.setOutlineColor(sf::Color::Red);
            debug_shape.setOutlineThickness(5);
            debug_shape.setPosition(this->getStartPos());
            debug_shape.setSize(this->getSizes());
            target->draw(debug_shape);
        }
        if(this->isCheck)
        {
            target->draw(this->line1);
            target->draw(this->line2);
        }
    }
    void Checkbox::Moving()
    {
        this->setPosition(sf::Vector2f(static_cast<sf::Vector2f>(GUI::mousePos) - this->getMoveOffset()));
    }
    void Checkbox::setPosition(const sf::Vector2f &pos)
    {
        this->setStartPos(sf::Vector2f(pos.x,pos.y));
        this->getBox().setPosition(pos);
        this->updateLinesPosition();
    }
    void Checkbox::updateLinesPosition()
    {
        this->line1.setPosition(sf::Vector2f(this->getStartPos().x + (this->getSizes().x - this->lineWidth), this->getStartPos().y + this->lineWidth/2));
        int posX = this->line1.getGlobalBounds().left - this->line2.getGlobalBounds().width + this->lineWidth + this->lineWidth/2 - 1;
        int posY = this->line1.getGlobalBounds().top + this->line1.getGlobalBounds().height - this->line2.getGlobalBounds().height + this->lineWidth - this->lineWidth/4 - 1;
        this->line2.setPosition(sf::Vector2f(posX,posY));
    }
    void Checkbox::setSize(const sf::Vector2f &size)
    {
        this->setSizes(size);
        this->getBox().setSize(size);
        this->lineWidth = size.x/5;
        this->updateLinesSize();
        this->updateLinesPosition();
    }
    void Checkbox::Resizing()
    {
        sf::Vector2f newSize = this->getSizes();
        newSize.y = newSize.x;
        if(newSize.x < 5) newSize.x = newSize.y = 5;
        this->setSize(newSize);
    }
    void Checkbox::updateLinesSize()
    {
        sf::Vector2f line1_size(this->lineWidth,this->getSizes().y-this->lineWidth/2);
        this->line1.setSize(line1_size);
        this->line2.setSize(sf::Vector2f(this->lineWidth,this->getSizes().y/2));
    }

}
