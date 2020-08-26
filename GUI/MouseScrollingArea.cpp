#include "MouseScrollingArea.h"

namespace GUI{
    MouseScrollingArea::MouseScrollingArea(const sf::Vector2f &start_pos, const sf::Vector2f &sizes)
        : GUI(start_pos,sizes,sf::Color(0,0,0),sf::Color(0,0,0),sf::Color(0,0,0))
    {
        this->m_isShowed = false;
        //ctor
    }

    MouseScrollingArea::~MouseScrollingArea()
    {
        //dtor
    }

    void MouseScrollingArea::update()
    {
        this->m_isContain = false;
        this->updateGUIState();
        if(this->getGUIStatus() == GUI_STATUS::HOVER || this->getGUIStatus() == GUI_STATUS::CLICKING)
        {
            this->m_isContain = true;
        }
    }

    void MouseScrollingArea::render(sf::RenderTarget *target)
    {
        if(this->m_isShowed)
        {
            sf::RectangleShape shape;
            shape.setSize(this->getSizes());
            shape.setPosition(this->getStartPos());
            shape.setFillColor(sf::Color(127,127,127));
            target->draw(shape);
        }
    }
    void MouseScrollingArea::Moving()
    {
        this->setPosition(sf::Vector2f(GUI::mousePos.x - this->getMoveOffset().x,
                                           GUI::mousePos.y - this->getMoveOffset().y));
    }
    void MouseScrollingArea::setPosition(const sf::Vector2f &pos)
    {
        this->setStartPos(pos);
    }
}
